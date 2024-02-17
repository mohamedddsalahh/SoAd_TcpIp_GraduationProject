################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TcpIp/TcpIp.c \
../TcpIp/TcpIp_PbCfg.c 

OBJS += \
./TcpIp/TcpIp.o \
./TcpIp/TcpIp_PbCfg.o 

C_DEPS += \
./TcpIp/TcpIp.d \
./TcpIp/TcpIp_PbCfg.d 


# Each subdirectory must supply rules for building sources it contributes
TcpIp/TcpIp.o: ../TcpIp/TcpIp.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/EthIf/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/SoAd/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/Stm32f103c6_Drivers/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/TcpIp/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"TcpIp/TcpIp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
TcpIp/TcpIp_PbCfg.o: ../TcpIp/TcpIp_PbCfg.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/EthIf/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/SoAd/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/Stm32f103c6_Drivers/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/TcpIp/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"TcpIp/TcpIp_PbCfg.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

