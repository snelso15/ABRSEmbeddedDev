################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GTK/curl_old/tests/server/fake_ntlm.c \
../GTK/curl_old/tests/server/getpart.c \
../GTK/curl_old/tests/server/resolve.c \
../GTK/curl_old/tests/server/rtspd.c \
../GTK/curl_old/tests/server/sockfilt.c \
../GTK/curl_old/tests/server/sws.c \
../GTK/curl_old/tests/server/testpart.c \
../GTK/curl_old/tests/server/tftpd.c \
../GTK/curl_old/tests/server/util.c 

OBJS += \
./GTK/curl_old/tests/server/fake_ntlm.o \
./GTK/curl_old/tests/server/getpart.o \
./GTK/curl_old/tests/server/resolve.o \
./GTK/curl_old/tests/server/rtspd.o \
./GTK/curl_old/tests/server/sockfilt.o \
./GTK/curl_old/tests/server/sws.o \
./GTK/curl_old/tests/server/testpart.o \
./GTK/curl_old/tests/server/tftpd.o \
./GTK/curl_old/tests/server/util.o 

C_DEPS += \
./GTK/curl_old/tests/server/fake_ntlm.d \
./GTK/curl_old/tests/server/getpart.d \
./GTK/curl_old/tests/server/resolve.d \
./GTK/curl_old/tests/server/rtspd.d \
./GTK/curl_old/tests/server/sockfilt.d \
./GTK/curl_old/tests/server/sws.d \
./GTK/curl_old/tests/server/testpart.d \
./GTK/curl_old/tests/server/tftpd.d \
./GTK/curl_old/tests/server/util.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/curl_old/tests/server/%.o: ../GTK/curl_old/tests/server/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -v
	@echo 'Finished building: $<'
	@echo ' '


