/* Coding Array STARTER Kit for Arduino
 *
 * CAK Starter Code 12_03_Photoresistor_CalibrationFunction
 *
 * This sketch runs while the button switch connected to the digital pin 8 is pressed. 
 * Call up the calibration () function to find the maximum and maximum values of the analog A1 pin to which the light sensor is connected.
 * Return to the main loop if the button is not pressed. 
 * This method can reset the maximum and maximum values of the light sensor when ambient brightness conditions change.
 * 
 * made by Arduinostory
 * we@arduinostory.com
 */

//Set up for LCD use 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set LCD I2C address. 16kans2joules LCD use 

// Set Variables
const int photoresistorPin = A1; // Connect the light sensor to the A1 pin 
const int redLED = 13;          // connect the calibration notification LED to pin 13. 
const int bluePin = 11;         // connect an LED for brightness display according to sensor value to No. 11. 
const int Button = 8;        // Connect button switch to pin 2 

int sensorValue = 0;        //  store the light sensor value 
int sensorMin = 1023;       //  set sensor max to 1023. 
int sensorMax = 0;          // set the sensor maximum value to 0


void setup() {

  // Set Calibration Notification LED Output 
  pinMode(redLED, OUTPUT);

  // set LED output to indicate brightness
  pinMode(bluePin, OUTPUT);

  // Enter buttons connected to pull-up resistance 
  pinMode(Button, INPUT);

  // Initialize LCD 
  lcd.init();
  lcd.backlight();                // turn on the backlight (lcd.noBacklight() turns off the backlight). 

}



void loop() {

  while (digitalRead(Button) == HIGH) {     // when button switch is pressed
    calibrate();                                 // calibration function. 

    digitalWrite(bluePin, LOW);                   // Turn off the blue LED during calibration. 

    lcd.clear();
    lcd.setCursor(0, 0);                // First line first column
    lcd.print("Calibration");              // output messages 
    lcd.setCursor(0, 1);                // First line first column 
    lcd.print("START");                     // output messages 

  }

  digitalWrite(redLED, LOW);        // Turn off the red LED after calibration.

  lcd.clear();
  lcd.setCursor(0, 0);                // First line first column 
  lcd.print("Calibration");              // output messages 
  lcd.setCursor(0, 1);                // First line first column 
  lcd.print("END");                     // output messages 

  sensorValue = analogRead(photoresistorPin);                   // store the light sensor value 
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255); //calibrate sensor values to 0-255. 
  sensorValue = constrain(sensorValue, 0, 255);                 // limit if sensor value is outside calibration range

  analogWrite(bluePin, sensorValue);   // adjust the LED brightness with the calibrated value. 
}



// calibrat() function setting: Reset the maximum and maximum values of the sensor according to the ambient brightness. 

void calibrate() {

  // Turn on the red LED for calibration notifications. 
  digitalWrite(redLED, HIGH);

  // LCD output
  lcd.clear();
  lcd.setCursor(0, 0);                // First line first column 
  lcd.print("Calibration");         // output messages 
  lcd.setCursor(0, 1);                // First line first column 
  lcd.print("START");               // output messages 

  sensorValue = analogRead(photoresistorPin);             // Read and save the value of the light sensor 

  if (sensorValue > sensorMax) {              // the illumination sensor is greater than 1023. 
    sensorMax = sensorValue;                       // read the sensor value and save it to sensorMax 
  }

  if (sensorValue < sensorMin) {             // the light sensor is less than zero 
    sensorMin = sensorValue;                       // read the sensor value and save it to sensorMin 
  }
}
