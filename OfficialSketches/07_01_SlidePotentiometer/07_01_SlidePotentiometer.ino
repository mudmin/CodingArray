/* Coding Array STARTER Kit for Arduino

/*  CAK Starter Code 07_01_SlidePotentiometer
 
    Change the resistance value by pushing the variable resistance from side to side. 
    As the resistance changes, 0 to 1023 analog values are entered as A0 pins. 
    Analog values are converted to voltages and expressed as values on the serial monitor.
    Can use a serial plotter to express it in graphs. 

    made by Arduinostory
    we@arduinostory.com
*/

const int potentiometerPin = A0;  // Output value of variable resistance is read from A0 
const int redLED = 13;
const int threshold = 400;

void setup() {
  pinMode (redLED, OUTPUT); // Set red LED to output
  Serial.begin(9600);      // Starts serial communication at 9600 speed 
  // Analog input/output pins need not be declared.. 
}

void loop() {

  int analogValue = analogRead(potentiometerPin);    // Read the analog value of variable resistance and store it in analogValue
  // AnalogValue stores integer values in the range 0 to 1023. 

  float voltage = analogValue * (5.0 / 1023.0);   //Convert Analog Readings to Volts 0 to 5 V 
  // Store in float variable because the math result value is real 

  //Serial.print("Analog Value : ")
  //Serial.println(analogValue);                    // Indicate the value of analogValue one line in the serial
  Serial.print("Voltage : ");
  Serial.println(voltage);                        // Print the converted voltage value one line in the serial window 

  if (analogValue > threshold) {    // If the value stored in analogValue is greater than 400
    digitalWrite(redLED, HIGH);     // Turn on the LED. 
  } else {                          // If the value stored in analogValue is less than or equal to 400
    digitalWrite(redLED, LOW);      // Turn off the LED. 

    delay(1);                        // Wait 1 millisecond to read reliably

  }
}
