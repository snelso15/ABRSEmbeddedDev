################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GTK/KeyPressInterpreter.cpp \
../GTK/graphicalFunctions.cpp \
../GTK/gtk-main.cpp \
../GTK/kioskKeyInput.cpp 

OBJS += \
./GTK/KeyPressInterpreter.o \
./GTK/graphicalFunctions.o \
./GTK/gtk-main.o \
./GTK/kioskKeyInput.o 

CPP_DEPS += \
./GTK/KeyPressInterpreter.d \
./GTK/graphicalFunctions.d \
./GTK/gtk-main.d \
./GTK/kioskKeyInput.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/%.o: ../GTK/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -v
	@echo 'Finished building: $<'
	@echo ' '


