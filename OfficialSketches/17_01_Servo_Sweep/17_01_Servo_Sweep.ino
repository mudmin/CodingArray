/*  ArduinoStory CodingArrayKit_Level_1
 *   
 *  CAK Starter code 17_01_Servo_Sweep
 *  This sketch uses servo live 
 *  Move the servo motor by 0 - > 180 degrees
 *  Move back to 180 - >0 degrees. 
 *  Note that servo motors cannot be rotated 360 degrees. 
 */
 
#include <Servo.h>         // Include servo library 

Servo myservo;            // create object myservo to control servo

int position =0;                // store the servo's position. Initial value 0 

void setup() {
  myservo.attach(3);      // attach servo motor to pin 3
}


void loop() {
  myservo.write(90);  // position in the center of the servo motor shaft (90 degrees)
  delay (1000);

  myservo.write(0);   // position 0 degrees on servo motor shaft 
  delay (1000);

  myservo.write(180);   // position 180 degrees on servo motor shaft
  delay (1000);

  myservo.write(90);  // located in the center of the servo motor shaft
  delay (1000);
  /*
  for(position = 0; position <= 180; position += 1) {     // increase by 1 degree to 0 to 180 degrees. 
    myservo.write(position);                                    // move to a specified angle 
    delay(30);                                                  // wait until servo to arrive.
  }

  for(position = 180; position >= 0; position -= 1) {     // decrease by 1 degree to 180 degrees. 
    myservo.write(position);                                   // move to a specified angle 
    delay(30);                                                 // wait until servo to arrive.
    }
     */
}
