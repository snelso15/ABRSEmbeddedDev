################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GTK/curl/tests/server/fake_ntlm.c \
../GTK/curl/tests/server/getpart.c \
../GTK/curl/tests/server/resolve.c \
../GTK/curl/tests/server/rtspd.c \
../GTK/curl/tests/server/sockfilt.c \
../GTK/curl/tests/server/sws.c \
../GTK/curl/tests/server/testpart.c \
../GTK/curl/tests/server/tftpd.c \
../GTK/curl/tests/server/util.c 

OBJS += \
./GTK/curl/tests/server/fake_ntlm.o \
./GTK/curl/tests/server/getpart.o \
./GTK/curl/tests/server/resolve.o \
./GTK/curl/tests/server/rtspd.o \
./GTK/curl/tests/server/sockfilt.o \
./GTK/curl/tests/server/sws.o \
./GTK/curl/tests/server/testpart.o \
./GTK/curl/tests/server/tftpd.o \
./GTK/curl/tests/server/util.o 

C_DEPS += \
./GTK/curl/tests/server/fake_ntlm.d \
./GTK/curl/tests/server/getpart.d \
./GTK/curl/tests/server/resolve.d \
./GTK/curl/tests/server/rtspd.d \
./GTK/curl/tests/server/sockfilt.d \
./GTK/curl/tests/server/sws.d \
./GTK/curl/tests/server/testpart.d \
./GTK/curl/tests/server/tftpd.d \
./GTK/curl/tests/server/util.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/curl/tests/server/%.o: ../GTK/curl/tests/server/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -v
	@echo 'Finished building: $<'
	@echo ' '


