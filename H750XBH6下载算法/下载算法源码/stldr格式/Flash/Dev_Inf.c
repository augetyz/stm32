/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright (c) 2020 Keil - An ARM Company. All rights reserved.     */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.c:  Device Description for ST STM32H7B3I-B0-DISCO Flash      */
/*                                                                     */
/***********************************************************************/

#include "Dev_Inf.H"       


#if defined (__ICCARM__)
__root struct StorageInfo const StorageInfo  =  {
#else
struct StorageInfo const StorageInfo =  {
#endif
	
    "STM32CubePro_FK750M5_XBH6_V0", 	// Device Name + version number
    NOR_FLASH,                    		// Device Type
    0x90000000,                     	// Device Start Address
    8 * 1024 * 1024,                	// Device Size in Bytes (8MBytes)
    4*1024,                         	// Programming Page Size 16Bytes
    0xFF,                          		// Initial Content of Erased Memory
    128 , 64 * 1024,                	// Sector Num : 128 ,Sector Size: 64KBytes 
    0x00000000, 0x00000000,	
	
};



