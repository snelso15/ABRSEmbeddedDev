################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GTK/graphicalFunctions.cpp \
../GTK/kioskKeyInput.cpp \
../GTK/main.cpp 

OBJS += \
./GTK/graphicalFunctions.o \
./GTK/kioskKeyInput.o \
./GTK/main.o 

CPP_DEPS += \
./GTK/graphicalFunctions.d \
./GTK/kioskKeyInput.d \
./GTK/main.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/%.o: ../GTK/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -I/home/snelso/git/wiringPi/wiringPi -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


