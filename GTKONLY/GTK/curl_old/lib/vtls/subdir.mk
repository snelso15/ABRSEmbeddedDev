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
	gcc -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -v
	@echo 'Finished building: $<'
	@echo ' '

