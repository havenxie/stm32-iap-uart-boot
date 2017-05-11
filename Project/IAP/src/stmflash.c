#include "stmflash.h"

/**
  * @brief  Read half words (16-bit data) of the specified address
  * @note   This function can be used for all STM32F10x devices.
  * @param  faddr: The address to be read (the multiple of the address, which is 2)
  * @retval Value of specified address
  */
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}


/**
  * @brief  There is no check writing.
  * @note   This function can be used for all STM32F10x devices.
  * @param  WriteAddr: The starting address to be written.
  * @param  pBuffer: The pointer to the data.
  * @param  NumToWrite:  The number of half words written
  * @retval None
  */
static void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//add addr 2.
	}  
} 

u16 STMFLASH_BUF[PAGE_SIZE / 2];//Up to 2K bytes

/**
  * @brief  Write data from the specified address to the specified length.
  * @note   This function can be used for all STM32F10x devices.
  * @param  WriteAddr: The starting address to be written.(The address must be a multiple of two)
  * @param  pBuffer: The pointer to the data.
  * @param  NumToWrite:  The number of half words written
  * @retval None
  */
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //扇区地址
	u16 secoff;	   //扇区内偏移地址(16位字计算)
	u16 secremain; //扇区内剩余地址(16位字计算)	   
 	u16 i;    
	u32 offaddr;   //去掉0X08000000后的地址
	if((WriteAddr < FLASH_BASE) || (WriteAddr >= FLASH_BASE + 1024 * FLASH_SIZE))return;//非法地址
	FLASH_Unlock();						//解锁
	offaddr = WriteAddr - FLASH_BASE;		//实际偏移地址.
	secpos = offaddr / PAGE_SIZE;			//扇区地址  0~127 for STM32F103RBT6
	secoff = (offaddr % PAGE_SIZE) / 2;		//在扇区内的偏移(2个字节为基本单位.)
	secremain = PAGE_SIZE / 2 - secoff;		//扇区剩余空间大小   
	if(NumToWrite <= secremain)
		secremain = NumToWrite;//不大于该扇区范围
	while(1) 
	{	
		STMFLASH_Read(secpos * PAGE_SIZE + FLASH_BASE, STMFLASH_BUF, PAGE_SIZE / 2);//读出整个扇区的内容
		for(i = 0; i < secremain; i++)//校验数据
		{
			if(STMFLASH_BUF[secoff + i] != 0XFFFF)break;//需要擦除  	  
		}
		if(i < secremain)//需要擦除
		{
			FLASH_ErasePage(secpos * PAGE_SIZE + FLASH_BASE);//擦除这个扇区
			for(i=0; i < secremain; i++)
			{
				STMFLASH_BUF[i + secoff] = pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos * PAGE_SIZE + FLASH_BASE, STMFLASH_BUF, PAGE_SIZE / 2);//写入整个扇区  
		}else 
			STMFLASH_Write_NoCheck(WriteAddr, pBuffer, secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(NumToWrite == secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;				//扇区地址增1
			secoff = 0;				//偏移位置为0 	 
		   	pBuffer += secremain;  	//指针偏移
			WriteAddr += secremain;	//写地址偏移	   
		   	NumToWrite -= secremain;	//字节(16位)数递减
			if(NumToWrite > (PAGE_SIZE / 2)) secremain = PAGE_SIZE / 2;//下一个扇区还是写不完
			else secremain = NumToWrite;//下一个扇区可以写完了
		}	 
	};	
	FLASH_Lock();//上锁
}

/**
  * @brief  Start reading the specified data from the specified address.
  * @note   This function can be used for all STM32F10x devices.
  * @param  ReadAddr: Start addr
  * @param  pBuffer: The pointer to the data.
  * @param  NumToWrite:  The number of half words written(16bit)
  * @retval None
  */
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//读取2个字节.
		ReadAddr+=2;//偏移2个字节.	
	}
}

void IAP_FLASH_WriteFlag(u16 flag) 
{
	STMFLASH_Write(IAP_FLASH_FLAG_ADDR, &flag, 1);
}

void IAP_FLASH_ReadFlag(u16 *pData)
{
	STMFLASH_Read(IAP_FLASH_FLAG_ADDR, pData, 1);   
}














