# BMP388_DEV
An Arduino compatible, non-blocking, I2C/SPI library for the Bosch BMP388 barometer.

![alt text](https://cdn-learn.adafruit.com/guides/cropped_images/000/002/449/medium640/BMP388_Top_Angle.jpg?1551997132 "Adafruit BMP388 Breakout Board")

© Copyright, image courtesy of [Adafruit Industries](https://www.adafruit.com/product/3966) lisensed under the terms of the [Create Commons Attribution-ShareAlike 3.0 Unported](https://creativecommons.org/licenses/by-sa/3.0/legalcode). 

This BMP388_DEV library offers the following features:

- Returns temperature in degrees celius (**°C**), pressure in hectoPascals/millibar (**hPa**) and altitude in metres (**m**)
- NORMAL or FORCED modes of operation
- I2C or hardware SPI communications with configurable clock rates
- Non-blocking operation 
- In NORMAL mode barometer returns results at the specified standby time interval
- Highly configurable, allows for changes to pressure and temperature oversampling, IIR filter and standby time
- Polling or interrupt (using the BMP388's external INT pin) driven measurments
- Storage and burst reading of measurments using the BMP388's internal 512KB FIFO memory

## __Version__

- Version 1.0.0 -- Intial version

## __Arduino Compatibility__

- All Arduino boards, but for 5V Arduino boards (such as the Uno, Nano, Mega, Leonardo, etc...), please check if the BMP388 breakout board requires a 5V to +3.3V voltage level shifter

## __Installation__

After download simply un-zip the file and place the BMP388 directory in your _.../Arduino/libraries/..._ folder. The _.../Arduino/..._ folder is the one where your Arduino IDE sketches are usually located.

## __Usage__

### __BMP388_DEV Library__

Simply include the BMP388_DEV.h file at the beginning of your sketch:

```
#include <BMP280_DEV.h>
```

For I2C communication the BMP388_DEV object is created (instantiated) without parameters:

```
BMP280_DEV bmp280;	// Set up I2C communications
```

By default the library uses the BMP388's I2C address 0x77. (To use the alternate I2C address: 0x76, see the begin() function below.

For SPI communication the chip select (CS) Arduino digital output pin is specified as an argument, for example digital pin 10:

```
BMP280_dev bmp280(10);	// Set up SPI communications on digital pin D10
```

The library also supports the ESP32 HSPI operation on pins: SCK 14, MOSI 13, MISO 27 and user defined SS (CS):

```
SPIClass SPI1(HSPI);							// Create the SPI1 HSPI object
BMP280_DEV bmp(21, HSPI, SPI1);		// Set up HSPI port communications on the ESP32
```

By default the I2C runs in fast mode at 400kHz and SPI at 1MHz.

---
### __Device Initialisation__

To initialise the BMP388 it is necessary to call the begin() function with or without parameters. The parameters specify the starting mode, pressure/temperature oversampling, IIR filter and standby time options respectively:

```
bmp280.begin(SLEEP_MODE, OVERSAMPLING_X16, OVERSAMPLING_X2, IIR_FILTER_4, TIME_STANDBY_05MS);
```

Alternatively simply call the begin function without any paremeters, this sets up the default configuration: SLEEP_MODE, pressure oversampling X16, temperature oversampling X2, IIR filter OFF and a standby time of 0.5ms:

```
bmp388.begin();	// Initialise the BMP380 with default configuration
```

Another alternative is to pass the BMP388's mode as an argument:

```
bmp388.begin(NORMAL_MODE);	// Initialise the BMP388 in NORMAL_MODE with default configuration
```

Or, specifying mode and alternate I2C address:

```
bmp388.begin(FORCED_MODE, BMP388_I2C_ALT_ADDR);	// Initialise the BMP388 in FORCED_MODE with the alternate I2C address (0x76)
```

Or even just the alternate I2C address, (BMP388 initialised in SLEEP_MODE by default):

```
bmp388.begin(BMP388_I2C_ALT_ADDR);	// Initialise the BMP388 with the alternate I2C address (0x76)
```

Note that the begin functions return the value 1 upon successful initialisation, otherwise it returns 0 for failure.

---
### __Device Configuration__

After initialisation it is possible to change the BMP388 configuration with the following functions:

```
bmp388.setPresOversamping(OVERSAMPING_X4);	// Options are OVERSAMPLING_SKIP, _X1, _X2, _X4, _X8, _X16
```

```
bmp388.setTempOversamping(OVERSAMPING_X4);	// Options are OVERSAMPLING_SKIP, _X1, _X2, _X4, _X8, _X16
```

```
bmp388.setIIRFilter(IIR_FILTER_16);	// Options are IIR_FILTER_OFF, _2, _4, _8, _16
```

```
bmp388.setTimeStandby(TIME_STANDBY_2000MS);	// Options are TIME_STANDBY_05MS, _62MS, _125MS, _250MS, _500MS, _1000MS, 2000MS, 4000MS
```
---
### __Modes Of Operation__

The BMP388 has 3 modes of operation: **SLEEP_MODE**, **NORMAL_MODE** and **FORCED_MODE**: 

- **SLEEP_MODE**: puts the device into an inactive standby state 

- **NORMAL_MODE**: performs continuous conversions, separated by the standby time

- **FORCED_MODE**: performs a single conversion, returning to **SLEEP_MODE** upon completion

To kick-off conversions in **NORMAL_MODE**:

```
bmp388.startNormalConversion();	// Start continuous conversions, separated by the standby time
```

To perform a single oneshot conversion in **FORCED_MODE**:

```
bmp388.startForcedConversion();	// Start a single oneshot conversion
```

To stop the conversion at anytime and return to **SLEEP_MODE**:

```
bmp388.stopConversion();	// Stop conversion and return to SLEEP_MODE
```
---
### __Results Acquisition__

The BMP388 barometer library acquires temperature in degrees celius (**°C**), pressure in hectoPascals/millibar (**hPa**) and altitude in metres (**m**). The acquisition functions scan the BMP388's status register and return 1 if the barometer results are ready and have been successfully read, 0 if they are not; this allows for non-blocking code implementation. The temperature, pressure and altitude results themselves are _float_ variables by passed reference to the function and are updated upon a successful read.

Here are the results acquisition functions:

```
bmp388.getMeasurements(temperature, pressure, altitude);	// Acquire temperature, pressue and altitude measurements
```

```
bmp388.getTempPres(temperature, pressure);	// Acquire both the temperature and pressure
```

```
bmp388.getTemperature(temperature);	// Acquire the temperature only
```

```
bmp388.getPressure(pressure);	// Acquire the pressure only, (also calculates temperature, but doesn't return it)
```

```
bmp388.getAltitude(altitude);	// Acquire the altitude only
```
---
### __Code Implementation__

Here is an example sketch of how to use the BMP388 library for non-blocking I2C operation, default configuration with continuous conversion in NORMAL_MODE, but with a standby sampling time of 1 second:

```
#include <BMP388_DEV.h>                           // Include the BMP388_DEV.h library

float temperature, pressure, altitude;            // Create the temperature, pressure and altitude variables
BMP388_DEV bmp388;                                // Instantiate (create) a BMP388_DEV object and set-up for I2C operation (address 0x77)

void setup() 
{
  Serial.begin(115200);                           // Initialise the serial port
  bmp388.begin();                                 // Default initialisation, place the BMP388 into SLEEP_MODE 
  bmp388.setTimeStandby(TIME_STANDBY_1000MS);     // Set the standby time to 1s
  bmp388.startNormalConversion();                 // Start NORMAL conversion mode
}

void loop() 
{
  if (bmp388.getMeasurements(temperature, pressure, altitude))    // Check if the measurement is complete
  {
    Serial.print(temperature);                    // Display the results    
    Serial.print(F("*C   "));
    Serial.print(pressure);    
    Serial.print(F("hPa   "));
    Serial.print(altitude);
    Serial.println(F(m"));
  }
}
```

A second sketch example for I2C operation, default configuration in FORCED conversion mode:

```
#include <BMP388_DEV.h>                           // Include the BMP388_DEV.h library

float temperature, pressure, altitude;            // Create the temperature, pressure and altitude variables
BMP388_DEV bmp388;                                // Instantiate (create) a BMP388_DEV object and set-up for I2C operation (address 0x77)

void setup() 
{
  Serial.begin(115200);                           // Initialise the serial port
  bmp388.begin();                                 // Default initialisation, place the BMP388 into SLEEP_MODE 
}

void loop() 
{
  bmp388.startForcedConversion();                 // Start a forced conversion (if in SLEEP_MODE)
  if (bmp388.getMeasurements(temperature, pressure, altitude))    // Check if the measurement is complete
  {
    Serial.print(temperature);                    // Display the results    
    Serial.print(F("*C   "));
    Serial.print(pressure);    
    Serial.print(F("hPa   "));
    Serial.print(altitude);
    Serial.println(F("m"));
  }
}
```

The sketches for SPI operation are identical except that the line:

```
BMP388_DEV bmp280;	// Instantiate (create) a BMP388_DEV object and set-up for I2C operation (address 0x77)
```

...should be replaced with the line:

```
BMP388_DEV bmp280(10);	// Instantiate (create) a BMP388_DEV object and set-up for SPI operation with chip select on D10
```

For more details see code examples provided in the _.../examples/..._ directory.

---
## __Example Code__

I2C Normal Mode: sampling at 1.3 seconds standby time intervals with default settings

I2C Normal Mode (Alterntive I2C Address): sampling at 1.3 second standby time intervals with default settings

I2C Forced Mode: with default settings

SPI Normal Mode: sampling at 1.3 second standby time intervals with default settings

SPI Forced Mode: with default settings

ESP32 HSPI Normal Mode: sampling at 1.3 second standby time intervals with default settings

SPI Normal Mode Multiple: sampling multiple BMP388 devices at 2 second standby time intervals with default settings

I2C Normal Mode and Interrupts: sampling at 1.3 seconds standby time intervals with default settings

I2C Forced Mode and Interrupts: with default settings

SPI Normal Mode and Interrupts: sampling at 1.3 seconds standby time intervals with default settings

SPI Forced Mode and Interrupts: sampling at 1.3 seconds standby time intervals with default settings

I2C Normal Mode and FIFO : store 10 measurements, sampling at 1.3 seconds standby time intervals with default settings

I2C Forced Mode and FIFO : store 10 measurements with default settings

SPI Normal Mode and FIFO : store 10 measurements, sampling at 1.3 seconds standby time intervals with default settings

SPI Forced Mode and FIFO : store 10 measurements with default settings

