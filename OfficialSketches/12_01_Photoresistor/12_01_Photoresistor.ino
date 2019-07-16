/* Coding Array STARTER Kit for Arduino
 *   
 *  CAK Starter Code 12_01_Photoresistor
 *  This sketch measures the brightness of light using a light sensing sensor. 
 *  A1 pin connected to the light sensing sensor enters an analog input value between 0 and 1023, depending on the brightness of the light. 
 *  Analog input values are divided into 0 - 3 4 steps through map function and used for switch-case. 
 *  
 *  made by Arduinostory
 *  we@arduinostory.com
 */

// Settings for LCD use 

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // Set the LCD I2C address. Use 16 space 2 line LCD. 

// Set Variables
const int photoresistorPin=A1;  // connect the light sensor to the A1 pin 

const int sensorMin =0;      // Minimum sensor value found by experiment, can be modified. 
const int sensorMax =700;    // Maximum sensor value found by experiment, can be modified. 


void setup() {
    
  // LCD initialization 
  lcd.init();
  lcd.backlight();                // Turn on the backlight. (lcd.noBacklight() turns off the backlight.) 
  lcd.setCursor(0,0);                 // first line first column 
  lcd.print("Range : ");              // Message Output 
   
  // Serial Communication Settings
  Serial.begin(9600);            // Starts serial communication at 9600 speeds 
}

void loop() {

// Read sensor values to map ranges 
  int sensorReading = analogRead(photoresistorPin);   // Read the light sensor value from the A2 pin 
  Serial.println(sensorReading);                                     
  int range = map (sensorReading,sensorMin,sensorMax,0,3);   // Map the sensor values from 0 to 3. 

// output messages according to sensor range  
  switch(range) {                 //  according to range 0-3
    case 0:                        //  touch the sensor and when the sensor value is zero, 
      Serial.println("DARK");             // Darkprint and replace lines in the serial window 
      //Display distance in LCD window
      lcd.clear();
      lcd.setCursor(0,0);                 //  first line first column 
      lcd.print("Range : ");              // indicate brightness phase on LCD window 
      lcd.print(range);
      lcd.setCursor(0,1);                 // the first column of the second line 
      lcd.print("DARK");                // DARK Output 
      break;
      
    case 1:                       //  Put your hands close to the sensor and when the sensor value is 1, 
      Serial.println("DIM");              // Dimprint and replace lines in serial window 
      //Display distance in LCD window
      lcd.clear();
      lcd.setCursor(0,0);                 //  first line first column 
      lcd.print("Range : ");              //indicate brightness phase on LCD window 
      lcd.print(range);
      lcd.setCursor(0,1);                 //  the first column of the second line 
      lcd.print("DIM");                 // DIM output 
      break;
      
    case 2:                       // Keep your hands away from the sensor and when the sensor value is 2 
      Serial.println("MEDIUM");           // print medium on serial window and replace lines 
      //Display distance in LCD window
      lcd.clear();
      lcd.setCursor(0,0);                 //  first line first column 
      lcd.print("Range : ");              // indicate brightness phase on LCD window 
      lcd.print(range);
      lcd.setCursor(0,1);                 // the first column of the second line 
      lcd.print("MEDIUM");              //MEDIUM Output       
      break;
      
    case 3:                      // When the sensor value is 3 without touching the sensor nearby, 
      Serial.println("BRIGHT");         // print the lightprint on the cereal window and replace the line 
      //Display distance in LCD window
      lcd.clear();
      lcd.setCursor(0,0);                 //  first line first column 
      lcd.print("Range : ");              // indicate brightness phase on LCD window 
      lcd.print(range);
      lcd.setCursor(0,1);                 // the first column of the second line 
      lcd.print("BRIGHT");              // BRIGHT Output      
      break;
  }

  delay(500);                      // 50 millisecond delay to reliably read values 
}
