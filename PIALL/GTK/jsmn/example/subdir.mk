################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GTK/jsmn/example/jsondump.c \
../GTK/jsmn/example/simple.c 

OBJS += \
./GTK/jsmn/example/jsondump.o \
./GTK/jsmn/example/simple.o 

C_DEPS += \
./GTK/jsmn/example/jsondump.d \
./GTK/jsmn/example/simple.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/jsmn/example/%.o: ../GTK/jsmn/example/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I/home/snelso/rpi/rootfs/usr/include/gtk-3.0 -I/home/snelso/rpi/rootfs/usr/include/curl -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Teensy -I/home/snelso/rpi/rootfs/usr/include/at-spi2-atk/2.0 -I/home/snelso/rpi/rootfs/usr/include/atk-1.0 -I/home/snelso/rpi/rootfs/usr/include/harfbuzz -I/home/snelso/rpi/rootfs/usr/include/libpng12 -I/home/snelso/rpi/rootfs/usr/include/pixman-1 -I/home/snelso/rpi/rootfs/usr/include/gdk-pixbuf-2.0 -I/home/snelso/rpi/rootfs/usr/include/cairo -I/home/snelso/rpi/rootfs/usr/include/freetype2 -I/home/snelso/rpi/rootfs/usr/include/gio-unix-2.0/ -I/home/snelso/rpi/rootfs/usr/include/pango-1.0 -I/home/snelso/rpi/rootfs/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/home/snelso/rpi/rootfs/usr/include/glib-2.0 -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Deps/wiringPi/wiringPi-from-pi -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"  -lpthread -lwiringPi -lcurl
	@echo 'Finished building: $<'
	@echo ' '


