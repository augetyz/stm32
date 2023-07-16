#include "SD_use.h"
#include "fatfs.h"
#include <stdio.h>
#include "ffconf.h"	

int32_t SD_Status ; 		 //SD卡检测标志位
FATFS 	SD_FatFs; 		// 文件系统对象
FRESULT File_Res;    // 操作结果 

uint32_t SD_ReadBuffer[512*64/4];	//	读数据数组
BYTE 	MyFile_ReadBuffer[1024];	//要读出的数据
extern UART_HandleTypeDef huart4;

char FR_Table[20][30]=
{
    "FR_OK", 				    /* (0) Succeeded */
	"FR_DISK_ERR",			/* (1) A hard error occurred in the low level disk I/O layer */
	"FR_INT_ERR",				/* (2) Assertion failed */
	"FR_NOT_READY",			/* (3) The physical drive cannot work */
	"FR_NO_FILE",				/* (4) Could not find the file */
	"FR_NO_PATH",				/* (5) Could not find the path */
	"FR_INVALID_NAME",		/* (6) The path name format is invalid */
	"FR_DENIED",				/* (7) Access denied due to prohibited access or directory full */
	"FR_EXIST",				/* (8) Access denied due to prohibited access */
	"FR_INVALID_OBJECT",		/* (9) The file/directory object is invalid */
	"FR_WRITE_PROTECTED",		/* (10) The physical drive is write protected */
	"FR_INVALID_DRIVE",		/* (11) The logical drive number is invalid */
	"FR_NOT_ENABLED",			/* (12) The volume has no work area */
	"FR_NO_FILESYSTEM",		/* (13) There is no valid FAT volume */
	"FR_MKFS_ABORTED",		/* (14) The f_mkfs() aborted due to any problem */
	"FR_TIMEOUT",				/* (15) Could not get a grant to access the volume within defined period */
	"FR_LOCKED",				/* (16) The operation is rejected according to the file sharing policy */
	"FR_NOT_ENOUGH_CORE",		/* (17) LFN working buffer could not be allocated */
	"FR_TOO_MANY_OPEN_FILES",	/* (18) Number of open files > _FS_LOCK */
	"FR_INVALID_PARAMETER"	/* (19) Given parameter is invalid */
};
extern SD_HandleTypeDef hsd1;


/**
  * @brief  SD卡信息输出函数
  * @param  无
  * @retval 无
  */
void show_sdcard_info(SD_HandleTypeDef hsd)
{
    uint64_t card_capacity;       /* SD卡容量 */
    HAL_SD_CardCIDTypeDef sd_card_cid;
    HAL_SD_CardInfoTypeDef g_sd_card_info_handle;
    HAL_SD_GetCardCID(&hsd, &sd_card_cid);      /* 获取CID */
    HAL_SD_GetCardInfo(&hsd,&g_sd_card_info_handle);            /* 获取SD卡信息 */

    switch (g_sd_card_info_handle.CardType)
    {
        case CARD_SDSC:
        {
            if (g_sd_card_info_handle.CardVersion == CARD_V1_X)
            {
                printf("Card Type:SDSC V1\r\n");
            }
            else if (g_sd_card_info_handle.CardVersion == CARD_V2_X)
            {
                printf("Card Type:SDSC V2\r\n");
            }
        }
            break;
        
        case CARD_SDHC_SDXC:
            printf("Card Type:SDHC\r\n");
            break;
    }

    card_capacity = (uint64_t)(g_sd_card_info_handle.LogBlockNbr) * 
    (uint64_t)(g_sd_card_info_handle.LogBlockSize); /* 计算SD卡容量 */
    /* 制造商ID */
    printf("Card ManufacturerID:%d\r\n", sd_card_cid.ManufacturerID); 
    /* 卡相对地址 */               
        printf("Card RCA:%d\r\n", g_sd_card_info_handle.RelCardAdd);       
    printf("LogBlockNbr:%d \r\n", 
    (uint32_t)(g_sd_card_info_handle.LogBlockNbr));   /* 显示逻辑块数量 */
    printf("LogBlockSize:%d \r\n", 
    (uint32_t)(g_sd_card_info_handle.LogBlockSize));  /* 显示逻辑块大小 */
    /* 显示容量 */
    printf("Card Capacity:%d GB\r\n", (uint32_t)(card_capacity >> 20)/1024);     
    /* 显示块大小 */         
    printf("Card BlockSize:%d\r\n\r\n", g_sd_card_info_handle.BlockSize);    
}

void FatFs_GetVolume(void)	// 计算设备容量
{
	FATFS *fs;		//定义结构体指针
	uint32_t SD_CardCapacity = 0;		//SD卡的总容量
	uint32_t SD_FreeCapacity = 0;		//SD卡空闲容量
	DWORD fre_clust, fre_sect, tot_sect; 	//空闲簇，空闲扇区数，总扇区数

	f_getfree("0:",&fre_clust,&fs);			//获取SD卡剩余的簇

	tot_sect = (fs->n_fatent-2) * fs->csize;	//总扇区数量 = 总的簇 * 每个簇包含的扇区数
	fre_sect = fre_clust * fs->csize;			//计算剩余的可用扇区数	   

	SD_CardCapacity = tot_sect / 2048 ;	// SD卡总容量 = 总扇区数 * 512( 每扇区的字节数 ) / 1048576(换算成MB)
	SD_FreeCapacity = fre_sect / 2048 ;	//计算剩余的容量，单位为M
	printf("-------------------获取设备容量信息-----------------\r\n");		
	printf("SD容量：%dMB\r\n",SD_CardCapacity);	
	printf("SD剩余：%dMB\r\n",SD_FreeCapacity);
}
uint8_t  FatFs_FileTest(void)	//文件创建和写入测试
{
	uint8_t i = 0;
	uint16_t BufferSize = 0;	
	FIL	MyFile;			// 文件对象
	UINT 	MyFile_Num;		//	数据长度
	BYTE 	MyFile_WriteBuffer[] = "STM32H750 SD卡 文件系统测试\n";	//要写入的数据
	
	
	printf("-------------FatFs 文件创建和写入测试---------------\r\n");
	
	File_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_CREATE_ALWAYS | FA_WRITE);	//打开文件，若不存在则创建该文件
	if(File_Res == FR_OK)
	{
		printf("文件打开/创建成功，准备写入数据...\r\n");
		
		File_Res = f_write(&MyFile,MyFile_WriteBuffer,sizeof(MyFile_WriteBuffer),&MyFile_Num);	//向文件写入数据
		if (File_Res == FR_OK)	
		{
            
			printf("写入成功，写入内容为：\r\n");
            HAL_Delay(100);
            HAL_UART_Transmit(&huart4, (uint8_t *)&MyFile_WriteBuffer, sizeof(MyFile_WriteBuffer), 100);
		}
		else
		{
			printf("文件写入失败，请检查SD卡或重新格式化!\r\n");
			f_close(&MyFile);	  //关闭文件	
			return ERROR;			
		}
		f_close(&MyFile);	  //关闭文件			
	}
	else
	{
		printf("无法打开/创建文件，请检查SD卡或重新格式化!\r\n");
		f_close(&MyFile);	  //关闭文件	
		return ERROR;		
	}
	
	printf("-------------FatFs 文件读取测试---------------\r\n");	
	
	BufferSize = sizeof(MyFile_WriteBuffer)/sizeof(BYTE);									// 计算写入的数据长度
	File_Res = f_open(&MyFile,"0:FatFs Test.txt",FA_OPEN_EXISTING | FA_READ);	//打开文件，若不存在则创建该文件
	File_Res = f_read(&MyFile,MyFile_ReadBuffer,BufferSize,&MyFile_Num);			// 读取文件
	if(File_Res == FR_OK)
	{
		printf("文件读取成功，正在校验数据...\r\n");
		
		for(i=0;i<BufferSize;i++)
		{
			if(MyFile_WriteBuffer[i] != MyFile_ReadBuffer[i])		// 校验数据
			{
				printf("校验失败，请检查SD卡或重新格式化!\r\n");
				f_close(&MyFile);	  //关闭文件	
				return ERROR;
			}
		}
        HAL_Delay(100);
		printf("校验成功，读出的数据为：\r\n");
		printf("%s\n",MyFile_ReadBuffer);
	}	
	else
	{
		printf("无法读取文件，请检查SD卡或重新格式化!\r\n");
		f_close(&MyFile);	  //关闭文件	
		return ERROR;		
	}	
	
	f_close(&MyFile);	  //关闭文件	
	return SUCCESS;
}
void FatFs_Check(void)	//判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
{
	BYTE work[_MAX_SS]; 
	
	FATFS_LinkDriver(&SD_Driver, SDPath);		// 初始化驱动
	File_Res = f_mount(&SD_FatFs,"0:",1);	//	挂载SD卡
	
	if (File_Res == FR_OK)	//判断是否挂载成功
	{
		printf("\r\nSD文件系统挂载成功\r\n");
	}
	else		
	{
		printf("SD卡还未创建文件系统，即将格式化\r\n");
		
		File_Res = f_mkfs("0:",FM_FAT32,0,work,sizeof work);		//格式化SD卡，FAT32，簇默认大小16K
		
		if (File_Res == FR_OK)		//判断是否格式化成功
			printf("SD卡格式化成功！\r\n");
		else
			printf("格式化失败，请检查或更换SD卡！\r\n");
	}
}
/*------------------------------------------功能函数-------------------------------------------------------------*/

/*
*********************************************************************************************************
* 函 数 名: ViewRootDir
* 功能说明: 显示 SD 卡根目录下的文件名
* 形 参：无
* 返 回 值: 无
*********************************************************************************************************
*/
extern SD_HandleTypeDef hsd1;
void ViewRootDir(void)
{
    FRESULT result;
    uint32_t cnt = 0;
    FILINFO fno,FileInf;
    char DiskPath[]="0:";
    DIR DirInf;
    /* 挂载文件系统 */
    result = f_mount(&SD_FatFs, DiskPath, 0); /* Mount a logical drive */
    if (result != FR_OK)
    {
        printf("挂载文件系统失败 (%s)\r\n", FR_Table[result]);
    }
    /* 打开根文件夹 */
    result = f_opendir(&DirInf, DiskPath); /* 如果不带参数，则从当前目录开始 */
    if (result != FR_OK)
    {
        printf("打开根目录失败 (%s)\r\n", FR_Table[result]);
        return;
    }
        printf("属性 | 文件大小 | 短文件名 | 长文件名\r\n");
    for (cnt = 0; ;cnt++)
    {
        result = f_readdir(&DirInf, &FileInf); /* 读取目录项，索引会自动下移 */
    if (result != FR_OK || FileInf.fname[0] == 0)
    {
        break;
    }
    if (FileInf.fname[0] == '.')
    {
    continue;
    }
    /* 判断是文件还是子目录 */
    if (FileInf.fattrib & AM_DIR)
    {
        printf("(0x%02d)目录 ", FileInf.fattrib);
    }
    else
    {
        printf("(0x%02d)文件 ", FileInf.fattrib);
    }
    f_stat(FileInf.fname, &fno);
    /* 打印文件大小, 最大 4G */
    printf(" %10d", (int)fno.fsize);
    printf(" %s\r\n", (char *)FileInf.fname); /* 长文件名 */
    }
    /* 打印卡速度信息 */
    if(hsd1.SdCard.CardSpeed == CARD_NORMAL_SPEED)
    {
        printf("Normal Speed Card <12.5MB/S, MAX Clock < 25MHz, Spec Version 1.01\r\n");
    }
    else if (hsd1.SdCard.CardSpeed == CARD_HIGH_SPEED)
    {
        printf("High Speed Card <25MB/s, MAX Clock < 50MHz, Spec Version 2.00\r\n");
    }
    else if (hsd1.SdCard.CardSpeed == CARD_ULTRA_HIGH_SPEED)
    {
        printf("UHS-I SD Card <50MB/S for SDR50, DDR50 Cards, MAX Clock < 50MHz OR 100MHz\r\n");
        printf("UHS-I SD Card <104MB/S for SDR104, MAX Clock < 108MHz, Spec version 3.01\r\n");
    }
    /* 卸载文件系统 */
    f_mount(NULL, DiskPath, 0);
}


