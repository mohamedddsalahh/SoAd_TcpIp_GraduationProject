################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/PduR.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/PduR.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/PduR.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/PduR.o: ../Src/PduR.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/EthIf/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/SoAd/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/Stm32f103c6_Drivers/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/TcpIp/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/PduR.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/main.o: ../Src/main.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/EthIf/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/SoAd/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/Stm32f103c6_Drivers/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/TcpIp/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/EthIf/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/SoAd/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/Stm32f103c6_Drivers/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/TcpIp/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/EthIf/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/SoAd/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/Stm32f103c6_Drivers/Inc" -I"D:/Mohamed/College/GP/TcpIp/SoAd_TcpIp_Integration/SoAd_TcpIp_Server/TcpIp/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

