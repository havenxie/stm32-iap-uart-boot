/**
  ******************************************************************************
  * @file    stm32100e_eval_fsmc_onenand.h
  * @author  MCD Application Team
  * @version V4.3.0
  * @date    10/15/2010
  * @brief   This file contains all the functions prototypes for the 
  *          stm32100e_eval_fsmc_onenand firmware driver.
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
   
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32100E_EVAL_FSMC_ONENAND_H
#define __STM32100E_EVAL_FSMC_ONENAND_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

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
  * @{
  */  

/** @defgroup STM32100E_EVAL_FSMC_ONENAND_Exported_Types
  * @{
  */
  typedef struct
{
  uint16_t Manufacturer_ID;
  uint16_t Device_ID;
}OneNAND_IDTypeDef;

/* OneNand Status */
typedef enum
{
  OneNAND_SUCCESS = 0,
  OneNAND_ONGOING,
  OneNAND_ERROR,
  OneNAND_TIMEOUT
}OneNAND_Status;
 
/**
  * @}
  */
  
/** @defgroup STM32100E_EVAL_FSMC_ONENAND_Exported_Constants
  * @{
  */
/** 
  * @brief  OneNAND memory command  
  */  
#define OneNAND_CMD_ERASE                            0x0094
#define OneNAND_CMD_MULTIPLE_ERASE                   0x0095
#define OneNAND_CMD_ERASE_MULTI_BLOCK_VERIFY_READ    0x0071
#define OneNAND_CMD_PROGRAM                          0x001A
#define OneNAND_CMD_RESET                            0x00F0
#define OneNAND_CMD_READ_ID                          0x0090

/** 
  * @brief OneNand Register description  
  */  
#define OneNAND_REG_MANUFACTERID             ((uint32_t)0x1E000) /* Manufacturer identification */
#define OneNAND_REG_DEVICEID                 ((uint32_t)0x1E002) /* Device identification */
#define OneNAND_REG_DATABUFFERSIZE           ((uint32_t)0x1E006) /* Data Buffer size */
#define OneNAND_REG_BOOTBUFFERSIZE           ((uint32_t)0x1E008) /* Boot Buffer size */
#define OneNAND_REG_AMOUNTOFBUFFERS          ((uint32_t)0x1E00A) /* Amount of data/boot buffers */
#define OneNAND_REG_TECHNOLOGY               ((uint32_t)0x1E00C) /* Info about technology */
#define OneNAND_REG_STARTADDRESS1            ((uint32_t)0x1E200) /* Nand Flash Block Address */
#define OneNAND_REG_STARTADDRESS3            ((uint32_t)0x1E204) /* Destination Block address for copy back program */
#define OneNAND_REG_STARTADDRESS4            ((uint32_t)0x1E206) /* Destination Page & sector address for copy back program */
#define OneNAND_REG_STARTADDRESINT8_T        ((uint32_t)0x1E20E) /* Nand Flash Page & sector address */
#define OneNAND_REG_STARTBUFFER              ((uint32_t)0x1E400) /* The meaning is with which buffer to start and how many
                                                                     buffers to use for the data transfer */
#define OneNAND_REG_COMMAND                  ((uint32_t)0x1E440) /* Host control and memory operation commands*/
#define OneNAND_REG_SYSTEMCONFIGURATION      ((uint32_t)0x1E442) /* Memory and host interface configuration */
#define OneNAND_REG_CONTROLSTATUS            ((uint32_t)0x1E480) /* Control status and result of memory operation */
#define OneNAND_REG_INTERRUPT                ((uint32_t)0x1E482) /* Memory Command Completion Interrupt Status */
#define OneNAND_REG_STARTBLOCKADDRESS        ((uint32_t)0x1E498) /* Start memory block address in Write Protection mode */
#define OneNAND_REG_WRITEPROTECTIONSTATUS    ((uint32_t)0x1E49C) /* Current memory Write Protection status */
#define OneNAND_REG_ECCSTATUS                ((uint32_t)0x1FE00) /* ECC status of sector */
#define OneNAND_REG_ECCMAINAREA1             ((uint32_t)0x1FE02) /* ECC error position of Main area data  error 
                                                                     for first selected sector */
#define OneNAND_REG_ECCSPAREAREA1            ((uint32_t)0x1FE04) /* ECC error position of Spare area data error 
                                                                     for first selected Sector */
#define OneNAND_REG_ECCMAINAREA2             ((uint32_t)0x1FE06) /* ECC error position of Main area data  error 
                                                                     for second selected sector */
#define OneNAND_REG_ECCSPAREAREA2            ((uint32_t)0x1FE08) /* ECC error position of Spare area data error 
                                                                     for second selected Sector */
#define OneNAND_REG_ECCMAINAREA3             ((uint32_t)0x1FE0A) /* ECC error position of Main area data  error 
                                                                     for third selected sector */
#define OneNAND_REG_ECCSPAREAREA3            ((uint32_t)0x1FE0C) /* ECC error position of Spare area data error 
                                                                     for third selected Sector */
#define OneNAND_REG_ECCMAINAREA4             ((uint32_t)0x1FE0E) /* ECC error position of Main area data  error 
                                                                     for fourth selected sector */
#define OneNAND_REG_ECCSPAREAREA4            ((uint32_t)0x1FE10) /* ECC error position of Spare area data error 
                                                                     for fourth selected Sector */

/**
  * @}
  */ 
  
/** @defgroup STM32100E_EVAL_FSMC_ONENAND_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32100E_EVAL_FSMC_ONENAND_Exported_Functions
  * @{
  */ 
void OneNAND_Init(void);
void OneNAND_ReadID(OneNAND_IDTypeDef* OneNAND_ID);
uint16_t OneNAND_ReadStatus(void);
uint16_t OneNAND_ReadControllerStatus(void);
uint16_t OneNAND_EraseBlock(uint32_t BlockAddr);
void OneNAND_Reset(void);
uint16_t OneNAND_Unlock(void);
uint16_t OneNAND_WriteBuffer(uint16_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite);
void OneNAND_AsynchronousRead(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead);
void OneNAND_SynchronousRead(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead);

#ifdef __cplusplus
}
#endif

#endif /* __STM32100E_EVAL_FSMC_ONENAND_H */
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
