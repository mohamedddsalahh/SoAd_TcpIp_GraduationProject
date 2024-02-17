################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SoAd/SoAd.c \
../SoAd/SoAd_PBcfg.c 

OBJS += \
./SoAd/SoAd.o \
./SoAd/SoAd_PBcfg.o 

C_DEPS += \
./SoAd/SoAd.d \
./SoAd/SoAd_PBcfg.d 


# Each subdirectory must supply rules for building sources it contributes
SoAd/SoAd.o: ../SoAd/SoAd.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/EthIf/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/SoAd/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/Stm32f103c6_Drivers/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/TcpIp/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SoAd/SoAd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
SoAd/SoAd_PBcfg.o: ../SoAd/SoAd_PBcfg.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/EthIf/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/SoAd/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/Stm32f103c6_Drivers/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Client/TcpIp/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SoAd/SoAd_PBcfg.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

