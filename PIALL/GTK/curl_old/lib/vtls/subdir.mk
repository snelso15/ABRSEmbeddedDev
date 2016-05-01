################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GTK/curl_old/lib/vtls/axtls.c \
../GTK/curl_old/lib/vtls/cyassl.c \
../GTK/curl_old/lib/vtls/darwinssl.c \
../GTK/curl_old/lib/vtls/gskit.c \
../GTK/curl_old/lib/vtls/gtls.c \
../GTK/curl_old/lib/vtls/mbedtls.c \
../GTK/curl_old/lib/vtls/nss.c \
../GTK/curl_old/lib/vtls/openssl.c \
../GTK/curl_old/lib/vtls/polarssl.c \
../GTK/curl_old/lib/vtls/polarssl_threadlock.c \
../GTK/curl_old/lib/vtls/schannel.c \
../GTK/curl_old/lib/vtls/vtls.c 

OBJS += \
./GTK/curl_old/lib/vtls/axtls.o \
./GTK/curl_old/lib/vtls/cyassl.o \
./GTK/curl_old/lib/vtls/darwinssl.o \
./GTK/curl_old/lib/vtls/gskit.o \
./GTK/curl_old/lib/vtls/gtls.o \
./GTK/curl_old/lib/vtls/mbedtls.o \
./GTK/curl_old/lib/vtls/nss.o \
./GTK/curl_old/lib/vtls/openssl.o \
./GTK/curl_old/lib/vtls/polarssl.o \
./GTK/curl_old/lib/vtls/polarssl_threadlock.o \
./GTK/curl_old/lib/vtls/schannel.o \
./GTK/curl_old/lib/vtls/vtls.o 

C_DEPS += \
./GTK/curl_old/lib/vtls/axtls.d \
./GTK/curl_old/lib/vtls/cyassl.d \
./GTK/curl_old/lib/vtls/darwinssl.d \
./GTK/curl_old/lib/vtls/gskit.d \
./GTK/curl_old/lib/vtls/gtls.d \
./GTK/curl_old/lib/vtls/mbedtls.d \
./GTK/curl_old/lib/vtls/nss.d \
./GTK/curl_old/lib/vtls/openssl.d \
./GTK/curl_old/lib/vtls/polarssl.d \
./GTK/curl_old/lib/vtls/polarssl_threadlock.d \
./GTK/curl_old/lib/vtls/schannel.d \
./GTK/curl_old/lib/vtls/vtls.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/curl_old/lib/vtls/%.o: ../GTK/curl_old/lib/vtls/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I/home/snelso/rpi/rootfs/usr/include/gtk-3.0 -I/home/snelso/rpi/rootfs/usr/include/curl -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Teensy -I/home/snelso/rpi/rootfs/usr/include/at-spi2-atk/2.0 -I/home/snelso/rpi/rootfs/usr/include/atk-1.0 -I/home/snelso/rpi/rootfs/usr/include/harfbuzz -I/home/snelso/rpi/rootfs/usr/include/libpng12 -I/home/snelso/rpi/rootfs/usr/include/pixman-1 -I/home/snelso/rpi/rootfs/usr/include/gdk-pixbuf-2.0 -I/home/snelso/rpi/rootfs/usr/include/cairo -I/home/snelso/rpi/rootfs/usr/include/freetype2 -I/home/snelso/rpi/rootfs/usr/include/gio-unix-2.0/ -I/home/snelso/rpi/rootfs/usr/include/pango-1.0 -I/home/snelso/rpi/rootfs/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/home/snelso/rpi/rootfs/usr/include/glib-2.0 -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Deps/wiringPi/wiringPi-from-pi -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"  -lpthread -lwiringPi -lcurl
	@echo 'Finished building: $<'
	@echo ' '


