/**
  ******************************************************************************
  * @file    stm32100e_eval_fsmc_onenand.c
  * @author  MCD Application Team
  * @version V4.3.0
  * @date    10/15/2010
  * @brief   This file provides a set of functions needed to drive the
  *          KFG1216x2A-xxB5 OneNAND memory mounted on STM32100E-EVAL board.
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
#include "stm32100e_eval_fsmc_onenand.h"

/** @addtogroup Utilities
  * @{
  */
  
/** @addtogroup STM32_EVAL
  * @{
  */ 

/** @addtogroup STM32100E_EVAL
  * @{
  */
  
/** @addtogroup STM32100E_EVAL_FSMC_ONENAND
  * @brief      This file provides a set of functions needed to drive the
  *             KFG1216x2A-xxB5 OneNAND memory mounted on STM32100E-EVAL board.
  * @{
  */ 

/** @defgroup STM32100E_EVAL_FSMC_ONENAND_Private_Types
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32100E_EVAL_FSMC_ONENAND_Private_Defines
  * @{
  */ 
#define Bank1_NOR1_ADDR               ((uint32_t)0x60000000)
#define ONENAND_BOOTPARTITION_ADDR    ((uint32_t)Bank1_NOR1_ADDR)

 
/**
  * @}
  */ 

/** @defgroup STM32100E_EVAL_FSMC_ONENAND_Private_Macros
  * @{
  */
#define ADDR_SHIFT(A) (Bank1_NOR1_ADDR + (2 * (A)))
#define OneNAND_WRITE(Address, Data)  (*(__IO uint16_t *)(Address) = (Data))
  
/**
  * @}
  */ 
  

/** @defgroup STM32100E_EVAL_FSMC_ONENAND_Private_Variables
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32100E_EVAL_FSMC_ONENAND_Private_Function_Prototypes
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32100E_EVAL_FSMC_ONENAND_Private_Functions
  * @{
  */ 

/**
  * @brief  Configures the FSMC and GPIOs to interface with the OneNAND memory.
  *         This function must be called before any write/read operation on the 
  *         OneNAND.
  * @param  None
  * @retval None
  */
void OneNAND_Init(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;
  GPIO_InitTypeDef GPIO_InitStructure;


  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE); 
  
/*-- GPIO Configuration ------------------------------------------------------*/
  /* OneNAND Data lines configuration */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOE |
                         RCC_APB2Periph_GPIOF, ENABLE);
  
/*-- GPIO Configuration ------------------------------------------------------*/
  /*!< OneNAND Data lines configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 |
                                GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure); 
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  /*!< OneNAND Address lines configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
                                GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 | 
                                GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
                                GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
     
  /*!< CLK, NOE and NWE configuration */  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  /*!< NE1 configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /*!< NL configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  /*!< NWAIT configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_Init(GPIOD, &GPIO_InitStructure);
    
  /*-- FSMC Configuration ----------------------------------------------------*/
  p.FSMC_AddressSetupTime = 0x01;
  p.FSMC_AddressHoldTime = 0x00;
  p.FSMC_DataSetupTime = 0x04;
  p.FSMC_BusTurnAroundDuration = 0x01;
  p.FSMC_CLKDivision = 0x1;
  p.FSMC_DataLatency = 0x00;
  p.FSMC_AccessMode = FSMC_AccessMode_B;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Enable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;	
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

/**
  * @brief  Reads OneNAND memory's Manufacturer and Device Code.
  * @param  OneNAND_ID: pointer to a OneNAND_IDTypeDef structure which will hold
  *         the Manufacturer and Device Code.  
  * @retval None
  */
void OneNAND_ReadID(OneNAND_IDTypeDef* OneNAND_ID)
{
  /* Read ID command */
  OneNAND_WRITE(Bank1_NOR1_ADDR + OneNAND_REG_COMMAND, OneNAND_CMD_READ_ID);

  /* Read ID data */
  OneNAND_ID->Manufacturer_ID = *(__IO uint16_t *)(Bank1_NOR1_ADDR + OneNAND_REG_MANUFACTERID);
  OneNAND_ID->Device_ID = *(__IO uint16_t *)(Bank1_NOR1_ADDR + OneNAND_REG_DEVICEID);
}

/**
  * @brief  Reads the OneNAND memory status. 
  * @param  None
  * @retval OneNAND Status
  */
uint16_t OneNAND_ReadStatus(void)
{
__IO uint16_t status = 0x0;

  /* Read Status */
  return (status = *(__IO uint16_t *)(Bank1_NOR1_ADDR + OneNAND_REG_INTERRUPT));
}

/**
  * @brief  Reads the OneNAND Controller status 
  * @param  None
  * @retval OneNAND Controller Status
  */
uint16_t OneNAND_ReadControllerStatus(void)
{
__IO uint16_t status = 0x0;

  /* Read Controller Status */
  return (status = *(__IO uint16_t *)(Bank1_NOR1_ADDR + OneNAND_REG_CONTROLSTATUS));
}

/**
  * @brief  Erases the specified OneNAND memory block.
  * @param  None
  * @retval The returned value can be: OneNAND_SUCCESS, OneNAND_ERROR
*           or OneNAND_TIMEOUT
  */
uint16_t OneNAND_EraseBlock(uint32_t BlockAddr)
{
  uint16_t status = 0;

  /* Erase operation*/
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + 0xF100*2) = BlockAddr;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + 0xF241*2) = 0x0000;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + 0xF220*2) = 0x0094; 

  status = *(__IO uint16_t *)(Bank1_NOR1_ADDR + 0xF241*2);

  while((status & 0x8000) != 0x8000)
  {
    status = *(__IO uint16_t *)(Bank1_NOR1_ADDR + 0xF241*2);
  }
 
  return (status);
}

/**
  * @brief  Resets the OneNAND memory
  * @param  None
  * @retval None
  */
void OneNAND_Reset(void)
{
  OneNAND_WRITE(ONENAND_BOOTPARTITION_ADDR + OneNAND_REG_COMMAND, OneNAND_CMD_RESET);
}

/**
  * @brief  Unlocks the OneNAND memory
  * @param  None
  * @retval None
  */
uint16_t OneNAND_Unlock(void)
{
  uint16_t  status = 0;

  /* Unlock sequence */
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + 0xF100*2) = 0x0001;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + 0xF241*2) = 0x0000;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + 0xF220*2) = 0x0023;

  status = *(__IO uint16_t *)(Bank1_NOR1_ADDR + 0xF241*2);

  while((status & 0x8000) != 0x8000)
  {
    status = *(__IO uint16_t *)(Bank1_NOR1_ADDR + 0xF241*2);
  }
  return (status);
}
/**
  * @brief  Writes a Half-word buffer to the OneNAND memory. 
  * @param  pBuffer : pointer to buffer. 
  * @param  WriteAddr : OneNAND memory internal address from which the data will be 
  *         written.
  * @param  NumHalfwordToWrite : number of half-words to write. 
  * @retval None
  */
uint16_t OneNAND_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{
  uint32_t datacounter = 0;
  uint16_t status = 0;

  for(datacounter = 0; datacounter < NumHalfwordToWrite; datacounter++)
  {
    *(__IO uint16_t *)((Bank1_NOR1_ADDR + WriteAddr) + (2*datacounter)) = pBuffer[datacounter];
  } 
 /* write operation */ 
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF100*2)) = 0x0001;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF107*2)) = 0x0801;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF241*2)) = 0x0000;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF220*2)) = 0x0080; 

  status = *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF241*2));

  while((status & 0x8000) != 0x8000)
  {
    status = *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF241*2));
  }

  /* Load operation */
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF100*2)) = 0x0000;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF107*2)) = 0x0000;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF200*2)) = 0x0000;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF101*2)) = 0x0000;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF241*2)) = 0x0000;
  *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF220*2)) = 0x0000; 

  status = *(__IO uint16_t *)(Bank1_NOR1_ADDR + (0xF241*2));

  while((status & 0x8000) != 0x8000)
  {
    status = *(__IO uint16_t *)(0x60000000 + (0xF241*2));
  }
  return (status);
}

/**
  * @brief  Reads a block of data from the OneNAND memory.
  * @param  pBuffer : pointer to the buffer that receives the data read from the 
  *         OneNAND memory.
  * @param  ReadAddr : OneNAND memory internal address to read from.
  * @param  NumHalfwordToRead : number of half-words to read.
  * @retval None
  */
void OneNAND_AsynchronousRead(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead)
{
  uint16_t datatmp = 0x0;
  datatmp = *(__IO uint16_t *)(Bank1_NOR1_ADDR + OneNAND_REG_SYSTEMCONFIGURATION); 
  /* Set the asynchronous read mode */
  OneNAND_WRITE(Bank1_NOR1_ADDR + OneNAND_REG_SYSTEMCONFIGURATION, ( datatmp& 0x7FFF));

  /* Read data */
  for(; NumHalfwordToRead != 0x00; NumHalfwordToRead--) /* while there is data to read */
  {
    /* Read a Halfword from the memory */
    *pBuffer++ = *(__IO uint16_t *)((Bank1_NOR1_ADDR + ReadAddr));
    ReadAddr = ReadAddr + 2; 
  }  
}

/**
  * @brief  Reads a block of data from the OneNAND memory.
  * @param  pBuffer : pointer to the buffer that receives the data read from the 
  *         OneNAND memory.
  * @param  ReadAddr : OneNAND memory internal address to read from.
  * @param  NumHalfwordToRead : number of half-words to read.
  * @retval None
  */
void OneNAND_SynchronousRead(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead)
{
  uint16_t datatmp = 0x0;
  datatmp = *(__IO uint16_t *)(Bank1_NOR1_ADDR + OneNAND_REG_SYSTEMCONFIGURATION); 
  /* Set the asynchronous read mode */
  OneNAND_WRITE(Bank1_NOR1_ADDR + OneNAND_REG_SYSTEMCONFIGURATION, (datatmp|0x8000));

  /* Read data */
  for(; NumHalfwordToRead != 0x00; NumHalfwordToRead--) /* while there is data to read */
  {
    /* Read a Halfword from the memory */
    *pBuffer++ = *(__IO uint16_t *)((Bank1_NOR1_ADDR + ReadAddr));
    ReadAddr = ReadAddr + 2; 
  }  
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */  

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
