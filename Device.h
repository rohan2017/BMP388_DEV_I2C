/*
  Device is an I2C/SPI compatible base class library.
	
	Copyright (C) Martin Lindupp 2020
	
	V1.0.0 -- Initial release 
	V1.0.1 -- Modification to allow user-defined pins for I2C operation on the ESP8266
	V1.0.2 -- Modification to allow user-defined pins for I2C operation on the ESP32
	
	The MIT License (MIT)
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#ifndef Device_h
#define Device_h

#include <Arduino.h>
#include <Wire.h>

////////////////////////////////////////////////////////////////////////////////
// Device Communications
////////////////////////////////////////////////////////////////////////////////
			 
enum Comms { I2C_COMMS, SPI_COMMS };

////////////////////////////////////////////////////////////////////////////////
// Device Class definition
////////////////////////////////////////////////////////////////////////////////

class Device{
	public:
		Device();  // Device object for I2C operation
		void setClock(uint32_t clockSpeed);  // Set the I2C/SPI clock speed
	protected:
		void initialise();  // Initialise communications	
		void setI2CAddress(uint8_t addr);  // Set the Device I2C address
		void writeByte(uint8_t subAddress, uint8_t data);  // I2C and SPI write byte wrapper function
		uint8_t readByte(uint8_t subAddress);  // I2C and SPI read byte wrapper function
		void readBytes(uint8_t subAddress, uint8_t* dest, uint16_t count);  // I2C and SPI read bytes wrapper function	
	private:
		Comms comms;  // Communications bus: I2C or SPI
		uint8_t address;  // The device I2C address
};
#endif