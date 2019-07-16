/* Coding Array STARTER Kit for Arduino
 *   
 * CAK Starter Code 09_04_I2C_1602LCD_TextDirection
 * 
 *  This sketch shows that 1602 LCD uses I2C communication. 
 *  Show one alphabet from a to Z. 
 *  'a through l' is written from left to right.
 *  'm through r' is written from right to left 
 *   's through z' causes text to appear from left to right again
 *  
 *  made by Arduinostory
 *  we@arduinostory.com *  
 */
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Set the LCD I2C address. Use 16 Space 2-line LCD. 
                                    
int thisChar ='a';                                     // thisChar Save                                      

void setup(){
  lcd.init();
  lcd.backlight();                // Turn on the backlight. (lcd.noBacklight() turns off the backlight.) 
  lcd.cursor();                   // Turn on the cursor. 
}

void loop(){

  if(thisChar =='m') {                           // If thisChar is m, change direction.
    lcd.rightToLeft();                           // From the next letter, mark to the left.
  }

  if(thisChar =='s') {                           // If thisChar is s 
    // go left for the next letter              
    lcd.leftToRight();                           // From the next letter, mark to the left.
  }

  if(thisChar >'z') {                            // When thisChar is out of z, 
    // go to (0,0):
    lcd.home();                                  // Go to (0,0) 
    thisChar ='a';                               // Restart from the beginning 
  }

  lcd.write(thisChar);                 // Indicate thisChar value on LCD.
  
  delay(1000);                         // for a second 
  
  thisChar++;                          // increase thisChar value one by one 
}
