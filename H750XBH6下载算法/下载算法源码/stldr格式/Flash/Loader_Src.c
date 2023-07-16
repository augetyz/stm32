/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright (c) 2020 Keil - An ARM Company. All rights reserved.     */
/***********************************************************************/
/*                                                                     */
/*  FlashPrg.c:  Flash Programming Functions adapted for               */
/*               ST Microelectronics STM32h7B3I/B0-Disco Flash         */
/*                                                                     */
/***********************************************************************/

#include "Dev_Inf.h"
#include "SystemConfig.h"
#include "qspi_w25q64.h"


/**
  * Description :
  * Initilize the MCU Clock, the GPIO Pins corresponding to the
  * device and initilize the FSMC with the chosen configuration 
  * Inputs    :
  *      None
  * outputs   :
  *      R0             : "1" 			: Operation succeeded
  * 			  "0" 			: Operation failure
  * Note: Mandatory for all types of device 
  */
int Init (void) 
{
//	for (int i = 0; i < 8; i++)
//	{
//	  NVIC->ICER[i]=0xFFFFFFFF;
//	  NVIC->ICPR[i]=0xFFFFFFFF;
//	}      
//	__set_PRIMASK(1);//关所有中断
		
	SystemInit(); 				// 系统初始化
	SystemClock_Config();	// 配置系统时钟，主频480MHz
	QSPI_W25Qxx_Init();  	// 初始化W25Q64
	
	return 1;
}


/**
  * Description :
  * Read data from the device 
  * Inputs    :
  *      Address       : Write location
  *      Size          : Length in bytes  
  *      buffer        : Address where to get the data to write
  * outputs   :
  *      R0             : "1" 			: Operation succeeded
  * 			  "0" 			: Operation failure
  * Note: Mandatory for all types except SRAM and PSRAM	
  */
int Read (uint32_t Address, uint32_t Size, uint8_t* buffer)
{ 
	if ( QSPI_W25Qxx_ReadBuffer(buffer, Address- W25Qxx_Mem_Addr, Size) != QSPI_W25Qxx_OK )  // 读取数据
	{
		return 0;	
	}	
	return 1;
} 


/**
  * Description :
  * Write data from the device 
  * Inputs    :
  *      Address       : Write location
  *      Size          : Length in bytes  
  *      buffer        : Address where to get the data to write
  * outputs   :
  *      R0           : "1" 			: Operation succeeded
  *                     "0" 			: Operation failure
  * Note: Mandatory for all types except SRAM and PSRAM	
  */
int Write (uint32_t Address, uint32_t Size, uint8_t* buffer)
{
	if ( QSPI_W25Qxx_WriteBuffer(buffer, Address -W25Qxx_Mem_Addr, Size) != QSPI_W25Qxx_OK )  // 写入数据
	{
		return 0;	
	}	
	return 1;                      
}


/**
  * Description :
  * Erase a full sector in the device
  * Inputs    :
  *     None
  * outputs   :
  *     R0             : "1" : Operation succeeded
  * 			 "0" : Operation failure
  * Note: Not Mandatory for SRAM PSRAM and NOR_FLASH
  */
int MassErase (void)
{  
	if ( QSPI_W25Qxx_ChipErase() != QSPI_W25Qxx_OK )  // 整片擦除
	{
		return 0;
	}
	
	return 1;  
}


/**
  * Description :
  * Erase a full sector in the device
  * Inputs    :
  *      SectrorAddress	: Start of sector
  *      Size          : Size (in WORD)  
  *      InitVal       : Initial CRC value
  * outputs   :
  *     R0             : "1" : Operation succeeded
  * 			 "0" : Operation failure
  * Note: Not Mandatory for SRAM PSRAM and NOR_FLASH
  */
int SectorErase (uint32_t EraseStartAddress ,uint32_t EraseEndAddress)
{     
	uint32_t BlockAddr;
 	
	EraseStartAddress -= W25Qxx_Mem_Addr;
	EraseEndAddress -= W25Qxx_Mem_Addr;
	EraseStartAddress = EraseStartAddress -  EraseStartAddress % 0x10000; // 64KB首地址 

	
	while (EraseEndAddress >= EraseStartAddress)
	{
		BlockAddr = EraseStartAddress & 0x0FFFFFFF;
		
		if ( QSPI_W25Qxx_BlockErase_64K(BlockAddr) != QSPI_W25Qxx_OK )  // 擦除对应扇区
		{
			return 0;
		}
		
		EraseStartAddress += 0x10000;
	}
	return 1;
}


/**
  * Description :
  * Calculates checksum value of the memory zone
  * Inputs    :
  *      StartAddress  : Flash start address
  *      Size          : Size (in WORD)  
  *      InitVal       : Initial CRC value
  * outputs   :
  *     R0             : Checksum value
  * Note: Optional for all types of device
  */
uint32_t CheckSum(uint32_t StartAddress, uint32_t Size, uint32_t InitVal)
{
	StartAddress -= W25Qxx_Mem_Addr;

	uint8_t missalignementAddress = StartAddress%4;
	uint8_t missalignementSize = Size ;
	int cnt;
	uint32_t Val;
	uint8_t value;

	StartAddress-=StartAddress%4;
	Size += (Size%4==0)?0:4-(Size%4);
  
  for(cnt=0; cnt<Size ; cnt+=4)
  {
    QSPI_W25Qxx_ReadBuffer(&value, StartAddress ,1);
    Val = value;
    QSPI_W25Qxx_ReadBuffer(&value, StartAddress + 1,1);
    Val+= value<<8;
    QSPI_W25Qxx_ReadBuffer(&value, StartAddress + 2,1);
    Val+= value<<16;
    QSPI_W25Qxx_ReadBuffer(&value, StartAddress + 3,1);
    Val+= value<<24;
    if(missalignementAddress)
    {
      switch (missalignementAddress)
      {
        case 1:
          InitVal += (uint8_t) (Val>>8 & 0xff);
          InitVal += (uint8_t) (Val>>16 & 0xff);
          InitVal += (uint8_t) (Val>>24 & 0xff);
          missalignementAddress-=1;
          break;
        case 2:
          InitVal += (uint8_t) (Val>>16 & 0xff);
          InitVal += (uint8_t) (Val>>24 & 0xff);
          missalignementAddress-=2;
          break;
        case 3:   
          InitVal += (uint8_t) (Val>>24 & 0xff);
          missalignementAddress-=3;
          break;
      }  
    }
    else if((Size-missalignementSize)%4 && (Size-cnt) <=4)
    {
      switch (Size-missalignementSize)
      {
        case 1:
          InitVal += (uint8_t) Val;
          InitVal += (uint8_t) (Val>>8 & 0xff);
          InitVal += (uint8_t) (Val>>16 & 0xff);
          missalignementSize-=1;
          break;
        case 2:
          InitVal += (uint8_t) Val;
          InitVal += (uint8_t) (Val>>8 & 0xff);
          missalignementSize-=2;
          break;
        case 3:   
          InitVal += (uint8_t) Val;
          missalignementSize-=3;
          break;
      } 
    }
    else
    {
      InitVal += (uint8_t) Val;
      InitVal += (uint8_t) (Val>>8 & 0xff);
      InitVal += (uint8_t) (Val>>16 & 0xff);
      InitVal += (uint8_t) (Val>>24 & 0xff);
    }
    StartAddress+=4;
  }
  
  return (InitVal);
}

/**
  * Description :
  * Verify flash memory with RAM buffer and calculates checksum value of
  * the programmed memory
  * Inputs    :
  *      FlashAddr     : Flash address
  *      RAMBufferAddr : RAM buffer address
  *      Size          : Size (in WORD)  
  *      InitVal       : Initial CRC value
  * outputs   :
  *     R0             : Operation failed (address of failure)
  *     R1             : Checksum value
  * Note: Optional for all types of device
  */
uint64_t Verify (uint32_t MemoryAddr, uint32_t RAMBufferAddr, uint32_t Size, uint32_t missalignement)
{
  uint32_t InitVal = 0;
  uint32_t VerifiedData = 0;
  uint8_t TmpBuffer = 0x00;
	uint64_t checksum;
  Size*=4;
        
	MemoryAddr -=W25Qxx_Mem_Addr;
	
  checksum = CheckSum((uint32_t)MemoryAddr + (missalignement & 0xf), Size - ((missalignement >> 16) & 0xF), InitVal);
  
  while (Size>VerifiedData)
  {
    QSPI_W25Qxx_ReadBuffer(&TmpBuffer, MemoryAddr+VerifiedData, 1);
         
    if (TmpBuffer != *((uint8_t*)RAMBufferAddr+VerifiedData))
      return ((checksum<<32) + MemoryAddr+VerifiedData);
        
    VerifiedData++;  
  }
       
  return (checksum<<32);

}
