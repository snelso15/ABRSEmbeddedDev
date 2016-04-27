/*
 * PowerSystems.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: snelso
 */

#include "PowerSystems.h"

#define ARDUINO_RESET_PIN 24
char *portname = "/dev/ttyAMA0";
int currentBatteryPercentage;
time_t lastSuccessfulPowerSystemsComm;
time_t lastArduinoPoll = 0;
char battery_reading_buffer[1000];
int battery_reading_buffer_pointer = 0;
int battery_reading_buffer_pointer_length = 1000;
int serial_port_handle;


int getBatteryPercentage() {
		return currentBatteryPercentage;
}

void resetArduino() {
		printf("Resetting arduino...\n\r");
		digitalWrite(ARDUINO_RESET_PIN, HIGH);
		usleep ((1 + 25) * 100);
		digitalWrite(ARDUINO_RESET_PIN, LOW);
		return;
}

int setup_serial(int serial_port_handle, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (serial_port_handle, &tty) != 0)
        {
                printf("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (serial_port_handle, TCSANOW, &tty) != 0)
        {
                printf ("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void set_blocking(int serial_port_handle, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (serial_port_handle, &tty) != 0)
        {
                printf ("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (serial_port_handle, TCSANOW, &tty) != 0)
                printf ("error %d setting term attributes", errno);

		return;
}

void periodic_battery_checkup() {
	int i;
	char buf [100];
	int n = read (serial_port_handle, buf, sizeof buf);  // read up to 100 characters if ready to read
	if( n ) {
		for(i = 0; i < n && battery_reading_buffer_pointer < battery_reading_buffer_pointer_length; i++) {
			battery_reading_buffer[battery_reading_buffer_pointer] = buf[i];
			battery_reading_buffer_pointer++;
		}
		if( battery_reading_buffer_pointer > 10 ) {
			battery_reading_buffer[battery_reading_buffer_pointer-1] = 0;
			int battery_phrase_offset = 0;
			int battery_phrase_length = 9;
			char battery_phrase[10] = "Battery: ";
			char numeric_buffer[10];
			int numeric_buffer_pointer = 0;
			int numeric_buffer_length = 10;
			for(i = 0; i < battery_reading_buffer_pointer; i++) {
				if( battery_phrase_offset >= battery_phrase_length && battery_reading_buffer[i] != '%' ) {
					if( numeric_buffer_pointer < numeric_buffer_length ) {
						numeric_buffer[numeric_buffer_pointer] = battery_reading_buffer[i];
						numeric_buffer_pointer++;
					}
				} else {
					if(battery_reading_buffer[i] == battery_phrase[battery_phrase_offset]) {
						battery_phrase_offset++;
					} else {
						battery_phrase_offset = 0;
					}
				}
			}

			int null_char_pos = 9;
			if(numeric_buffer_pointer < numeric_buffer_length) {
				null_char_pos = numeric_buffer_pointer;
			}
			numeric_buffer[null_char_pos] = 0;
			int battery_percentage;
			sscanf(numeric_buffer, "%d", &battery_percentage);
			currentBatteryPercentage = battery_percentage;
			lastSuccessfulPowerSystemsComm = time(NULL);
			battery_reading_buffer_pointer = 0;
			write(serial_port_handle, "1", 1);
	                lastArduinoPoll = time(NULL);
		}
	}
	if( (lastArduinoPoll + 1) < time(NULL) ) {
		write(serial_port_handle, "1", 1);
		lastArduinoPoll = time(NULL);
	}
	if( (lastSuccessfulPowerSystemsComm + 60) < time(NULL) ) {
		resetArduino();
		lastSuccessfulPowerSystemsComm = time(NULL);
	}
};

void init_battery_comms() {
	//wiringPiSetupGpio();
	wiringPiSetupSys();

	pinMode(ARDUINO_RESET_PIN, OUTPUT);
	digitalWrite(ARDUINO_RESET_PIN, LOW);

	serial_port_handle = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (serial_port_handle < 0)
	{
			printf("error %d opening %s: %s", errno, portname, strerror (errno));
			return;
	}

	setup_serial(serial_port_handle, B19200, 0);  // set speed to 19,200 bps, 8n1 (no parity)
	set_blocking(serial_port_handle, 0);                // set no blocking
	write(serial_port_handle, "1", 1);           // ask for battery percentage
}
