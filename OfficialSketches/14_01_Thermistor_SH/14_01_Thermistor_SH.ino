/* Coding Array STARTER Kit for Arduino

    CAK Starter code 14_01_Thermistor_SH
    This sketch converts the voltage distributed to the thermistor connected to the A4 into a resistor.
    One of the ways to change the resistance value to temperature 
    Use the Steinhart-Hart formula to calculate the temperature. 
    The A4 pin and I2C LCD module cannot be used together and must be selected as a jumper.

    made by Arduinostory
    we@arduinostory.com
*/

#include <math.h>


const int thermistorPin = A4;   // connect thermistor to A4 pin 


//parameters can vary the value depending on the module.
double ParamA = 0.001129148;
double ParamB = 0.000234125;
double ParamC = 0.0000000876741;


void setup() {
  // initiate serial communication at 9600 speeds 
  Serial.begin(9600);

}


void loop() {

  int readVal = analogRead(thermistorPin);
  double temp = Thermistor(readVal);                 // recall temperature measurement function

  double tempC = temp - 273.15;                     //Convert Absolute Temperature to Celsius 
  double tempF = (tempC * 9.0) / 5.0 + 32.0;         //Convert temperature to Fahrenheit 

  // Output Serial Monitor 
  //Serial.println(readVal);
  
  Serial.print(tempC);      // display temperature 
  Serial.println(" C");

  delay (500);
}

// set Steinhart-Hart temperature measurement function

double Thermistor(int RawADC)
{
  double Temp;
  Temp = log (10000.0 * ((1024.0 / RawADC - 1)));
  Temp = 1 / (ParamA + ( ParamB + (ParamC * Temp * Temp )) * Temp );
  
  return Temp;
}
