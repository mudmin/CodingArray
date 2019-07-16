/* Coding Array STARTER Kit for Arduino
 *   
 *  CAK Starter Code 12_02_Photoresistor_Calibration
 *  This sketch will learn how to calibrate the light sense sensor input values according to the surroundings.  
 *  Read the value of the analog A1 pin to which the light sensor is connected for 5 seconds to store the maximum and maximum values
 *   The maximum value stored is 0 and the maximum value is 255, which is converted through the map function. 
 *   After uploading the code, cover the light sensor with your hands and press the reset button. 
 *   Allow the maximum and maximum values to be stored while keeping hands away from the light sensor for 5 seconds.
 *   Then, move your hands around the light sensor to check the change in the blue brightness of the RGB LED
 *  
 *  made by Arduinostory
 *  we@arduinostory.com
 */

// set up for LCD use 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD I2C address. 16 space 2 lines LCD use

// Set Variables
const int photoresistorPin=A1;  // Connect light sensor to A1 pin 
const int redLED=13;            // connect the calibration notification LED to pin 13. 
const int bluePin=11;           //  connect LEDs for brightness display according to sensor value to number 11. 

int sensorValue =0;         //  store the light sensor value 
int sensorMin =1023;        // set sensor max to 1023. 
int sensorMax =0;           // set the sensor maximum value to 0 


void setup() {
  
  // Calibration Notification LED Output Settings
  pinMode(redLED, OUTPUT);
  digitalWrite(redLED, HIGH);
  
  // LCD setting 
  lcd.init();
  lcd.backlight();                //  turn on the backlight (lcd.noBacklight() turns off the backlight). 
  lcd.clear();
  lcd.setCursor(0,0);                 //  First line first column 
  lcd.print("Calibration");              // output messages 
  lcd.setCursor(0,1);                 // First line first column 
  lcd.print("START");              // output messages 
  
 // Sensor Value Calibration
  while(millis() < 5000) {                     // for 5 seconds
    sensorValue = analogRead(photoresistorPin);           //save sensor values

    if(sensorValue > sensorMax) {                  //sensor value is greater than maximum 
      sensorMax = sensorValue;                           // reset to maximum value 
    }

    if(sensorValue < sensorMin) {                  //sensor value is less than the maximum value 
      sensorMin = sensorValue;                           // reset to maximum value
    }
  }
  
// End calibration. Turn off the LED and output a message to the LCD screen 
  digitalWrite(redLED,LOW);                            
  
  lcd.clear();
  lcd.setCursor(0,0);                 // First line first column 
  lcd.print("Calibration");              // output messages
  lcd.setCursor(0,1);                 // First line first column 
  lcd.print("END");                     // output messages
}


void loop() {

  sensorValue = analogRead (photoresistorPin);   //read an analogue sensor value and store it in a variable

  // read sensor value and convert to 0-255
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

  // limit if sensor value is outside calibration range 
  sensorValue = constrain(sensorValue, 0, 255);

  // adjust blue LED brightness with sensor value
  analogWrite(bluePin,sensorValue);    

}
