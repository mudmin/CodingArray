/* Coding Array STARTER Kit for Arduino

   CAK Starter Code 09_06_I2C_1602LCD_SerialDisplay

/*  This sketch shows that 1602 LCD uses I2C communication. 
    Try printing the entered characters in the serial window.

    made by Arduinostory
    we@arduinostory.com
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address. Use 16 Space 2-line LCD. 

void setup() {
  lcd.init();
  lcd.backlight();                // Turn on the backlight. (lcd.noBacklight() turns off the backlight.) 
  lcd.write(12);
  Serial.begin(9600);                        // Starts serial communication at 9600 speed 
}

void loop() {

  if (Serial.available()) {   // When the text arrives on the serial communication, 

    delay(100);                // Wait 0.1 seconds for the entire message to arrive.

    lcd.clear();               // Clear the screen. 

    while (Serial.available() > 0) { // while the text is coming in 

      lcd.write(Serial.read());        // Write the characters you read on the LCD. 
     
    }
  }

}
