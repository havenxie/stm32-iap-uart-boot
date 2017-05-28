#ifndef __IAP_H__
#define __IAP_H__
#include "stm32f10x.h"
#include "download.h"
#include "upload.h"

/* Exported types ------------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Exported constants --------------------------------------------------------*/
/* Constants used by Serial Command Line Mode */






extern pFunction Jump_To_Application;
extern uint32_t JumpAddress;

extern void FLASH_DisableWriteProtectionPages(void);
extern int8_t IAP_Jump_To_Application(void);
extern void IAP_USART_Init(void);
extern void Main_Menu(void);
extern void IAP_FLASH_WriteFlag(uint16_t flag);
extern uint16_t IAP_FLASH_ReadFlag(void);

#endif
