/* Coding Array STARTER Kit for Arduino
 *   
 * CAK Starter Code 05_02_RGB_LED_Fading
 *  
 *  In this example, we use a common cathode RGB LED 
 *  Pin 910 and 11 are connected to pins that control red, green and blue LEDs respectively. 
 *  Use the PWM (Pulse-Width Modulation) function to adjust the brightness of the LEDs.  
 *  The 'radom' command adjusts the brightness of the three colors of RGB to enable a variety of color blends.
 */
 
const int redPin =9;           // Red LED No. 9
const int greenPin = 10;       // Green LED No. 10 
const int bluePin=11 ;         // Blue LED No. 11 
 
int delayTime=30;           // Delay time setting

int redV;                     // Set red LED analog value (0-255) 
int greenV;                   // Set green LED analog value (0-255) 
int blueV;                    // Set blue LED analog value (0-255) 

int fadeAmount =5;            // fade storage variable 

void setup() {
  
   pinMode(redPin, OUTPUT);   // Set pin 9 to output 
   pinMode(greenPin, OUTPUT); // Set pin 10 to output    
   pinMode(bluePin, OUTPUT);  // Set pin 11 to output 

}


void loop() {
  //Red LED brightness adjustment
  greenV=0;                   
  blueV=0;                 
  for(redV =0; redV <=255;redV +=5) {  
                                               // Increase the value by 5 times from 0 to 255.
    analogWrite(redPin,redV);                    // Turn on the LED more and more and more. 
    analogWrite(greenPin,greenV);     
    analogWrite(bluePin,blueV); 
    delay(delayTime);                           // 30-millisecond wait 
  }

  for(int redV=255 ;redV >=0; redV -=5) {
                                               // Reducing the value by 5 times from 255 to 0. 
    analogWrite(redPin,redV);                   // Turn on the darker LEDs.
    analogWrite(greenPin,greenV);     
    analogWrite(bluePin,blueV);    
    delay(delayTime);                          // 30-millisecond wait 
  }

  
  //Green LED brightness adjustment 
   redV=0;                   
   blueV=0;  
  
  for(greenV=0  ; greenV <=255; greenV +=5) {  
                                               // Increase the value by 5 times from 0 to 255.
    analogWrite(redPin,redV);                     // Turn on the LED more and more and more. 
    analogWrite(greenPin,greenV);     
    analogWrite(bluePin,blueV);                           
    delay(delayTime);                            // 30-millisecond wait 
  }

  for(int greenV =255 ; greenV >=0; greenV -=5) {
                                               // Reducing the value by 5 times from 255 to 0. 
    analogWrite(redPin,redV);                   // Turn on the darker LEDs. 
    analogWrite(greenPin,greenV);     
    analogWrite(bluePin,blueV);    
    delay(delayTime);                          // 30-millisecond wait 
  }
  
  
  //Blue LED brightness adjustment 
  redV=0;                   
  greenV=0;  
  for(blueV=0 ; blueV <=255; blueV +=5) {  
                                               // Increase the value by 5 times from 0 to 255. 
    analogWrite(redPin,redV);                    // Turn on the LED more and more and more. 
    analogWrite(greenPin,greenV);     
    analogWrite(bluePin,blueV);               
              
    delay(delayTime);                                    // 30-millisecond wait 
  }

  for(int blueV=255 ;blueV >=0; blueV -=5) {
                                               // Reducing the value by 5 times from 255 to 0. 
    analogWrite(redPin,redV);                   // Turn on the darker LEDs. 
    analogWrite(greenPin,greenV);     
    analogWrite(bluePin,blueV);    
    delay(delayTime);                          // 30-millisecond wait 
  }  
  
//20 Random colors 
  for (int i=0; i<20; i++){
    analogWrite(redPin,random(0,255));                   
    analogWrite(greenPin,random(0,255));     
    analogWrite(bluePin,random(0,255));    
    delay(1000);
  }
}
