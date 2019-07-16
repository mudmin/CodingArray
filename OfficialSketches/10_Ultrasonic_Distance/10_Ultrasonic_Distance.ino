/*  ArduinoStory CodingArrayKit_Level_1
 *   
 *  CAK Starter Code 10_Ultrasonic_Distance
 *   
 *  This sketch uses ultrasonic sensors to measure the distance. 
 *  The trigger pin is connected to Arduino's number 5. The trigger pin produces ultrasonic waves
 *   Echo pins are connected to Arduino's number 4. The echo pin detects reflected ultrasound
 *   The measured distance should be shown in both the serial and LCD windows. 
 *   If the measured distance exceeds the set value, the green LED, 
 *  If the measured distance exceeds the set value, turn on the red LED. 
 */
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Set the LCD I2C address. Use 16 Space 2-line LCD 

int redLED = 13;                 // Red LED No. 13                 
int greenPin=10;                 // Green LED No. 13 

int threshold = 15;              // Set Distance Threshold Value

void setup() {
 

 pinMode(5,OUTPUT);     // Trigger pin connection No. 5 
 pinMode(4,INPUT);      // Echopin to Pin 4


  //LED Output Settings
  pinMode(redLED,OUTPUT);      // Set pin 13 to output
  pinMode(greenPin, OUTPUT);   // Set pin 10 to output

  // Serial Communication Settings
  Serial.begin(9600);            // Starts serial communication at 9600 speeds
     
  // LCD Settings
  lcd.init();
  lcd.backlight();                // Turn on the backlight. (lcd.noBacklight() turns off the backlight.) 
  lcd.clear();
}


void loop() {

//  Distance measurement with ultrasonic sensor 

  float Duration, Distance;
  digitalWrite(5, HIGH);                                     // Fire an ultrasound. 
  delayMicroseconds(10);                                     // for 10 microseconds
  digitalWrite(5, LOW);                                      // Turn off the ultrasound. 
  Duration =pulseIn(4, HIGH);                                // Save the time the ehofin is held in HIGH
  Distance =((float)(340 *Duration) /10000) /2;              // convert the distance to cm 


// Measured Distance Output 
  
  Serial.print(Distance);                 // Print distance in serial window without changing lines 
  Serial.println("cm");                   // unit output 


  if (Distance < threshold){             // If the measurement distance is less than the threshold value, turn on the red LED.
    
     digitalWrite(redLED,HIGH);
     digitalWrite(greenPin,LOW);     
     
     //Show Distance to LCD Window
     
    lcd.clear();
    lcd.setCursor(0,0);                 // first line first column 
    lcd.print(Distance,2);              // Measured Distance Output    
    lcd.print("[cm]");                  // unit output 


  
  }
  else {                                //If the measured value is greater than the threshold value, turn on the green LED.
    
     digitalWrite(redLED,LOW);
     digitalWrite(greenPin,HIGH);     
     
     //Show Distance to LCD Window 

    lcd.clear();
    lcd.setCursor(0,0);                 // first line first column
    lcd.print(Distance,2);             // Measured Distance Output   
    lcd.print("[cm]");                 //  unit output 
  }

  
  delay(2000);                      // 2000 millisecond delay to reliably read values 
}
