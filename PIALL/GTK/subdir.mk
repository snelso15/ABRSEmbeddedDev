################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GTK/ABRSDebug.cpp \
../GTK/CANThread.cpp \
../GTK/CANWorker.cpp \
../GTK/CommandLineUtils.cpp \
../GTK/PowerSystems.cpp \
../GTK/TeensyWorker.cpp \
../GTK/UIWorker.cpp \
../GTK/backLightControl.cpp \
../GTK/backendCommunicator.cpp \
../GTK/backendFunctionality.cpp \
../GTK/graphicalFunctions.cpp \
../GTK/kioskKeyInput.cpp \
../GTK/main.cpp \
../GTK/motionSensor.cpp \
../GTK/weatherMonitor.cpp \
../GTK/workerCallbacks.cpp 

OBJS += \
./GTK/ABRSDebug.o \
./GTK/CANThread.o \
./GTK/CANWorker.o \
./GTK/CommandLineUtils.o \
./GTK/PowerSystems.o \
./GTK/TeensyWorker.o \
./GTK/UIWorker.o \
./GTK/backLightControl.o \
./GTK/backendCommunicator.o \
./GTK/backendFunctionality.o \
./GTK/graphicalFunctions.o \
./GTK/kioskKeyInput.o \
./GTK/main.o \
./GTK/motionSensor.o \
./GTK/weatherMonitor.o \
./GTK/workerCallbacks.o 

CPP_DEPS += \
./GTK/ABRSDebug.d \
./GTK/CANThread.d \
./GTK/CANWorker.d \
./GTK/CommandLineUtils.d \
./GTK/PowerSystems.d \
./GTK/TeensyWorker.d \
./GTK/UIWorker.d \
./GTK/backLightControl.d \
./GTK/backendCommunicator.d \
./GTK/backendFunctionality.d \
./GTK/graphicalFunctions.d \
./GTK/kioskKeyInput.d \
./GTK/main.d \
./GTK/motionSensor.d \
./GTK/weatherMonitor.d \
./GTK/workerCallbacks.d 


# Each subdirectory must supply rules for building sources it contributes
GTK/%.o: ../GTK/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I/home/snelso/rpi/rootfs/usr/include/gtk-3.0 -I/home/snelso/rpi/rootfs/usr/include/at-spi2-atk/2.0 -I/home/snelso/rpi/rootfs/usr/include/atk-1.0 -I/home/snelso/rpi/rootfs/usr/include/harfbuzz -I/home/snelso/rpi/rootfs/usr/include/libpng12 -I/home/snelso/rpi/rootfs/usr/include/pixman-1 -I/home/snelso/rpi/rootfs/usr/include/gdk-pixbuf-2.0 -I/home/snelso/rpi/rootfs/usr/include/cairo -I/home/snelso/rpi/rootfs/usr/include/freetype2 -I/home/snelso/rpi/rootfs/usr/include/gio-unix-2.0/ -I/home/snelso/rpi/rootfs/usr/include/pango-1.0 -I/home/snelso/rpi/rootfs/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/home/snelso/rpi/rootfs/usr/include/glib-2.0 -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Deps/wiringPi/wiringPi-from-pi -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/CAN -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<" -lpthread -lwiringPi
	@echo 'Finished building: $<'
	@echo ' '

GTK/backendFunctionality.o: ../GTK/backendFunctionality.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I/home/snelso/rpi/rootfs/usr/include/gtk-3.0 -I/home/snelso/rpi/rootfs/usr/include/curl -I/home/snelso/rpi/rootfs/usr/include/at-spi2-atk/2.0 -I/home/snelso/rpi/rootfs/usr/include/atk-1.0 -I/home/snelso/rpi/rootfs/usr/include/harfbuzz -I/home/snelso/rpi/rootfs/usr/include/libpng12 -I/home/snelso/rpi/rootfs/usr/include/pixman-1 -I/home/snelso/rpi/rootfs/usr/include/gdk-pixbuf-2.0 -I/home/snelso/rpi/rootfs/usr/include/cairo -I/home/snelso/rpi/rootfs/usr/include/freetype2 -I/home/snelso/rpi/rootfs/usr/include/gio-unix-2.0/ -I/home/snelso/rpi/rootfs/usr/include/pango-1.0 -I/home/snelso/rpi/rootfs/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/home/snelso/rpi/rootfs/usr/include/glib-2.0 -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Deps/wiringPi/wiringPi-from-pi -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/CAN -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"GTK/backendFunctionality.d" -o "$@" "$<" -lpthread -lwiringPi
	@echo 'Finished building: $<'
	@echo ' '

GTK/weatherMonitor.o: ../GTK/weatherMonitor.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I/home/snelso/rpi/rootfs/usr/include/gtk-3.0 -I/home/snelso/rpi/rootfs/usr/include/curl -I/home/snelso/rpi/rootfs/usr/include/at-spi2-atk/2.0 -I/home/snelso/rpi/rootfs/usr/include/atk-1.0 -I/home/snelso/rpi/rootfs/usr/include/harfbuzz -I/home/snelso/rpi/rootfs/usr/include/libpng12 -I/home/snelso/rpi/rootfs/usr/include/pixman-1 -I/home/snelso/rpi/rootfs/usr/include/gdk-pixbuf-2.0 -I/home/snelso/rpi/rootfs/usr/include/cairo -I/home/snelso/rpi/rootfs/usr/include/freetype2 -I/home/snelso/rpi/rootfs/usr/include/gio-unix-2.0/ -I/home/snelso/rpi/rootfs/usr/include/pango-1.0 -I/home/snelso/rpi/rootfs/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/home/snelso/rpi/rootfs/usr/include/glib-2.0 -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/Deps/wiringPi/wiringPi-from-pi -I/home/snelso/capstone-workspace/ABRSEmbeddedDev/CAN -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"GTK/weatherMonitor.d" -o "$@" "$<" -lpthread -lwiringPi
	@echo 'Finished building: $<'
	@echo ' '


