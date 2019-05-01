################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MFRC522.c \
../Src/beeper.c \
../Src/card_reader.c \
../Src/database.c \
../Src/ethernetif.c \
../Src/gpio.c \
../Src/lwip.c \
../Src/main.c \
../Src/printf_redirect.c \
../Src/rtc.c \
../Src/scan_fifo.c \
../Src/spi.c \
../Src/stm32f2xx_hal_msp.c \
../Src/stm32f2xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f2xx.c \
../Src/tim.c \
../Src/timer.c \
../Src/usart.c \
../Src/wwdg.c 

OBJS += \
./Src/MFRC522.o \
./Src/beeper.o \
./Src/card_reader.o \
./Src/database.o \
./Src/ethernetif.o \
./Src/gpio.o \
./Src/lwip.o \
./Src/main.o \
./Src/printf_redirect.o \
./Src/rtc.o \
./Src/scan_fifo.o \
./Src/spi.o \
./Src/stm32f2xx_hal_msp.o \
./Src/stm32f2xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f2xx.o \
./Src/tim.o \
./Src/timer.o \
./Src/usart.o \
./Src/wwdg.o 

C_DEPS += \
./Src/MFRC522.d \
./Src/beeper.d \
./Src/card_reader.d \
./Src/database.d \
./Src/ethernetif.d \
./Src/gpio.d \
./Src/lwip.d \
./Src/main.d \
./Src/printf_redirect.d \
./Src/rtc.d \
./Src/scan_fifo.d \
./Src/spi.d \
./Src/stm32f2xx_hal_msp.d \
./Src/stm32f2xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f2xx.d \
./Src/tim.d \
./Src/timer.d \
./Src/usart.d \
./Src/wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F207xx -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Inc" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/system" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Drivers/STM32F2xx_HAL_Driver/Inc" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Drivers/STM32F2xx_HAL_Driver/Inc/Legacy" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/lwip" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/netif" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/posix" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/system/arch" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Drivers/CMSIS/Include" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/lwip_sql_connector-master/include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


