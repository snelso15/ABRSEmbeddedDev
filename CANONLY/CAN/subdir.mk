################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CAN/ABRSMsgs.c \
../CAN/MCP25625.c \
../CAN/PiSPICommands.c \
../CAN/main.c \
../CAN/utils.c 

OBJS += \
./CAN/ABRSMsgs.o \
./CAN/MCP25625.o \
./CAN/PiSPICommands.o \
./CAN/main.o \
./CAN/utils.o 

C_DEPS += \
./CAN/ABRSMsgs.d \
./CAN/MCP25625.d \
./CAN/PiSPICommands.d \
./CAN/main.d \
./CAN/utils.d 


# Each subdirectory must supply rules for building sources it contributes
CAN/%.o: ../CAN/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"  -lwiringPi -lpthread
	@echo 'Finished building: $<'
	@echo ' '


