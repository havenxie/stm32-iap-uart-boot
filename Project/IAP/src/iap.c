#include "iap_config.h"
#include "iap.h"
#include "stmflash.h"
#include "ymodem.h"

pFunction Jump_To_Application;
uint32_t JumpAddress;
uint32_t BlockNbr = 0, UserMemoryMask = 0;
__IO uint32_t FlashProtection = 0;


void IAP_FLASH_WriteFlag(uint16_t flag) 
{
	FLASH_Unlock();
	STMFLASH_Write(IAP_FLASH_FLAG_ADDR, &flag, 1);
	FLASH_Lock();
}

uint16_t IAP_FLASH_ReadFlag(void)
{
	return STMFLASH_ReadHalfWord(0x8002800);   
}


/**
  * @brief  Disable the write protection of desired pages
  * @param  None
  * @retval None
  */
void FLASH_DisableWriteProtectionPages(void)
{
	uint32_t useroptionbyte = 0, WRPR = 0;
	uint16_t var1 = OB_IWDG_SW, var2 = OB_STOP_NoRST, var3 = OB_STDBY_NoRST;
	FLASH_Status status = FLASH_BUSY;

	WRPR = FLASH_GetWriteProtectionOptionByte();

	/* Test if user memory is write protected */
	if ((WRPR & UserMemoryMask) != UserMemoryMask)
	{
		useroptionbyte = FLASH_GetUserOptionByte();

		UserMemoryMask |= WRPR;

		status = FLASH_EraseOptionBytes();

		if (UserMemoryMask != 0xFFFFFFFF)
		{
			status = FLASH_EnableWriteProtection((uint32_t)~UserMemoryMask);
		}

		/* Test if user Option Bytes are programmed */
		if ((useroptionbyte & 0x07) != 0x07)
		{ 
			/* Restore user Option Bytes */
			if ((useroptionbyte & 0x01) == 0x0)
			{
				var1 = OB_IWDG_HW;
			}
			if ((useroptionbyte & 0x02) == 0x0)
			{
				var2 = OB_STOP_RST;
			}
			if ((useroptionbyte & 0x04) == 0x0)
			{
				var3 = OB_STDBY_RST;
			}
			FLASH_UserOptionByteConfig(var1, var2, var3);
		}

		if (status == FLASH_COMPLETE)
		{
			SerialPutString("Write Protection disabled...\r\n");

			SerialPutString("...and a System Reset will be generated to re-load the new option bytes\r\n");

			/* Generate System Reset to load the new option byte values */
			NVIC_SystemReset();
		}
		else
		{
			SerialPutString("Error: Flash write unprotection failed...\r\n");
		}
	}
	else
	{
		SerialPutString("Flash memory not write protected\r\n");
	}
}

/**
  * @brief  Initialize the ssart: Configure RCC, USART and GPIOs.
  * @param  None
  * @retval None
  */
void IAP_USART_Init(void)
{
 USART_InitTypeDef USART_InitStructure;

  /* USART resources configuration (Clock, GPIO pins and USART registers) ----*/
  /* USART configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  STM_EVAL_COMInit(COM1, &USART_InitStructure);  
}


/**
  * @brief  Jump to user application
  * @param  None
  * @retval None
  */
int8_t IAP_Jump_To_Application(void)
{
	/* Test if user code is programmed starting from address "ApplicationAddress" */
	if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
	{   
		SerialPutString("Jump to user app.\r\n\n");
		/* Jump to user application */
		JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
		Jump_To_Application = (pFunction) JumpAddress;
		/* Initialize user application's Stack Pointer */
		__set_MSP(*(__IO uint32_t*) ApplicationAddress);
		Jump_To_Application();
		return 0;
	}
	else
	{
		SerialPutString("Jump to user app error.\r\n\n");
		return -1;
	}
}


/**
  * @brief  Display the Main Menu on to HyperTerminal
  * @param  None
  * @retval None
  */
void Main_Menu(void)
{
	//uint8_t *cmdStr = (uint8_t *)malloc(sizeof(uint8_t)*(CMD_STRING_SIZE + 1));
	uint8_t cmdStr[CMD_STRING_SIZE] = {0};
	/* Get the number of block (4 or 2 pages) from where the user program will be loaded */
	BlockNbr = (FlashDestination - 0x08000000) >> 12;
	
	/* Compute the mask to test if the Flash memory, where the user program will be
	loaded, is write protected */
#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
  UserMemoryMask = ((uint32_t)~((1 << BlockNbr) - 1));
#else /* USE_STM3210E_EVAL */
  if (BlockNbr < 62)
  {
    UserMemoryMask = ((uint32_t)~((1 << BlockNbr) - 1));
  }
  else
  {
    UserMemoryMask = ((uint32_t)0x80000000);
  }
#endif /* (STM32F10X_MD) || (STM32F10X_MD_VL) */

	/* Test if any page of Flash memory where program user will be loaded is write protected */
	if ((FLASH_GetWriteProtectionOptionByte() & UserMemoryMask) != UserMemoryMask)
	{
		FlashProtection = 1;
	}
	else
	{
		FlashProtection = 0;
	}

	while (1)
	{
		SerialPutString("\r\nIn-Application Programming Application(V 3.3.0) \r\n\n");
		SerialPutString("Upload Image To the Internal Flash   ----> update\r\n\n");
		SerialPutString("Upload Image From the Internal Flash ----> upload\r\n\n");
		SerialPutString("Erase Image From the app region      ----> erase \r\n\n");
		SerialPutString("Jump To The New Program and Run      ----> runapp\r\n\n");
		if(FlashProtection != 0)//There is write protected
		{
			SerialPutString("Disable the write protection --------------------> cmd_diswp\r\n\n");
		}
		SerialPutString("==========================================================\r\n\n");
		
		SerialPutString("cmd>");
		
		GetInputString(cmdStr);
		
		if(strcmp((char *)cmdStr, CMD_UPDATE_STR) == 0)
		{
			IAP_FLASH_WriteFlag(UPDATE_FLAG_DATA);
			return;
		}
		else if(strcmp((char *)cmdStr, CMD_UPLOAD_STR) == 0)
		{
			IAP_FLASH_WriteFlag(UPLOAD_FLAG_DATA);
			return;
		}
		else if(strcmp((char *)cmdStr, CMD_ERASE_STR) == 0)
		{
			IAP_FLASH_WriteFlag(ERASE_FLAG_DATA);
			return;
		}
		else if(strcmp((char *)cmdStr, CMD_RUNAPP_STR) == 0)
		{
			IAP_FLASH_WriteFlag(APPRUN_FLAG_DATA);
			return;
		}
		else if(strcmp((char *)cmdStr, CMD_ERROR_STR) == 0)
		{
			SerialPutString("Invalid CMD !\r\n\n");
		}
		else
		{
			SerialPutString("Invalid CMD !\r\n\n");
		}
		
	}
	//free(cmdStr);
}
