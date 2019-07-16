/* Coding Array STARTER Kit for Arduino
 *  
 * CAK Starter Code 04_01_Button
 * 
 *   If condition statement is used 
 *   Press button switch to connect circuit and return HIGH (1) value to light LED 
 *   If the button switch is not pressed, the circuit will open and the LOW (0) value will be returned to turn off the LED.
 *
 *   made by Arduinostory
 *   we@arduinostory.com
 */

int redLED = 13;       //   Set red LED pin to 13
int Button = 8;        //  Button switch pin set to 8 

void setup() {
  pinMode(Button, INPUT);                 // Set button pin to input 
  pinMode(redLED, OUTPUT);                // Set redLED pin to output 

  Serial.begin(9600);                    //  Starts serial communication at 9600 speed 

}

void loop() {

  int sensorVal = digitalRead(Button);  //  Receive button input value for sensorVal variable.  Variables inserted in void function are regional variables 

  Serial.println(sensorVal);          //  Mark the value of the button one line in the serial window
  //  If the pull-down resistance is connected, give LOW (0) when the button is open and HIGH (1) when pressed. 
  //  give HIGH (1) value when the button is open and LOW (0) when pressed. 


  if (sensorVal == LOW) {         //  If the button is open, 
    digitalWrite(redLED, LOW);          //  RedLED OFF 
  }

  else {                        //  If the button is pressed, 
    digitalWrite(redLED, HIGH);        //  Turn on the redLED. 
  }
  delay(10);
}
