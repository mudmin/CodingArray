/*  Coding Array STARTER Kit for Arduino
 *   
 *  CAK Starter Code 03_02_BlinkingLED2
 *  
 *  This sketch shows the pin number using variables.
 * 
 *  void If a variable is declared at the top of the previous program 
 *  Any part of the program can use that variable.
 *  These variables are called global variables.
 *  
 *  made by Arduinostory
 *  we@arduinostory.com

 */
 
int redLED = 13;    // Red LED to 13 

void setup() {
  pinMode(redLED,OUTPUT);   // Set No. 13 to output pin
}

void loop() { 
  // Red LED on
  digitalWrite(redLED, HIGH);  // Give digital signal 1 (HIGH) to pin 13. Red LED illuminated 
  delay(1000);                 // Wait for 1000 milliseconds (=1 second) 

  // Red LED off
  digitalWrite(redLED, LOW);   // Give digital signal 0 (LOW) to pin 13. Red LED Off
  delay(1000);                 // Wait for 1000 milliseconds (=1 second).
}
