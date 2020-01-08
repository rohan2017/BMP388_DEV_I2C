# CURRENTLY UNDER DEVELOPMENT

# BMP388_DEV
An Arduino compatible, non-blocking, I2C/SPI library for the Bosch BMP388 barometer.

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
- Storage and burst reading of up to 70 temperature and pressure measurements using the BMP388's internal 512KB FIFO memory

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
#include <BMP388_DEV.h>
```

For I2C communication the BMP388_DEV object is created (instantiated) without parameters:

```
BMP388_DEV bmp388;	// Set up I2C communications
```

By default the library uses the BMP388's I2C address 0x77. (To use the alternate I2C address: 0x76, see the begin() function below.

For SPI communication the chip select (CS) Arduino digital output pin is specified as an argument, for example digital pin 10:

```
BMP388_dev bmp388(10);	// Set up SPI communications on digital pin D10
```

The library also supports the ESP32 HSPI operation on pins: SCK 14, MOSI 13, MISO 27 and user defined SS (CS):

```
SPIClass SPI1(HSPI);							    // Create the SPI1 HSPI object
BMP388_DEV bmp388(21, HSPI, SPI1);		// Set up HSPI port communications on the ESP32
```

By default the I2C runs in fast mode at 400kHz and SPI at 1MHz. However it is possible to change the clock speed using the set clock function:

```
bmp388.setClock(4000000);			// Set the SPI clock to 4MHz
```

---
### __Device Initialisation__

To initialise the BMP388 it is necessary to call the begin() function with or without parameters. The parameters specify the starting mode, pressure/temperature oversampling, IIR filter and standby time options respectively:

```
bmp388.begin(SLEEP_MODE, OVERSAMPLING_X16, OVERSAMPLING_X2, IIR_FILTER_4, TIME_STANDBY_5MS);
```

Alternatively simply call the begin function without any paremeters, this sets up the default configuration: SLEEP_MODE, pressure oversampling X16, temperature oversampling X2, IIR filter OFF and a standby time of 5ms:

```
bmp388.begin();	// Initialise the BMP388 with default configuration
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
bmp388.setPresOversamping(OVERSAMPING_X4);	// Options are OVERSAMPLING_SKIP, _X1, _X2, _X4, _X8, _X16, _32
```

```
bmp388.setTempOversamping(OVERSAMPING_X4);	// Options are OVERSAMPLING_SKIP, _X1, _X2, _X4, _X8, _X16, _X32
```

```
bmp388.setIIRFilter(IIR_FILTER_16);	// Options are IIR_FILTER_OFF, _2, _4, _8, _16, _32
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
BMP388_DEV bmp388;	// Instantiate (create) a BMP388_DEV object and set-up for I2C operation (address 0x77)
```

...should be replaced with the line:

```
BMP388_DEV bmp388(10);	// Instantiate (create) a BMP388_DEV object and set-up for SPI operation with chip select on D10
```

For more details see code examples provided in the _.../examples/..._ directory.

---
### __Interrupts__

The BMP388 barometer has an INT output pin that allows measurements to be interrupt driven instead of polling, both in NORMAL and FORCED modes of operation.

Interrupts are enabled by calling the enable interrupt function with or without parameters. The parameters specify whether the INT pin output drive is: PUSH_PULL or OPEN_DRAIN, the signal is: ACTIVE_LOW or ACTIVE_HIGH and interrupt itself is: UNLATCHED or LATCHED. UNLATCHED automatically clears the interrupt signal after 2.5ms, while LATCHED remains active until the data is read.

The default settigs are PUSH_PULL, ACTIVE_HIGH and UNLATCHED:

```
bmp388.enableInterrupt(PUSH_PULL, ACTIVE_HIGH, UNLATCHED);		// Enable interrupts with default settings
```
Alternatively these settings are used if the enable interrupt function is called without any parameters:

```
bmp388.enableInterrupt();		// Enable interrupts with default settings
```
The interrupts can also be disabled by calling the disable interrupt function:

```
bmp388.disableInterrupt();		// Enable interrupts with default settings
```

Attaching the Arduino to the BMP388's interrupt pins is performed using the standard attachInterrupt() function:

```
attachInterrupt(digitalPinToInterrupt(2), interruptHandler, RISING);   // Set interrupt to call interruptHandler function on D2
```

If the SPI interface being shared with other devices then it is also necessary to call the SPI usingInterrupt function as well:

```
bmp388.usingInterrupt(digitalPinToInterrupt(2));     // Invoke the SPI usingInterrupt() function
```

The I2C interface uses the Arduino Wire library. However as the Wire library generates interrupts itself during operation, it is unfortunately therefore not possible to call the results acqusition functions from within the INT pin's Interrupt Service Routine (ISR) itself. Instead a data ready flag is set within the ISR that allows the barometer data to be read in the main loop() function.

Here is an example sketch using I2C in NORMAL_MODE, default configuration with interrupts:

```
///////////////////////////////////////////////////////////////////////////////
// BMP388_DEV - I2C Communications, Default Configuration, Normal Conversion
///////////////////////////////////////////////////////////////////////////////

#include <BMP388_DEV.h>                           // Include the BMP388_DEV.h library

volatile boolean dataReady = false;

BMP388_DEV bmp388;                                // Instantiate (create) a BMP388_DEV object and set-up for I2C operation (address 0x77)

void setup() 
{
  Serial.begin(115200);                           // Initialise the serial port
  bmp388.begin();                                 // Default initialisation, place the BMP388 into SLEEP_MODE 
  bmp388.enableInterrupt();                       // Enable the BMP388's interrupt (INT) pin
  attachInterrupt(digitalPinToInterrupt(2), interruptHandler, RISING);   // Set interrupt to call interruptHandler function on D2
  bmp388.setTimeStandby(TIME_STANDBY_1280MS);     // Set the standby time to 1.3 seconds
  bmp388.startNormalConversion();                 // Start BMP388 continuous conversion in NORMAL_MODE  
}

void loop() 
{
  if (dataReady)
  {
    float temperature, pressure, altitude;
    bmp388.getMeasurements(temperature, pressure, altitude);      // Read the measurements
    Serial.print(temperature);                    // Display the results    
    Serial.print(F("*C   "));
    Serial.print(pressure);    
    Serial.print(F("hPa   "));
    Serial.print(altitude);
    Serial.println(F("m")); 
    dataReady = false;                            // Clear the dataReady flag
  }   
}

void interruptHandler()                           // Interrupt handler function
{
  dataReady = true;                               // Set the dataReady flag
}
```

The SPI interface on the other hand, does allow for the results acquistion functions to be called from within the ISR.

Here is an example sketch using SPI in NORMAL_MODE, default configuration with interrupts:

```
///////////////////////////////////////////////////////////////////////////////
// BMP388_DEV - SPI Communications, Default Configuration, Normal Conversion
///////////////////////////////////////////////////////////////////////////////

#include <BMP388_DEV.h>                             // Include the BMP388_DEV.h library

volatile boolean dataReady = false;
volatile float temperature, pressure, altitude;

BMP388_DEV bmp388(10);                              // Instantiate (create) a BMP388_DEV object and set-up for SPI operation on digital pin D10

void setup() 
{
  Serial.begin(115200);                             // Initialise the serial port
  bmp388.begin();                                   // Default initialisation, place the BMP388 into SLEEP_MODE 
  bmp388.enableInterrupt();                         // Enable the BMP388's interrupt (INT) pin
  bmp388.usingInterrupt(digitalPinToInterrupt(2));  // Invoke the SPI usingInterrupt() function
  attachInterrupt(digitalPinToInterrupt(2), interruptHandler, RISING);   // Set interrupt to call interruptHandler function on D2
  bmp388.setTimeStandby(TIME_STANDBY_1280MS);       // Set the standby time to 1.2 seconds
  bmp388.startNormalConversion();                   // Start BMP388 continuous conversion in NORMAL_MODE 
}

void loop() 
{
  if (dataReady)                                    // Check if the measurement is complete
  {   
    dataReady = false;                              // Clear the data ready flag
    Serial.print(temperature);                      // Display the results    
    Serial.print(F("*C   "));
    Serial.print(pressure);    
    Serial.print(F("hPa   "));
    Serial.print(altitude);
    Serial.println(F("m"));  
  }
}

void interruptHandler()                             // Interrupt handler function
{
  if(bmp388.getMeasurements(temperature, pressure, altitude))    // Read the measurement data
  {
    dataReady = true;                                 // Set the data ready flag
  }
}
```
---
## __FIFO (First In First Out) Operation__ 

The BMP388 barometer contains a 512KB FIFO memory, capable if storing and burst reading up to 70 temperature and pressure measurements.

To enable the FIFO simply cal

---
## __FIFO Operation with Interrupts__ 

The BMP388 barometer also allows FIFO operation to be integrated with interrupts from the INT pin.

---
## __Example Code__

- I2C Normal Mode: 1.3 second automatic sampling rate with default settings

- I2C Normal Mode: (Alterntive I2C Address): 1.3 second automatic sampling rate with default settings

- I2C Forced Mode: 1 second manual sampling rate with default settings

- SPI Normal Mode: 1.3 second automatic sampling rate with default settings

- SPI Forced Mode: 1 second manual sampling rate with default settings

- ESP32 HSPI Normal Mode: 1.3 second automatic sampling rate with default settings

- SPI Normal Mode Multiple: 1.3 second automatic sampling of multiple BMP388 with default settings

- I2C Normal Mode and Interrupts: 1.3 second automatic sampling rate with default settings

- I2C Forced Mode and Interrupts: 1 second manual sampling with default settings

- SPI Normal Mode and Interrupts: 1.3 second automatic sampling rate with default settings

- SPI Forced Mode and Interrupts: 1 second manual sampling rate with default settings

- I2C Normal Mode and FIFO : store 10 measurements at 1.3 second automatic sampling rate with default settings

- I2C Forced Mode and FIFO : store 10 measurements at 1 second manual sampling rate with default settings

- SPI Normal Mode and FIFO : store 10 measurements, sampling at 1.3 seconds standby time intervals with default settings

- SPI Forced Mode and FIFO : store 10 measurements with default settings

