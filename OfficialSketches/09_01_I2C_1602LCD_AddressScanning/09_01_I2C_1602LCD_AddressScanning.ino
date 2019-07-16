/* Coding Array STARTER Kit for Arduino
 *   
 * CAK Starter Code 09_01_I2C_1602LCD_AddressScannig
 *  
 *  This sketch is designed to use 1602 LCDs using I2C communication
 *  Scans the address to show the results on the serial monitor. 
 *  
 *  made by Arduinostory
 *  we@arduinostory.com
 */
 
#include <Wire.h>            // Includes the Wire Library for I2C communication. 

void setup()
{
  Wire.begin();

  Serial.begin(9600);              // Starts serial communication at 9600 speeds 
  while(!Serial);                  // Wait for the serial monitor. 
  Serial.println("\nI2C Scanner");
}


void loop()
{
  byte error,address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices =0;

  for (address =1; address <127; address++) 
  {
    // The i2c_scanner has determined whether the device has approved the address. 
    // Use the Write.endTransmission return value to know.  
    Wire.beginTransmission(address);
    error =Wire.endTransmission();

    if (error ==0)
    {
      Serial.print("I2C device found at address 0x");
      if(address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if(error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices ==0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           //  Wait five seconds for the next scan.. 
}
