/* Coding Array STARTER Kit for Arduino

     CAK Starter Code 06_01_TouchSensor1

    The touch sensor is a sensor that returns a digital input value when the body touches it.
    Can be used as a button switch.
    Short delay time will not count the number of touch accurately. 
    This sketch will learn how to use the touch sensor by default and how to count the number of times the sensor has been pressed. 

    made by Arduinostory
    we@arduinostory.com
*/

#define Touch 7             // Electrostatic Touch Sensor to 7 

int touchCounter = 0;         // Variables that store the number of times a touch sensor is pressed
int lastTouchState = 0;         // Read and save the previous button switch status 

void setup() {
  pinMode(Touch, INPUT);     // Set the touch sensor connected to pin 7 to input 
  Serial.begin(9600);       // Starts serial communication at 9600 speeds 
}


void loop() {
  int touchState = digitalRead(Touch); // Read touch sensor switch values and store them in touchState 

  if (touchState != lastTouchState) { // Touch sensor status has changed 
    if (touchState == HIGH) {              // When the touch sensor is pressed, 
      touchCounter ++;                                 // Increase the number of touch sensors pressed 
      Serial.println("TOUCHED");                          // Write "TOUCHED" in the serial window and replace lines 
      Serial.print("number of touch sensor pushes: ");    // "~:" to the cereal window. 
      Serial.println(touchCounter);                   // Connect and press and replace touch sensor 
    } else {                                          // If the touch sensor has changed from TOUCHED to not touched 
      Serial.println("not touched");                  // Write "not touched" in the serial window and replace lines 
    }
    delay(100);
  }
    lastTouchState = touchState;             //Use current touchState as lastTouchState in the next loop 
}
