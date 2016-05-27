################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GTK/curl_old/packages/OS400/ccsidcurl.c \
../GTK/curl_old/packages/OS400/os400sys.c 

OBJS += \
./GTK/curl_old/packages/OS400/ccsidcurl.o \
./GTK/curl_old/packages/OS400/os400sys.o 

C_DEPS += \
./GTK/curl_old/packages/OS400/ccsidcurl.d \
./GTK/curl_old/packages/OS400/os400sys.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/curl_old/packages/OS400/%.o: ../GTK/curl_old/packages/OS400/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -v
	@echo 'Finished building: $<'
	@echo ' '


