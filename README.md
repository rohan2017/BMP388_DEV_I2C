# BMP388_DEV

Thanks to MartinL1 for this library. I was having issues using it with my STM32 blackpill, so I simply shaved down the parts that I didn't need/that could be causing problems. THIS LIBRARY DOES NOT DO SPI, nor does it allow you to set custom SCL and SDA pins. 

An Arduino compatible, non-blocking, I2C library for the Bosch BMP388 barometer.

![alt text](https://cdn-learn.adafruit.com/assets/assets/000/072/428/small360/sensors_BMP388_Top_Angle.jpg?1551997243 "Adafruit BMP388 Breakout Board")

© Copyright, image courtesy of [Adafruit Industries](https://www.adafruit.com/product/3966) lisensed under the terms of the [Create Commons Attribution-ShareAlike 3.0 Unported](https://creativecommons.org/licenses/by-sa/3.0/legalcode). 

This BMP388_DEV library offers the following features:

- Returns temperature in degrees celius (**°C**), pressure in hectoPascals/millibar (**hPa**) and altitude in metres (**m**)
- NORMAL or FORCED modes of operation
- I2C or hardware SPI communications with configurable clock rates
- Non-blocking operation 
- In NORMAL mode barometer returns results at the specified standby time interval
- Highly configurable, allows for changes to pressure and temperature oversampling, IIR filter and standby time
- Polling or interrupt driven measurements (using the BMP388's external INT pin)
- Storage and burst reading of up to 72 temperature and pressure measurements using the BMP388's internal 512 byte FIFO memory

---
	
<a name="version"></a>
## __Version__

- Version 1.0.2 -- Modification to allow user-defined pins for I2C operation on the ESP32
- Version 1.0.1 -- Fix uninitialised structures, thanks to David Jade for investigating and flagging up this issue
- Version 1.0.0 -- Intial version

<a name="arduino_compatibility"></a>
## __Arduino Compatibility__

- All Arduino boards, but for 5V Arduino boards (such as the Uno, Nano, Mega, Leonardo, etc...), please check if the BMP388 breakout board requires a 5V to +3.3V voltage level shifter

<a name="installation"></a>
## __Installation__

The BMP388_DEV library can be installed using the Arduino IDE's Library Manager. To access the Library Manager, in the Arduino IDE's menu select _Sketch->Include Library->Manage Libraries..._. In the Library Manager's search bar type BMP388 then select the "Install" button in the BMP388_DEV entry.

Alternatively simply download BMP388_DEV from this Github repository, un-zip or extract the files and place the BMP388_DEV directory in your _.../Arduino/libraries/..._ folder. The _.../Arduino/..._ folder is the one where your Arduino IDE sketches are usually located.

<a name="usage"></a>
## __Usage__

<a name="bmp388_dev_library"></a>
### __BMP388_DEV Library__

Simply include the BMP388_DEV.h file at the beginning of your sketch:

```
#include <BMP388_DEV.h>
```

For I2C communication the BMP388_DEV object is created (instantiated) without any parameters:

```
BMP388_DEV bmp388;	// Set up I2C communications
```

By default the library uses the BMP388's I2C address 0x77. (To use the alternate I2C address: 0x76, see the begin() function below.

By default the I2C runs in fast mode at 400kHz. However it is possible to change the I2C clock speed using the set clock function:

Check out the readme in MartinL1's original library for further explanations (I removed them from here because they are no longer accurate)
