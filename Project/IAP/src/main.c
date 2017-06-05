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
	int8_t execute_res = 1;
	uint8_t erase_cont[3] = {0};
	/* Initialize USART*/
	IAP_USART_Init();
	
	while(1)
	{
		execute_res = 1;
		flash_flag = IAP_FLASH_ReadFlag();
		switch(flash_flag)
		{
			case APPRUN_FLAG_DATA://jump to app
				execute_res = IAP_Jump_To_Application();
				if(execute_res != 0)
					IAP_FLASH_WriteFlag(INIT_FLAG_DATA);
				break;
			case INIT_FLAG_DATA://initialze state (blank mcu)
				Main_Menu();
				break;
			case UPDATE_FLAG_DATA:// download app state
				execute_res = SerialDownload();				
				if(execute_res == 0) 
					IAP_FLASH_WriteFlag(APPRUN_FLAG_DATA);
				else
					IAP_FLASH_WriteFlag(INIT_FLAG_DATA);
				break;
			case UPLOAD_FLAG_DATA:// upload app state
				execute_res = SerialUpload();
				if(execute_res == 0)
					IAP_FLASH_WriteFlag(APPRUN_FLAG_DATA);
				else 
					IAP_FLASH_WriteFlag(INIT_FLAG_DATA);
				break;
			case ERASE_FLAG_DATA:// erase app state
				Int2Str(erase_cont, FLASH_IMAGE_SIZE / PAGE_SIZE);
				SerialPutString("@");
				SerialPutString(erase_cont);
				SerialPutString("@");
				EraseSomePages(FLASH_IMAGE_SIZE, 1);
				IAP_FLASH_WriteFlag(INIT_FLAG_DATA);
				break;
			default:
				break;
		}
	}
}


