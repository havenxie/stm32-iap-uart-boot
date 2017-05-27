/**
  ******************************************************************************
  * @file    IAP/src/main.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    10/15/2010
  * @brief   Main program body
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 


/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "iap.h"


int main(void)
{
	uint16_t flash_flag = 0;  
	/* Initialize USART*/
	IAP_USART_Init();
	
	while(1)
	{
		flash_flag = IAP_FLASH_ReadFlag();
		switch(flash_flag)
		{
			case APPRUN_FLAG_DATA://jump to app
				IAP_Jump_To_Application();
				break;
			case INIT_FLAG_DATA://initialze state (blank mcu)
				Main_Menu();
				break;
			case DOWNLOAD_FLAG_DATA:// download app state
				/* Download user application in the Flash */
				if(SerialDownload() == 0) //download completed
				{
					IAP_FLASH_WriteFlag(APPRUN_FLAG_DATA); 
				}
				break;
			case UPLOAD_FLAG_DATA:// upload app state
				/* Upload user application from the Flash */
				SerialUpload();
				IAP_FLASH_WriteFlag(APPRUN_FLAG_DATA);
				break;
			case ERASE_FLAG_DATA:// erase app state
				//todo
				EraseSomePages(FLASH_IMAGE_SIZE);
				IAP_FLASH_WriteFlag(INIT_FLAG_DATA);			
				break;
			default:
				break;
		}
	}
}


