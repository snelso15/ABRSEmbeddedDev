################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Teensy/teensyCommunicator.cpp 

OBJS += \
./Teensy/teensyCommunicator.o 

CPP_DEPS += \
./Teensy/teensyCommunicator.d 


# Each subdirectory must supply rules for building sources it contributes
Teensy/%.o: ../Teensy/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I/home/snelso/rpi/rootfs/usr/include/gtk-3.0 -I/home/snelso/rpi/rootfs/usr/include/curl -I/home/snelso/rpi/rootfs/usr/include/at-spi2-atk/2.0 -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Deps/curl/include/curl -I/home/snelso/rpi/rootfs/usr/include/atk-1.0 -I/home/snelso/rpi/rootfs/usr/include/harfbuzz -I/home/snelso/rpi/rootfs/usr/include/libpng12 -I/home/snelso/rpi/rootfs/usr/include/pixman-1 -I/home/snelso/rpi/rootfs/usr/include/gdk-pixbuf-2.0 -I/home/snelso/rpi/rootfs/usr/include/cairo -I/home/snelso/rpi/rootfs/usr/include/freetype2 -I/home/snelso/rpi/rootfs/usr/include/gio-unix-2.0/ -I/home/snelso/rpi/rootfs/usr/include/pango-1.0 -I/home/snelso/rpi/rootfs/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/home/snelso/rpi/rootfs/usr/include/glib-2.0 -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Deps/wiringPi/wiringPi-from-pi -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/CAN -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Teensy -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lpthread -lwiringPi
	@echo 'Finished building: $<'
	@echo ' '


