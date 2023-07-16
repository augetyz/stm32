#ifndef __SD_USE_H_
#define __SD_USE_H_

#include "main.h"
#include "fatfs.h"


void show_sdcard_info(SD_HandleTypeDef hsd);
void FatFs_Check(void);				// 判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
void FatFs_GetVolume(void);		// 计算设备容量
uint8_t  FatFs_FileTest(void);	// 文件创建和写入测试
void ViewRootDir(void);//显示 SD 卡根目录下的文件名
#endif

