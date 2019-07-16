/* Coding Array STARTER Kit for Arduino

    CAK Starter Code 06_02_TouchSensor2

    This sketch shows a touch sensor 
    Touch 1, 2 and 3 to light up the green LED. 
    Touch four times to show the LED is off.
    This allows users to set the desired brightness mood using the touch sensor. 

     made by Arduinostory
     we@arduinostory.com
*/

#define Touch 7             // Connect the capacitive touch sensor to  7. 

const int greenPin = 10 ;       // Green LED to No.10 

int touchCounter = 0;         // Variables that store the number of times a touch sensor is pressed
int lastTouchState = 0;         // Read and save the previous Touch Sensor status 

int alanlogValue;               //  Set analog value of LED (0-255) 


void setup() {

  pinMode(Touch, INPUT);     // Set the touch sensor connected to pin 7 to input 
  pinMode(greenPin, OUTPUT);  // Set pin 11 to output 
  Serial.begin(9600);       // Starts serial communication at 9600 speeds 

}


void loop() {
  int touchState = digitalRead(Touch); // Read touch sensor switch values and store them in touchState 

  if (touchState != lastTouchState) { // Touch sensor status has changed 
    if (touchState == HIGH) {              //

      touchCounter ++;                                 // Increase the number of touch sensors pressed 
      Serial.println("TOUCHED");                          // Write "TOUCHED" in the serial window and replace lines 
      Serial.print("number of touch sensor pushes: ");    //  "~:" to the cereal window 
      Serial.println(touchCounter);                   // Connect and press and replace touch sensor

      //Use current touchState as lastTouchState in the next loop 
      lastTouchState = touchState;

      if (touchCounter % 4 == 0) {   // Touch sensor presses 0
        alanlogValue = 0;
        Serial.println("OFF");
      }

      if (touchCounter % 4 == 1) {   // Touch sensor presses 1
        alanlogValue = 85;
        Serial.println("First level");
      }

      if (touchCounter % 4 == 2) {   // Touch sensor presses 2 
        alanlogValue = 170;
        Serial.println("Second level");
      }

      if (touchCounter % 4 == 3) {   // Touch sensor presses 3 
        alanlogValue = 255;
        Serial.println("Third level");
      }

      //Press the touch sensor to turn on the changed analog value. 
      analogWrite(greenPin, alanlogValue);

    } else {                                              // If the touch sensor has changed from TOUCHED to not touched

      Serial.println("not touched");                     // Write "not touched" in the serial window and replace lines
    }
    delay(100);
  }

  //Use current touchState as lastTouchState in the next loop 
  lastTouchState = touchState;
}
