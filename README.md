**

## 说明

1. 该项目实现通过PC的串口对STM32系列MCU进行IAP。

2. 该项目包含三个部分（三套代码）：
    
    - 运行在STM32平台的Bootloader；
    - 运行在STM32平台的App(我做了两个，一个是支持usmart的重量版，一个是很简洁的轻量版)；
    - 运行在Windows平台的上位机操作工具。

3. 本篇是属于运行在STM32平台的Bootloader部分，另外两篇介绍请参阅：
    - [windows平台操作工具](https://github.com/havenxie/winapp-iap)
    - [STM32平台的APP(支持USMART的版本)](https://github.com/havenxie/stm32-iap-app)     [STM32平台的APP(轻量版)](https://github.com/havenxie/stm32-iap-app_lite)
    

4. 该部分作为Bootloader可运行在多个STM32F10x系列：
    
    CL系列、XL系列、HD系列、HD_VL系列、MD系列、MD_VL系列、LD系列、LD_VL系列。
	
5. 这套代码几乎不用移植就可以用在你的项目上。只需要简单的根据你的项目配置工程。

*****

## 准备工作：

> 在开始使用之前请详细阅读下面关于STM32系列分类的介绍。

### STM32产品型号分类：

- cl：互联型产品，stm32f105xx/107xx系列
- vl：超值型产品，stm32f100系列
- ld：低密度产品，FLASH = 16K/32K/没做
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

- "Binary": 包含将hex文件转换成bin文件的工具，你也可以不用这个工具，直接用Keil安装目录中的hex转bin工具。我在这里用了这个工具是因为每个人的安装目录不同，不可能做到一致，直接将转换工具放在项目中可以保证每个人都会有一致的效果。（这里我已经设置好了，使用者不必关心）

- "CORE": STM32的启动文件和内核文件

- "IAP": 实现IAP功能的主要函数都在这里
```
    inc/common.h          与硬件相关的配置及一些基础功能函数的头文件
    inc/iap.h             实现iap功能函数的头文件  
    inc/iap_config.h      IAP的配置文件（用户可以根据需求更改的文件）   
    inc/stmflash.h        内部flash操作的函数的头文件
    inc/ymodem.h          实现Ymodem协议的函数的头文件  

```

- "IAP\src": 包含IAP固件的源文件
```
    src/common.c          与硬件相关的一些基础功能函数
    src/iap.c             实现iap各种功能的函数  
    src/stmflash.c        内部flash操作的函数
    src/ymodem.c          实现Ymodem协议的函数 
```              

 - "MDK-ARM": KEIL的工程文件及user文件

 - "STM32F10X-FWLib": ST官方库文件

 - "keilkill": 用来清除中间文件的bat脚本，双击运行即可

 - "README": 自述文件
 
      
***** 

## 使用IAP工程的方法：

1. 打开MDK-ARM文件夹下的IAP.uvproj工程

2. 在工具栏(Select Target)中选择与你的硬件对应的型号:

    - STM32-IAP_MD_VL: 对应MD_VL设备    
    - STM32-IAP_HD_VL: 对应HD_VL设备
    - STM32-IAP_CL: 对应CL设备
    - STM32-IAP_MD: 对应MD设备
    - STM32-IAP_HD: 对应HD设备
    - STM32-IAP_XL: 对应XL设备

3. 在iap_config.h文件中设置你的用户应用程序(app)的起始地址ApplicationAddress（我这里是0x8003000) 。设置用来存储标志信息的flash地址IAP_FLASH_FLAG_ADDR（我这里的是0x8002800，即0X8003000-2KByte）

4. 在option->target->1ROM中设置bootloader的起始地址是0x8000000，设置你为bootloader分配的flash空间大小（我这里是0x3000）。通过第三项和第四项的设置你会知道，我把flash在逻辑上分为3个部分：

    + 第一部分分了10KByte，用来存储bootloader的代码；
    + 第二部分分了2KByte，用来存储一些用于状态标志的数据（用户也可以把一些数据信息保留在这里，只要不放在该区域的前两个字节即可）
    + 剩余的部分都是用来存储用户应用程序的。也就是说你还有（flash总大小 - 12KByte）的空间可以使用。

5. 编译工程，会在MDK-ARM -> OUTPUT 文件夹下生成与你的硬件平台相对应的文件夹，在这里面就会有hex文件和bin文件。

6. 通过JLINK或者STlINK或者uart下载目标文件到你的硬件平台。

7. 使mcu运行起来。

8. 打开上位机工具，通过串口和MCU进行连接。

9. 选择需要烧入用户应用程序（应用程序app的设置请看另一篇）。

10. 根据你的需求选择更新app、读出app、擦除app、app进入iap模式、复位运行app等操作。

注：bootloader部分只需要烧录一次即可，之后所有操作都通过上位机工具完成。


*****

## 上位机工具配置（可以兼容超级终端）：
    
    + 数据位长度 = 8 Bits
    + 1位停止位
    + 无校验位
    + 波特率 = 115200 baud（根据你的项目需求选择合适的波特率）
    + 硬件流控: None 
    + “包长度”指的是数据传输过程中每一包的长度。可根据你的需要选择合适的包长度。

*****

## 版本说明：
- level00: 官方版本首次跑通。
- level01: 抽象硬件平台，
	+ 修改输出文件
	+ 根据MCU的类别(暂实现6种)选择工程的配置，而不是根据开发版选择硬件平台
    + 使bootloader和app识别相同的指令。
- level02：处理不同情况下各功能之间跳转。
- level03:
    + 完成update和erase部分。
    + first completed except upload
- level04:
	+ 裁剪工程大小
	+ 重新构建工程结构
	+ 添加.bat文件

- 用户使用master版本即可。
	

