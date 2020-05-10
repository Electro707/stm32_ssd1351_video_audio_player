################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Src/delay.c \
../Libraries/Src/diskio.c \
../Libraries/Src/display.c \
../Libraries/Src/ff.c \
../Libraries/Src/ffsystem.c \
../Libraries/Src/ffunicode.c 

OBJS += \
./Libraries/Src/delay.o \
./Libraries/Src/diskio.o \
./Libraries/Src/display.o \
./Libraries/Src/ff.o \
./Libraries/Src/ffsystem.o \
./Libraries/Src/ffunicode.o 

C_DEPS += \
./Libraries/Src/delay.d \
./Libraries/Src/diskio.d \
./Libraries/Src/display.d \
./Libraries/Src/ff.d \
./Libraries/Src/ffsystem.d \
./Libraries/Src/ffunicode.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Src/delay.o: ../Libraries/Src/delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 '-DVDD_VALUE=3300' '-DHSE_VALUE=8000000' -DSTM32F103xB '-DLSI_VALUE=40000' '-DHSI_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' -DUSE_FULL_LL_DRIVER -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Libraries/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/Src/delay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/Src/diskio.o: ../Libraries/Src/diskio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 '-DVDD_VALUE=3300' '-DHSE_VALUE=8000000' -DSTM32F103xB '-DLSI_VALUE=40000' '-DHSI_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' -DUSE_FULL_LL_DRIVER -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Libraries/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/Src/diskio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/Src/display.o: ../Libraries/Src/display.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 '-DVDD_VALUE=3300' '-DHSE_VALUE=8000000' -DSTM32F103xB '-DLSI_VALUE=40000' '-DHSI_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' -DUSE_FULL_LL_DRIVER -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Libraries/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/Src/display.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/Src/ff.o: ../Libraries/Src/ff.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 '-DVDD_VALUE=3300' '-DHSE_VALUE=8000000' -DSTM32F103xB '-DLSI_VALUE=40000' '-DHSI_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' -DUSE_FULL_LL_DRIVER -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Libraries/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/Src/ff.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/Src/ffsystem.o: ../Libraries/Src/ffsystem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 '-DVDD_VALUE=3300' '-DHSE_VALUE=8000000' -DSTM32F103xB '-DLSI_VALUE=40000' '-DHSI_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' -DUSE_FULL_LL_DRIVER -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Libraries/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/Src/ffsystem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Libraries/Src/ffunicode.o: ../Libraries/Src/ffunicode.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 '-DVDD_VALUE=3300' '-DHSE_VALUE=8000000' -DSTM32F103xB '-DLSI_VALUE=40000' '-DHSI_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' -DUSE_FULL_LL_DRIVER -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DPREFETCH_ENABLE=1' -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Libraries/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/Src/ffunicode.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

