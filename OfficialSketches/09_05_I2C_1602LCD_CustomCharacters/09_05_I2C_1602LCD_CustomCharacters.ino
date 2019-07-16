/* Coding Array STARTER Kit for Arduino
 *   
 *  CAK Starter Code 09_05_I2C_1602LCD_CustomCharacters
 *  
 *  This sketch shows that 1602 LCD uses I2C communication. 
 *  Set up a special character or Figure to "I ♥ Array Kit !" and smile on the first line of the LCD. 
 *  In the second row, the shape of a person who raises and lowers his or her arms is displayed. 
 *  Learn how to indicate that the value of A0 variable resistance is constant. 

 *  made by Arduinostory
 *  we@arduinostory.com
 */
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Set the LCD I2C address. Use 16 Space 2-line LCD.


//Create special characters 
byte heart[8] ={
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte smiley[8] ={
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

byte frownie[8] ={
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};

byte armsDown[8] ={
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] ={
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

                                    
void setup(){
  lcd.init();
  lcd.backlight();                // Turn on the backlight. (lcd.noBacklight() turns off the backlight.) 
  
  //  Define New Characters 
  lcd.createChar(0,heart);                   
  lcd.createChar(1,smiley); 
  lcd.createChar(2,frownie);
  lcd.createChar(3,armsDown);
  lcd.createChar(4,armsUp);

  lcd.setCursor(0,0);                 // first line first column 
  
  
  // Write text to LCD 
  lcd.print("I ");
  lcd.write(byte(0));                           // Use a heart that is stored at 0 bytes.
  lcd.print(" Array Kit! ");
  lcd.write((byte)1);                           // Use a smiley stored in one byte.. 

}

void loop(){

  
  int sensorReading = analogRead(A0);       // Read the variable resistance value of A0. 
 
  int delayTime = map(sensorReading,0,1023,200,1000);  // Map resistance values from 200 to 1000 
  
  lcd.setCursor(4,1);                       //Set the cursor to the bottom 5th position 
  
  lcd.write(3);                             // Draw a person with his arm down on number 3. 
  delay(delayTime);                         // Delay by variable resistance value 
  lcd.setCursor(4,1);                       //Set the cursor to the bottom 5th position 
 
  //lcd.write(4);                             // Draw the person with the arm up stored in number 4. 
  delay(delayTime);                         // Delay by variable resistance value 
}
