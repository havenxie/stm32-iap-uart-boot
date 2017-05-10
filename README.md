*****

## 说明

1. 这个项目包含一套源代码和预先配置好的工程文件，该项目实现对STM32系列的MCU通过串口进行IAP。

2. 本套代码可运行在：STM32F10x的CL系列、XL系列、HD系列、HD_VL系列、MD系列、MD_VL系列、LD系列、LD_VL系列。
	
3. 这套代码已经在：STM3210C-EVAL (CL)、STM3210E-EVAL-XL (XL)、STM3210E-EVAL (HD)、STM32100E-EVAL(HD_VL)、STM3210B-EVAL (MD)、STM32100B-EVAL (MD_VL) 平台上验证过了。几乎不用移植就可以用在你的项目上。只要修改stm32_eval.h文件中相应注释。

*****

## STM32型号分类简介：

### STM32产品型号分类：

- cl：互联型产品，stm32f105xx/107xx系列
- vl：超值型产品，stm32f100系列
- ld：低密度产品，FLASH = 16K/32K
- md：中等密度产品，FLASH = 64K/128k
- hd：高密度产品，FLASH = 256K/384K/512K
- xl：超高密度产品，FLASH = 768K/1024K(stm32f101/103)

###	STM32启动文件分类：
- startup_stm32f10x_cl.s：互联型的STM32F105xx，STM32F107xx
- startup_stm32f10x_ld.s：小容量的STM32F101xx，STM32F102xx，STM32F103xx
- startup_stm32f10x_ld_vl.s：小容量的STM32F100xx
- startup_stm32f10x_md.s：中容量的STM32F101xx，STM32F102xx，STM32F103xx
- startup_stm32f10x_md_vl.s：中容量的STM32F100xx
- startup_stm32f10x_hd.s：大容量的STM32F101xx，STM32F102xx，STM32F103xx
- startup_stm32f10x_hd_vl.s：大容量的STM32F100xx
- startup_stm32f10x_xl.s：超大容量FLASH在512K到1024K字节的STM32F101xx，STM32F102xx，STM32F103xx

### STM32产品FLASH标识：
- 8: 64K
- B: 128K
- C: 256K
- D: 384K
- E: 512K
- F: 768K
- G: 1024K

*****

## 工程目录结构 

- "IAP\Binary": 包含将hex文件转换成bin文件的工具

- "IAP\inc": 包含IAP固件的头文件
```
    IAP/inc/common.h            This file provides all the headers of the common functions.
    IAP/inc/ymodem.h            This file provides all the software function headers of the ymodem.c file.    
    IAP/inc/stm32f10x_conf.h    Library Configuration file
    IAP/inc/stm32f10x_it.h      Header for stm32f10x_it.c    
```

- "IAP\src": 包含IAP固件的源文件
```
    IAP/src/main.c              Main program
    IAP/src/stm32f10x_it.c      Interrupt handlers
    IAP/src/download.c          This file provides the firmware which allows to download an image to internal Flash.
    IAP/src/upload.c            This file provides the firmware which allows to upload an image from internal Flash. 
    IAP/src/common.c            This file provides all the common functions. 
    IAP/src/ymodem.c            This file provides all the firmware functions related to the ymodem protocol.
    IAP/src/system_stm32f10x.c  STM32F10x system source file
```              

 - "IAP\MDK-ARM": 包含KEIL开发工具的工程文件

 - "IAP\EWARM": 包含IAR开发工具的工程文件
 
      
***** 

## 加载运行IAP工程方法：

### MDK-ARM(Keil5平台):

1. 打开MDK-ARM文件夹下的IAP.uvproj工程
2. 在工具栏(Select Target)中选择工程配置:
    - STM32100E-EVAL: 配置成HD_VL设备
    - STM3210E-EVAL_XL: 配置成XL设备
    - STM32100B-EVAL: 配置成MD_VL设备    
    - STM3210C-EVAL: 配置成CL设备
    - STM3210B-EVAL: 配置成MD设备
    - STM3210E-EVAL: 配置成HD设备

3. 编译工程
4. 通过JLINK或者STlINK或者uart下载目标文件。
5. 运行。

### EWARM(IAR平台):步骤参考Keil

*****

## 超级终端配置：
    + 数据位长度 = 8 Bits
    + 1位停止位
    + 无校验位
    + 波特率 = 115200 baud
    + 硬件流控: None 

*****

### 使用方法： 

1. Generate a binary image for the pogram provided in the "Project\IAP\binary_template"
   directory. 
2. Program the internal Flash with the IAP (see below) 
3. Open HyperTerminal window using the settings already defined in section
   "Hardware environment" 
4. To run the IAP driver, keep the Key push-button pressed at Reset. 
   The IAP main menu is then displayed on the HyperTerminal window.
5. To download an application, press 1 and use the Ymodem protocol

*****

## 版本说明：
- level00: 官方版本首次跑通。