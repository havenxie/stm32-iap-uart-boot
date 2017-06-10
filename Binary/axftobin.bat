@echo off

if exist C:\Keil\ARM\BIN40\fromelf.exe (
if exist .\..\MDK-ARM\STM32100B-EVAL\STM32100B-EVAL.axf (C:\Keil\ARM\BIN40\fromelf.exe ".\..\MDK-ARM\STM32100B-EVAL\STM32100B-EVAL.axf" --bin --output ".\STM32100B-EVAL_SysTick.bin")
if exist .\..\MDK-ARM\STM3210C-EVAL\STM3210C-EVAL.axf (C:\Keil\ARM\BIN40\fromelf.exe ".\..\MDK-ARM\STM3210C-EVAL\STM3210C-EVAL.axf" --bin --output ".\STM3210C-EVAL_SysTick.bin")  
if exist .\..\MDK-ARM\STM3210B-EVAL\STM3210B-EVAL.axf (C:\Keil\ARM\BIN40\fromelf.exe ".\..\MDK-ARM\STM3210B-EVAL\STM3210B-EVAL.axf" --bin --output ".\STM3210B-EVAL_SysTick.bin")
if exist .\..\MDK-ARM\STM3210E-EVAL\STM3210E-EVAL.axf (C:\Keil\ARM\BIN40\fromelf.exe ".\..\MDK-ARM\STM3210E-EVAL\STM3210E-EVAL.axf" --bin --output ".\STM3210E-EVAL_SysTick.bin")
if exist .\..\MDK-ARM\STM3210E-EVAL_XL\STM3210E-EVAL_XL.axf (C:\Keil\ARM\BIN40\fromelf.exe ".\..\MDK-ARM\STM3210E-EVAL_XL\STM3210E-EVAL_XL.axf" --bin --output ".\STM3210E-EVAL_XL_SysTick.bin")
if exist .\..\MDK-ARM\STM32100E-EVAL\STM32100E-EVAL.axf (C:\Keil\ARM\BIN40\fromelf.exe ".\..\MDK-ARM\STM32100E-EVAL\STM32100E-EVAL.axf" --bin --output ".\STM32100E-EVAL_SysTick.bin")

 )

pause

