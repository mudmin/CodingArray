/* Coding Array STARTER Kit for Arduino
 *   
 * CAK Starter Code 09_02_I2C_1602LCD_HelloCAK
 *    
 *  This sketch shows Hello ! ^_^ ! Coding Array Kit for 1602 LCDs using I2C communication 
 *  Show the string, using scrollDisplayRight and scrollDisplayLeft methods 
 *  Scrolls to the left and right. 
 *  Flashes the screen using noDisplay and discaly method to indicate that one loop is complete. 
 *  
 *  made by Arduinostory
 *  we@arduinostory.com
 */
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Set the LCD I2C address. Use 16-kan2 line LCD. 
                                    // Put the scanned address instead of 0x27. 
void setup(){
  lcd.init();
  lcd.backlight();                //  Turn on the backlight. (lcd.noBacklight() turns off the backlight.) 
  lcd.setCursor(0,0);                 // first line first column
  lcd.print("Hello ! ^_^ !");
  lcd.setCursor(0,1);                // 2nd line first column 
  lcd.print("Coding Array Kit");
  delay(1000);
}

void loop(){
/*
  // Scroll 16 length of string to the left             
  for(int positionCounter = 0; positionCounter < 16; positionCounter++) {
                                              
    lcd.scrollDisplayLeft();                           // Scroll to the left by one position 
                                                       
    delay(200);                                        // for 200 milliseconds 
  }

  // String length 16+ Rows 16 Scroll to the right at a total of 32 locations 
  for(int positionCounter = 0; positionCounter < 32; positionCounter++) {
                         
    lcd.scrollDisplayRight();                          // Scroll to the left by one position
                                                       
    delay(200);                                       // for 200 milliseconds 
  }

  // Scroll to the left 16 positions to center 
  for(int positionCounter = 0; positionCounter < 16; positionCounter++) {
    
    lcd.scrollDisplayLeft();                          //  Scroll to the left by one position 
    // wait a bit:
    delay(200);                                       // for 200 milliseconds 
  }



  // noDisplay and dispaly
  lcd.noDisplay();   // Turn off the screen 
  delay(500);       // for 0.5 second 
 
  lcd.display();      // Turn on the screen 
  delay(500);        // for 0.5 second 
*/
}
