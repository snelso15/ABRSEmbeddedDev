################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GTK/curl_old/src/macos/src/curl_GUSIConfig.cpp \
../GTK/curl_old/src/macos/src/macos_main.cpp 

OBJS += \
./GTK/curl_old/src/macos/src/curl_GUSIConfig.o \
./GTK/curl_old/src/macos/src/macos_main.o 

CPP_DEPS += \
./GTK/curl_old/src/macos/src/curl_GUSIConfig.d \
./GTK/curl_old/src/macos/src/macos_main.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/curl_old/src/macos/src/%.o: ../GTK/curl_old/src/macos/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -v
	@echo 'Finished building: $<'
	@echo ' '


