
/* Coding Array STARTER Kit for Arduino
 * CAK Starter Code 11_HallEffect
 *  
 *   This sketch uses the Hall Effect module connected to Analog A2.
 *  Read the value of the analogue sensor which varies with the surrounding magnetic field 
 *  Measure the strength of the magnetic field by converting it to voltage. 
 *  This module has a lower output voltage as the N pole approaches and a higher output voltage as the S pole approaches.
 *  
 *  Outputs a comma-separated serial message for easy transfer of result values to Excel.  
 *  Copy the message from the serial window and paste it into the memo pad.Save as CSV" extension 
 *  You can create a file that can be retrieved from Excel
 *  
 *  made by Arduinostory
 *  we@arduinostory.com

*/


// set up for LCD use

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address. Use 16 Space 2-line LCD 

//connect hall sensor to A2 pin 
const int hallPin = A2;


// Set Variables
int sensorReading;                        // Store analog sensor values 
int voltage;                            // Store the converted value to voltage 



void setup() {
  // Set communication speed to 9600 
  Serial.begin(9600);

  // LCD initialization 
  lcd.init();
  lcd.backlight();                //  Turn on the backlight. (lcd.noBacklight() turns off the backlight.) 

  Serial.println("sensorReading, Voltage (mv)");      // Output message for csv file in serial window 
  delay(1000);
}

void loop()
{
    
  sensorReading = analogRead(hallPin);         // Read and save the analog value of the sensor 
  voltage = (int) sensorReading * (5.0 / 1024.0) * 1000; // Convert Analog Values from Voltage0 to 5000 

  // csv (when you want to receive data in comma-separated text format) 
  Serial.print(sensorReading);
  Serial.print(",");
  Serial.println(voltage);

  //Output a message in an LCD window
    lcd.clear();
    lcd.setCursor(0, 0);                // first line first column 
    lcd.print("Anlaog_V :");
    lcd.print(sensorReading);
    lcd.setCursor(0, 1);                // 2nd line first column 
    lcd.print(voltage);
    lcd.print("mV");
  delay(500);
}
