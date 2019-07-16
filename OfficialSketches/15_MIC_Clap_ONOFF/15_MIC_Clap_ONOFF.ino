/* Coding Array STARTER Kit for Arduino
 * 
 *  CAK Starter code 15_MIC_Clap_ONOFF
 *   
 * This sketch turns on the LED when you clap twice. 
 * Shows the LED illuminates when hit twice again. 
 * 
 *  made by Arduinostory
 *  we@arduinostory.com
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set LCD I2C address. 16kans2joules LCD use

const int sampleWindow = 125; // sample period milliseconds (125 mS = 8 Hz) 
int ledPin = 13;             // Red LED connection to pin 13
int soundValue = 0;         // store the value of the sound sensor 
int clapCounter = 0;        // Save clap count
double threshold = 2.0;         // set clapping sound threshold voltage value

void setup() 
{
Serial.begin(9600);        // initiate serial communication at 9600 speeds 
pinMode(ledPin, OUTPUT);
  
lcd.init();                       // Initialize LCD
lcd.backlight();                  // turn on the backlight (lcd.noBacklight() turns off the backlight).
lcd.clear();                      // clear LCD screen 
lcd.setCursor(0, 0);                // First line first column
lcd.print("LED OFF");                  // message output 
lcd.setCursor(0, 1);                // Line 1st column 
lcd.print("CLAP TWICE~");              // message output 

  
}

void loop() 
{
  unsigned long start= millis();  // start sampling 
  unsigned int peakToPeak = 0;    // Amplitude Value Variables
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;


 // collect data for 125 milliseconds. 
 while (millis() - start < sampleWindow)
 {
      soundValue = analogRead(3); // specify analogue pin number 3.
      if (soundValue < 1024)  // Read data up to the ADC maximum (1024=10bit). 
      {
         if (soundValue > signalMax)
         {
           signalMax = soundValue;  // Store the maximum sound value in the signalMax variable. 
         }
         else if (soundValue < signalMin)
         {
           signalMin = soundValue;  // store the sound minimum in the variable (signalMin). 
         }
     }
 }
 peakToPeak = signalMax - signalMin;  // calculate peak-to-peak amplitude 
 double volts = (peakToPeak * 5) / 1024; // convert the ADC value to a voltage value. Reference Voltage 5V

 Serial.println(volts);
 if (volts >=threshold)
 {
   clapCounter ++;
   Serial.println(soundValue);      //  Output soundValue value to serial monitor 
   Serial.println(clapCounter);     // Output number of applause to serial monitor 
   delay(50);
   // turn on the LED in two claps 
   if(clapCounter == 2)
   {
      digitalWrite(ledPin, HIGH);             // turn on the red LED. 
      Serial.println("LED ON" );              // Output a message to the serial monitor 
      // LCD output
      lcd.clear();
      lcd.setCursor(0, 0);                    // First line first column
      lcd.print("LED ON");                    // message output 
      lcd.setCursor(0, 1);                    // Line 1st column
      lcd.print("CLAP TWICE  ");              // message output 
    }
    // turn off the LED in four claps 
    if (clapCounter == 4) 
    {
      digitalWrite(ledPin, LOW);                // Turn off the red LED.
      Serial.println("LED OFF");            // output messages to serial monitors 

      // LCD output
      lcd.clear();
      lcd.setCursor(0, 0);                   // First line first column 
      lcd.print("LED OFF");                  // message output 
      lcd.setCursor(0, 1);                   // Line 1st column
      lcd.print("CLAP TWICE  ");             // message output 
      clapCounter = clapCounter % 2;         // Save remaining 0 (initialize clap count)
     }
  }             
}
