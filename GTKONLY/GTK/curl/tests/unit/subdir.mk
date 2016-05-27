################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GTK/curl/tests/unit/unit1300.c \
../GTK/curl/tests/unit/unit1301.c \
../GTK/curl/tests/unit/unit1302.c \
../GTK/curl/tests/unit/unit1303.c \
../GTK/curl/tests/unit/unit1304.c \
../GTK/curl/tests/unit/unit1305.c \
../GTK/curl/tests/unit/unit1307.c \
../GTK/curl/tests/unit/unit1308.c \
../GTK/curl/tests/unit/unit1309.c \
../GTK/curl/tests/unit/unit1330.c \
../GTK/curl/tests/unit/unit1394.c \
../GTK/curl/tests/unit/unit1395.c \
../GTK/curl/tests/unit/unit1396.c \
../GTK/curl/tests/unit/unit1397.c \
../GTK/curl/tests/unit/unit1398.c \
../GTK/curl/tests/unit/unit1600.c \
../GTK/curl/tests/unit/unit1601.c \
../GTK/curl/tests/unit/unit1602.c \
../GTK/curl/tests/unit/unit1603.c \
../GTK/curl/tests/unit/unit1604.c 

OBJS += \
./GTK/curl/tests/unit/unit1300.o \
./GTK/curl/tests/unit/unit1301.o \
./GTK/curl/tests/unit/unit1302.o \
./GTK/curl/tests/unit/unit1303.o \
./GTK/curl/tests/unit/unit1304.o \
./GTK/curl/tests/unit/unit1305.o \
./GTK/curl/tests/unit/unit1307.o \
./GTK/curl/tests/unit/unit1308.o \
./GTK/curl/tests/unit/unit1309.o \
./GTK/curl/tests/unit/unit1330.o \
./GTK/curl/tests/unit/unit1394.o \
./GTK/curl/tests/unit/unit1395.o \
./GTK/curl/tests/unit/unit1396.o \
./GTK/curl/tests/unit/unit1397.o \
./GTK/curl/tests/unit/unit1398.o \
./GTK/curl/tests/unit/unit1600.o \
./GTK/curl/tests/unit/unit1601.o \
./GTK/curl/tests/unit/unit1602.o \
./GTK/curl/tests/unit/unit1603.o \
./GTK/curl/tests/unit/unit1604.o 

C_DEPS += \
./GTK/curl/tests/unit/unit1300.d \
./GTK/curl/tests/unit/unit1301.d \
./GTK/curl/tests/unit/unit1302.d \
./GTK/curl/tests/unit/unit1303.d \
./GTK/curl/tests/unit/unit1304.d \
./GTK/curl/tests/unit/unit1305.d \
./GTK/curl/tests/unit/unit1307.d \
./GTK/curl/tests/unit/unit1308.d \
./GTK/curl/tests/unit/unit1309.d \
./GTK/curl/tests/unit/unit1330.d \
./GTK/curl/tests/unit/unit1394.d \
./GTK/curl/tests/unit/unit1395.d \
./GTK/curl/tests/unit/unit1396.d \
./GTK/curl/tests/unit/unit1397.d \
./GTK/curl/tests/unit/unit1398.d \
./GTK/curl/tests/unit/unit1600.d \
./GTK/curl/tests/unit/unit1601.d \
./GTK/curl/tests/unit/unit1602.d \
./GTK/curl/tests/unit/unit1603.d \
./GTK/curl/tests/unit/unit1604.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/curl/tests/unit/%.o: ../GTK/curl/tests/unit/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/freetype2 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -v
	@echo 'Finished building: $<'
	@echo ' '


