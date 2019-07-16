/* Coding Array STARTER Kit for Arduino
 *   
 *  CAK Starter Code 03_01_BlinkingLED
 *  
 *  Let's set the red LEDs connected to pin 13 to the output and repeat the execution
 *  of the LED turning on for 1 second and off for 1 second, 
 *  depending on the time settings of the digitalWrite 
 *  function indicating the digital output and the delay function..
 *  
 *  made by Arduinostory
 *  we@arduinostory.com
 */
 
void setup() {
  pinMode(13,OUTPUT); //  Set 13 to output pin
}

void loop() { 
  digitalWrite(13,HIGH); // Give digital signal 1 (HIGH) to pin 13. LED illuminated
  delay(1000);           // Wait for 1000 milliseconds (=1 second).  
  digitalWrite(13,LOW);  // Give digital signal 0 (LOW) to pin 13. LED Off 
  delay(1000);           // Wait for 1000 milliseconds (=1 second) .
}
