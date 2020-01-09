///////////////////////////////////////////////////////////////////////////////
// BMP388_DEV - SPI Communications, Default Configuration, Forced Conversion
///////////////////////////////////////////////////////////////////////////////

#include <BMP388_DEV.h>                           // Include the BMP388_DEV.h library

float temperature, pressure, altitude;            // Create the temperature, pressure and altitude variables
BMP388_DEV bmp388(10);                            // Instantiate (create) a BMP388_DEV object and set-up for SPI operation on digital pin D10

void setup() 
{
  Serial.begin(115200);                           // Initialise the serial port
  bmp388.begin();                                 // Default initialisation, place the BMP388 into SLEEP_MODE 
  //bmp388.setPresOversampling(OVERSAMPLING_X4);    // Set the pressure oversampling to X4
  //bmp388.setTempOversampling(OVERSAMPLING_X1);    // Set the temperature oversampling to X1
  //bmp388.setIIRFilter(IIR_FILTER_4);              // Set the IIR filter to setting 4 
}

void loop() 
{
  bmp388.startForcedConversion();                 // Start BMP388 forced conversion (if we're in SLEEP_MODE)
  if (bmp388.getMeasurements(temperature, pressure, altitude))    // Check if the measurement is complete
  {
    Serial.print(temperature);                    // Display the results    
    Serial.print(F("*C   "));
    Serial.print(pressure);    
    Serial.print(F("hPa   "));
    Serial.print(altitude);
    Serial.println(F("m"));  
  }
  delay(1000);
}
