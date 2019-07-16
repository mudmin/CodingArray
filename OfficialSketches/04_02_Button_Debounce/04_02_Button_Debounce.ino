/*  ArduinoStory CodingArrayKit_STARTER
 *   
 * CAK Starter Code 04_02_Button_Debounce
 * 
 *   When a button switch is opened and closed, it often generates incorrect signals due to mechanical and physical problems. 
 *  Avoid this situation by pressing and reading multiple times in a very short time that can fool a program 
 *  This process is called divauning. 
 */
 
const int Button =8;     //  Set button switch pin to 8 
const int redLED = 13;      // Set LED pin to 13 

int ledState =HIGH;          //  Set output pin to HIGH 
int buttonState;             //  Variables that read and store the current button switch status 
int lastButtonState =HIGH;    // Read and save the previous button switch status, reset to LOW 

unsigned long lastDebounceTime =0;    //  Save the last time the output pin was switched. 
unsigned long debounceDelay =50;      //  Time to wait for steady state (milliseconds) 

void setup() {
  pinMode(redLED, OUTPUT);                    // Set red LED pin to output 
  pinMode(Button, INPUT); 
  digitalWrite(redLED,ledState);       // Turn the LED on and off according to the ledState 
}


void loop() {
 
  int reading = digitalRead(Button);   // Read button status and save to reading variable 

  if(reading != lastButtonState) {     // If the status of the button changes to Noise or Press, 
    
    lastDebounceTime =millis();          //  Reset the debounging timer, 
  }
    
  // Whatever value you've read, if it's longer than the debounce delay,
  if((millis() -lastDebounceTime) > debounceDelay) { 
    if(reading != buttonState) {             // If the status of the button changes, 
      buttonState =reading;                 // Save the status of the button. 

      if(buttonState ==LOW) {                       // If the new button status is HIGH 
        ledState =!ledState;                         // Change the status of the LED.
      }
    }
  }
 
  digitalWrite(redLED,ledState);         // LEDs are on/off with values stored in ledState

  // Store the value of the reading variable in lastButtonState (used in the next loop)
  lastButtonState =reading;
}
