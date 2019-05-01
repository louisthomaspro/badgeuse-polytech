################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/api/api_lib.c \
../Middlewares/Third_Party/LwIP/src/api/api_msg.c \
../Middlewares/Third_Party/LwIP/src/api/err.c \
../Middlewares/Third_Party/LwIP/src/api/netbuf.c \
../Middlewares/Third_Party/LwIP/src/api/netdb.c \
../Middlewares/Third_Party/LwIP/src/api/netifapi.c \
../Middlewares/Third_Party/LwIP/src/api/sockets.c \
../Middlewares/Third_Party/LwIP/src/api/tcpip.c 

OBJS += \
./Middlewares/Third_Party/LwIP/src/api/api_lib.o \
./Middlewares/Third_Party/LwIP/src/api/api_msg.o \
./Middlewares/Third_Party/LwIP/src/api/err.o \
./Middlewares/Third_Party/LwIP/src/api/netbuf.o \
./Middlewares/Third_Party/LwIP/src/api/netdb.o \
./Middlewares/Third_Party/LwIP/src/api/netifapi.o \
./Middlewares/Third_Party/LwIP/src/api/sockets.o \
./Middlewares/Third_Party/LwIP/src/api/tcpip.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/api/api_lib.d \
./Middlewares/Third_Party/LwIP/src/api/api_msg.d \
./Middlewares/Third_Party/LwIP/src/api/err.d \
./Middlewares/Third_Party/LwIP/src/api/netbuf.d \
./Middlewares/Third_Party/LwIP/src/api/netdb.d \
./Middlewares/Third_Party/LwIP/src/api/netifapi.d \
./Middlewares/Third_Party/LwIP/src/api/sockets.d \
./Middlewares/Third_Party/LwIP/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/api/%.o: ../Middlewares/Third_Party/LwIP/src/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F207xx -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Inc" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/system" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Drivers/STM32F2xx_HAL_Driver/Inc" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Drivers/STM32F2xx_HAL_Driver/Inc/Legacy" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/lwip" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/netif" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/posix" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Middlewares/Third_Party/LwIP/system/arch" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/Drivers/CMSIS/Include" -I"/mnt/data/corentin/Projets/eclipse-workspace/Badgeuse/lwip_sql_connector-master/include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


