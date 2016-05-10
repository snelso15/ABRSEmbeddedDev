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
	arm-linux-gnueabihf-gcc -I/home/snelso/rpi/rootfs/usr/include/gtk-3.0 -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Teensy -I/home/snelso/rpi/rootfs/usr/include/at-spi2-atk/2.0 -I/home/snelso/rpi/rootfs/usr/include/atk-1.0 -I/home/snelso/rpi/rootfs/usr/include/harfbuzz -I/home/snelso/rpi/rootfs/usr/include/libpng12 -I/home/snelso/rpi/rootfs/usr/include/pixman-1 -I/home/snelso/rpi/rootfs/usr/include/gdk-pixbuf-2.0 -I/home/snelso/rpi/rootfs/usr/include/cairo -I/home/snelso/rpi/rootfs/usr/include/freetype2 -I/home/snelso/rpi/rootfs/usr/include/gio-unix-2.0/ -I/home/snelso/rpi/rootfs/usr/include/pango-1.0 -I/home/snelso/rpi/rootfs/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/home/snelso/rpi/rootfs/usr/include/glib-2.0 -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Deps/wiringPi/wiringPi-from-pi -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"  -lpthread -lwiringPi
	@echo 'Finished building: $<'
	@echo ' '


