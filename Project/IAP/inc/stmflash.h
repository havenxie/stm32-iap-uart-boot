#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "stm32f10x.h"
#include "stm32f10x_flash.h"
#include "common.h"

#ifndef PAGE_SIZE//common.h文件中没有完善
  #define PAGE_SIZE                         (0x400)    /* 1 Kbyte */
  #define FLASH_SIZE                        (0x10000)  /* 64 KBytes */
#endif


extern u16 STMFLASH_ReadHalfWord(u32 faddr);		  //读出半字  
extern void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//从指定地址开始写入指定长度的数据
extern void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//从指定地址开始读出指定长度的数据								   
extern void IAP_FLASH_WriteFlag(u16 flag);
extern uint16_t IAP_FLASH_ReadFlag(void);
#endif

















