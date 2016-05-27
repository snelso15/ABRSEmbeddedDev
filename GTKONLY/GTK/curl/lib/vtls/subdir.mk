################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GTK/curl/lib/vtls/axtls.c \
../GTK/curl/lib/vtls/cyassl.c \
../GTK/curl/lib/vtls/darwinssl.c \
../GTK/curl/lib/vtls/gskit.c \
../GTK/curl/lib/vtls/gtls.c \
../GTK/curl/lib/vtls/mbedtls.c \
../GTK/curl/lib/vtls/nss.c \
../GTK/curl/lib/vtls/openssl.c \
../GTK/curl/lib/vtls/polarssl.c \
../GTK/curl/lib/vtls/polarssl_threadlock.c \
../GTK/curl/lib/vtls/schannel.c \
../GTK/curl/lib/vtls/vtls.c 

OBJS += \
./GTK/curl/lib/vtls/axtls.o \
./GTK/curl/lib/vtls/cyassl.o \
./GTK/curl/lib/vtls/darwinssl.o \
./GTK/curl/lib/vtls/gskit.o \
./GTK/curl/lib/vtls/gtls.o \
./GTK/curl/lib/vtls/mbedtls.o \
./GTK/curl/lib/vtls/nss.o \
./GTK/curl/lib/vtls/openssl.o \
./GTK/curl/lib/vtls/polarssl.o \
./GTK/curl/lib/vtls/polarssl_threadlock.o \
./GTK/curl/lib/vtls/schannel.o \
./GTK/curl/lib/vtls/vtls.o 

C_DEPS += \
./GTK/curl/lib/vtls/axtls.d \
./GTK/curl/lib/vtls/cyassl.d \
./GTK/curl/lib/vtls/darwinssl.d \
./GTK/curl/lib/vtls/gskit.d \
./GTK/curl/lib/vtls/gtls.d \
./GTK/curl/lib/vtls/mbedtls.d \
./GTK/curl/lib/vtls/nss.d \
./GTK/curl/lib/vtls/openssl.d \
./GTK/curl/lib/vtls/polarssl.d \
./GTK/curl/lib/vtls/polarssl_threadlock.d \
./GTK/curl/lib/vtls/schannel.d \
./GTK/curl/lib/vtls/vtls.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/curl/lib/vtls/%.o: ../GTK/curl/lib/vtls/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -v
	@echo 'Finished building: $<'
	@echo ' '


