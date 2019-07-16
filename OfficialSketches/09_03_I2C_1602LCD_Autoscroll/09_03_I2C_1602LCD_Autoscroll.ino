/* Coding Array STARTER Kit for Arduino
 *   
 * CAK Starter Code 09_03_I2C_1602LCD_Autoscroll
 *
 *   This sketch shows that 1602 LCD uses I2C communicati
 *  Numbers from 0 to 9 are displayed on the screen
 *  Use the autoscroll( ) and noAutoscroll( ) methods.
 *  Show how to move all strings left or right.
 *  
 *  made by Arduinostory
 *  we@arduinostory.com

 */
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Set the LCD I2C address. Use 16 Space 2-line LCD. 
                                 
void setup(){
  lcd.init();
  lcd.backlight();                // Turn on the backlight. (lcd.noBacklight() turns off the backlight.) 
  
}


void loop() {
  
  lcd.setCursor(0,0);                         //Position the cursor (0,0) in the upper left corner. 
  
  for(int thisChar = 0; thisChar <10; thisChar++) {     
    lcd.print(thisChar);                      // The numbers from 0 to 9 are shown on the LCD. 
    delay(500);                               //  For 0.5 Second 
  }

  lcd.setCursor(16,1);                       // Position the cursor in the lower right hand corner. 
  
  lcd.autoscroll();                          // Set to auto-scroll 
  
  for(int thisChar = 0; thisChar <10; thisChar++) {
    lcd.print(thisChar);                     // The numbers from 0 to 9 are shown on the LCD..
    delay(500);                              //  For 0.5 Second 
  }
 
  lcd.noAutoscroll();                        // Automatic Scroll Revocation

  lcd.clear();                                // Clear the screen before going to the next loop.


}
