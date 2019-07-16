/*  ArduinoStory CodingArrayKit_Level_1
 *   
 *  CAK Starter code 17_02_Servo_Knob
 *  This sketch uses servo live 
 *  The servo motor is between 0 and 180 degrees depending on the variable resistance value 
 *  Move the axis. 
 */
 
#include <Servo.h>         // Include servo library

Servo myservo;            // create object myservo to control servo; up to 12 can be created 

int position =0;                // store the servo's position. Initial value 0
int potPin=A0;                  //  Connect variable resistance to A1 pin 

void setup() {
  myservo.attach(3);            // attach servo motor to pin 3 
}


void loop() {

  int val =analogRead(potPin);               // Read variable resistance value (0-1023)
  int servoVal =map(val,0,1023,0,180);       // map variable resistance values to 0-180 degrees servo motor rotation angle 
  myservo.write(servoVal);                   // position of mapped servo 
  delay(15);                                 // wait for the servo to arrive. 
  
  int pitchVal=map(val, 0, 1023,120,1500);   // map variable resistance values to 120 to 1500 Hz sound frequencies 
  tone(6, pitchVal, 10);                     // output mapped sound value to manual buzzer connected to pin 6 for 10 milliseconds 
  
  delay (1);                                 // delay of 1 millisecond for safety 

}
