/* Coding Array STARTER Kit for Arduino
 *   
 *  CAK Starter code 14_02_Thermistor_BParameter
 *  This sketch converts the voltage distributed to the thermistor connected to the A4 into a resistor. 
 *  One of the ways to change the resistance value to temperature
 *  Use the B parameter expression to calculate the temperature. 
 *  
 *  made by Arduinostory
 *  we@arduinostory.com
 *   
 */
 
#include <math.h>

                                   
const int thermistorPin=A4;     // connect thermistor to A4 pin 


//B parameter
float ParmB=3435.0;

void setup() {
  // initiate serial communication at 9600 speeds
  Serial.begin(9600);
  
  }


void loop() {
 
  float readVal =analogRead(thermistorPin);
 
  //calculate temperature 
  float resistor =(1023.0*10000)/readVal-10000;
  float tempC =(ParmB/(log(resistor/10000)+(ParmB/(273.15+25)))) -273.15;

  
// Output Serial Monitor 
 // Serial.println(readVal);      //output analog values read from Serial.println(readVal); A4 
  Serial.print(tempC);          // temperature output 
  Serial.println(" C");         // output units

  delay(1000);                       // 1 second delay 

}
