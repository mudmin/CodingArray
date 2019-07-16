/* Coding Array STARTER Kit for Arduino
 *   
 * CAK Starter Code 08_PassiveBuzzer
 *  
 *  This sketch plays a note through a buzzer connected to pin 6. 
 *  The * tone() function calls up the pitches.h header file to give a given frequency sound. 
 *  Play a familiar 'school bell' song to us. 
 *  In this sketch, the code is inserted in the setup part and played only once. 
 *   If the loop part is coded, the performance may be repeated.
 *  
 *  made by Arduinostory
 *  we@arduinostory.com

 */
 
#include "pitches.h"

int buzzer=6;            //Connect the Piezo buzzer to No. 6. 

                         //the pitch of playing 
int melody[] ={NOTE_G7,NOTE_G7,NOTE_A7,NOTE_A7,NOTE_G7,
                NOTE_G7,NOTE_E7,NOTE_G7,NOTE_G7,NOTE_E7,
                NOTE_E7,NOTE_D7,0,NOTE_G7,NOTE_G7,NOTE_A7,
                NOTE_A7,NOTE_G7,NOTE_G7,NOTE_E7,NOTE_G7,
                NOTE_E7,NOTE_D7,NOTE_E7,NOTE_C7,0
               };
                            //Sound length, 4 = crotchet, 2 = minim 
int noteDurations[] ={4,4,4,4,4,4,2,4,4,4,4,3,1,4,4,4,4,4,4,2,4,4,4,4,3,1};

void setup() {
  for(int thisNote =0; thisNote <26; thisNote++)
  {
    int noteDuration =1000 /noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);       //Connect the Piezo buzzer to No. 6 
    int pauseBetweenNotes =noteDuration *1.30;          //phonetic delimiting 
    delay(pauseBetweenNotes);                           //delay

    noTone(buzzer);                               //Stop playing music 
  }
}

void loop() {
}
