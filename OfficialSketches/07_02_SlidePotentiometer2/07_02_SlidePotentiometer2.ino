/* Coding Array STARTER Kit for Arduino

   CAK Starter Code 07_02_SlidePotentiometer2

   As the variable resistance value increases, the color of the RGB LED changes to red->green->blue

    made by Arduinostory
    we@arduinostory.com
*/

int potPin = A0;           // Output of variable resistance connected to analogue pin A0 
int potVal = 0;           // Variables that store analog (0-1023) values read from variable resistance 

const int redPin = 9;          // Red LED No. 9 
const int greenPin = 10;       // Green LED No. 10 
const int bluePin = 11 ;       // Blue LED No. 11 

int redV = 0;                   // Set red LED analog value (0-255)
int greenV = 0;                 // Set green LED analog value (0-255) 
int blueV = 0;                  // Set blue LED analog value (0-255)

void setup() {
  pinMode(redPin, OUTPUT);   // Set pin 9 to output
  pinMode(greenPin, OUTPUT); // Set pin 10 to output
  pinMode(bluePin, OUTPUT);  // Set pin 11 to output
}

void loop() {
  potVal = analogRead(potPin);              // The analog output value of variable resistance is read from the A0 pin (0-1023).
  int ledLevel = map(potVal, 0, 1023, 0, 255); // Converts the analog input value to the analog output value (0-255) 

  if (potVal < 341){  // When the value of variable resistance is 1 divided into three stages (0-340)
    redV = 255 - ledLevel;      // The red is getting lighter 
    greenV = ledLevel;          // The green is getting darker
    blueV = 1;                  // Blue has no effect 
  }

  else if (potVal < 682) { // When the value of variable resistance is 2 divided into three stages (341-681)
    redV = 1;                           // Red has no effect 
    greenV = 255 - ledLevel;            //The green is getting lighter 
    blueV = ledLevel;                   // The blue is getting darker 
  }

  else { // When the value of variable resistance is 3 divided into three stages (682-1023)
    redV = ledLevel;                     // The Red is getting darker
    greenV = 1;                          // Green has no effect 
    blueV = 255 - ledLevel;              // The blue is getting lighter 
  }

  analogWrite(redPin, redV);            // Write values to red pins
  analogWrite(greenPin, greenV);        // Write values to green pins
  analogWrite(bluePin, blueV);          // Write values to blue pins
}
