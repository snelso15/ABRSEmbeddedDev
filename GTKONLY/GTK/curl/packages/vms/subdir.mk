################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GTK/curl/packages/vms/curl_crtl_init.c \
../GTK/curl/packages/vms/report_openssl_version.c 

OBJS += \
./GTK/curl/packages/vms/curl_crtl_init.o \
./GTK/curl/packages/vms/report_openssl_version.o 

C_DEPS += \
./GTK/curl/packages/vms/curl_crtl_init.d \
./GTK/curl/packages/vms/report_openssl_version.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/curl/packages/vms/%.o: ../GTK/curl/packages/vms/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -v
	@echo 'Finished building: $<'
	@echo ' '


