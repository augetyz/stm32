#include "sdbsp.h"
#include "sdmmc.h"
#include <stdio.h>

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



/**
 * @brief       读SD卡数据
 * @param       buf:读数据缓存区
 * @param       sector:扇区地址
 * @param       cnt:扇区个数
 * @retval      返回值:0,正常;其他,错误;
 */
uint8_t sd_read_disk(uint8_t* buf, uint32_t sector, uint32_t cnt)
{
    uint8_t sta = HAL_OK;
    uint32_t timeout = SD_TIMEOUT;
    long long lsector = sector;
//    INTX_DISABLE();  /* 关闭总中断(POLLING模式,严禁中断打断SDIO读写操作!!!) */
    
    __set_PRIMASK(1);/* 禁止全局中断 */
    sta = HAL_SD_ReadBlocks(&hsd1, (uint8_t*)buf,lsector, cnt, 
    SD_TIMEOUT); /* 多个sector的读操作 */
    /* 等待SD卡读完 */
    /* 等待SD卡写完 */
    while (HAL_SD_GetCardState(&hsd1) != HAL_SD_CARD_TRANSFER)
    {
        if (timeout-- == 0)
        {
            sta = 1;
            break;
        }
    }
//   INTX_ENABLE();  /* 开启总中断 */
    __set_PRIMASK(0);/* 使能全局中断 */
    return sta;
}
/**
 * @brief       写数据到SD卡
 * @param       buf:写数据缓存区
 * @param       sector:扇区地址
 * @param       cnt:扇区个数
 * @retval      返回值:0,正常;其他,错误;
 */
uint8_t sd_write_disk(uint8_t *buf, uint32_t sector, uint32_t cnt)
{
    uint8_t sta = HAL_OK;
    uint32_t timeout = SD_TIMEOUT;
    long long lsector = sector;
    __set_PRIMASK(1);/* 禁止全局中断 */
    sta = HAL_SD_WriteBlocks(&hsd1, (uint8_t*)buf, lsector, cnt, 
    SD_TIMEOUT); /* 多个sector的写操作 */
        
    /* 等待SD卡写完 */
    while (HAL_SD_GetCardState(&hsd1) != HAL_SD_CARD_TRANSFER)
    {
        if (timeout-- == 0)
        {
            sta = 1;
            break;
        }
    }
    __set_PRIMASK(0);/* 使能全局中断 */
    return sta;
}

