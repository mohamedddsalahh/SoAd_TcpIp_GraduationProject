################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EthIf/EthIf.c 

OBJS += \
./EthIf/EthIf.o 

C_DEPS += \
./EthIf/EthIf.d 


# Each subdirectory must supply rules for building sources it contributes
EthIf/EthIf.o: ../EthIf/EthIf.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/EthIf/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/SoAd/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/Stm32f103c6_Drivers/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/TcpIp/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"EthIf/EthIf.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

