/* Coding Array STARTER Kit for Arduino
 *   
 * CAK Starter Code 05_01_RGB_DigitalMixing
 *  
 *  RGB LEDs combine the three primary colors of red, green and blue to release a variety of colors. 
 *  Pin 910 and 11 are connected to pins that control red, green and blue LEDs respectively.
 *  In this example, we will use a common cathode RGB LED to find out the tri-circular mixture of light from the digital output. 
 *  
 *  
 *  made by Arduinostory
 *  we@arduinostory.com  
 */
 

const int redPin =9;           // Red LED No. 9
const int greenPin = 10;       // Green LED No.10
const int bluePin=11 ;         // Blue LED No.11 
 
void setup() {

   pinMode(redPin, OUTPUT);   // Set pin 9 to output 
   pinMode(greenPin, OUTPUT); // Set pin 10 to output 
   pinMode(bluePin, OUTPUT);  // Set pin 11 to output 

  Serial.begin(9600);         // 9600-speed serial communication start 
  
}


void loop() {
   Serial.println("RED on");        //  Red LED illuminated 
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,LOW);
    delay(1000);                    //  for a second 

    Serial.println("GREEN on");       // Green LED illuminated
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH);
    digitalWrite(bluePin,LOW);
    delay(1000);                      //  for a second 

    Serial.println("BLUE on");        // Blue LED illuminated 
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,HIGH);
    delay(1000);                     //  for a second     

    Serial.println("Yellow on");      // Yellow LED illuminated 
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,HIGH);
    digitalWrite(bluePin,LOW);
    delay(1000);                      //  for a second 

    Serial.println("Magenta on");     // Magenta LED illuminated 
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,HIGH);
    delay(1000);                      //  for a second  

   Serial.println("Cyan on");         // Cyan LED illuminated 
   digitalWrite(redPin,LOW);
   digitalWrite(greenPin,HIGH);
   digitalWrite(bluePin,HIGH);
   delay(1000);                       //  for a second 

   Serial.println("White on");        // White LED illuminated 
   digitalWrite(redPin,HIGH);
   digitalWrite(greenPin,HIGH);
   digitalWrite(bluePin,HIGH);
   delay(1000);                       //  for a second 
}
