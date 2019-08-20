//Note: Very slight changes in the little potentiometer on the microphone will make a big difference in responsiveness

#include <Arduino.h>      //Used Primarily for Platform IO
#include "pitches.h"      //To create sounds and tones from the buzzer
#include <Wire.h>         //Used to communicate with I2C devices like the LCD
#include <Servo.h>        //the little servo motor
Servo myservo;
#include <DHT.h>          //Temperature & Humidity Sensor
#define DHTPIN 12         //Temp & Humidity sensor pin
#define DHTTYPE DHT11     //There are multiple types of DHT Sensors, CA uses DHT11
#define buz 6             //Buzzer pin
DHT dht(DHTPIN, DHTTYPE);
#include <LiquidCrystal_I2C.h>        //Special library for the LCD screen
LiquidCrystal_I2C lcd(0x27, 16, 2);   //The address of the LCD Screen and how many columns/rows it has

//This is Dan's interactive mode.
//0 is the default mode where everything works as normal in the Everything together sketch
//1 will accept input from Node-red or the serial monitor's input.
int mode = 0;

//sounds for switching modes
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

///////////////////////////
//this section tells the Arduino what pins the sensors are connected to


int echo = 4;             //Ultrasonic sensor echo pin
int trigger = 5;          //Ultrasonic sensor trigger pin
int touch = 7;            //Touch module
int pushbutton = 8;       //Tactile pushbutton
int red = 9;              //RGB LED Red pin
int green = 10;           //RGB LED Green pin
int blue = 11;            //RGB LED Blue pin
int dhtsensor = 12;       //DHT 11 Temperature & Humidity Sensor
int led = 13;             //The single color led is connected to pin 13
int hall = A2;            //Hall Effect(Magnetic Sensor)



//end pin declarations
//////////////////////////

//We are going to create some variables here that will hold data lower in the sketch
//These top ones basically keep track of time to determine how often a sensor should be checked
long mil = 0;
long ledt = 0;
long buzt = 0;
long lcdt = 0;
long dist = 0;
long lit = 0;
long analogt =0;
long mict = 0;

float temp, humi;
unsigned long dura = 0;
float dst = 0;
int leds = 0;
int bar = 0;
int oldbar = 0;         //The previous reading of the sliderbar
int touchwas = false;   //Save whether the touch sensor was last in a touched or not state
int touched = 0;
//Microphone (You can adjust sensitivity with the screw)
const int sampleWindow = 125; // sample period milliseconds (125 mS = 8 Hz)
int soundValue = 0;         // store the value of the sound sensor
double threshold = 2.0;         // set clapping sound threshold voltage value

//These variables are used to receive data from the PC/Raspberry Pi
const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

//The code in the setup function is run once on boot
void setup() {
  Serial.begin(9600);           //Setup the serial port to begin at 9600bps
  Serial.println("mode=Standard Mode");
  //Give the Arduino some basic information on what the pins we declared above actually do
  pinMode(echo, INPUT);         //Ultrasonic sensor echo pin
  pinMode(trigger, OUTPUT);     //Ultrasonic sensor trigger pin
  pinMode(touch, INPUT);        //Touch Module
  pinMode(pushbutton, INPUT);   //Tactile Pushbutton
  pinMode(red, OUTPUT);         //RGB Red LED
  pinMode(green, OUTPUT);       //RGB Green LED
  pinMode(blue, OUTPUT);        //RGB Blue LED
  pinMode(led, OUTPUT);         //Single Color LED


  myservo.attach(3);           //Tell the servo library which pin the servo is connected to
  dht.begin();                 //Start the temperature and humidity sensor

  myservo.write(180 - int(bar / 5.68));

  lcd.init();                  //Startup the LCD
  lcd.backlight();             //Turn on the LCD baclight

  bar = analogRead(A0);        //Read the position of the slider bar once on boot
  intro();                     //Run the intro function (defined below) that runs on boot

  makeIcon();                  //Call the functions that display the boot animation on the LCD Screen
  drawIcon();
}



void loop() {
  //The number of milliseconds since the Arduino booted
  mil = millis();


  if(analogRead(hall) < 480){  //look for a magnet near the hall effect sensor if one is found
    if(mode == 0){             //if you are in mode 0, switch to 1
      mode = 1;
    }else{
      mode = 0;
    }
    changeMode() ;                    //Play a tone
    delay(1000);                      //Give time to take the magnet away
    lcd.clear();                      //Reset the screen
    lcd.setCursor(0, 0);
    if(mode == 0){
      lcd.print("Standard");
      Serial.println("mode=Standard Mode");
    }else{
      lcd.print("Interactive");
      Serial.println("mode=Interactive Mode");
      bar = analogRead(A0); //Get the inital position of the slider bar
      myservo.write(180 - int(bar / 5.68));
      Serial.print("bar=");
      Serial.println(bar);
    }
    lcd.setCursor(0, 1);
    lcd.print("Mode Activated");
    delay(1000);
    if(mode == 0){
      makeIcon();
      drawIcon();
    }else{
      lcd.clear();                      //Reset the screen
      lcd.setCursor(0, 0);
    }
  }



  if(mode == 0){
    standard();
  }else{
    interactive();
  }

}

void both(){
  //We are going to try not to repeat ourselves too much in this code, so anything that will work in both "modes" will go in here.

  //Set up some variables that get cleared out every time the code loops over
  float Duration, Distance;

  //Ultrasonic Sensor Reading
  if (mil > dist) {
    dist = mil + 1000;
    digitalWrite(trigger, LOW);                                  //Make sure the trigger is off
    delayMicroseconds(2);                                        //Wait 2 microseconds
    digitalWrite(trigger, HIGH);                                 //Shoot off a pulse of ultrasound
    delayMicroseconds(10);                                       //Keep shooting for 10 microseconds
    digitalWrite(trigger, LOW);                                  //Stop shooting
    Duration = pulseIn(echo, HIGH);                              //See how long it took to receive the reflected sound
    Distance = ((float)(340 * Duration) / 10000) / 2;            //Calculate the distance based on the time it took to receive the signal
    if(mode == 0){                                                 //Only write to the LCD in Standard Mode
      lcd.setCursor(10, 1);                                        //Print the distance on the second (1) line of the LCD in the 10th position
      if (Distance < 100) {
        lcd.print(Distance, 10);
      } else {
        lcd.print(" ");
        lcd.print(int(Distance));
      }
      lcd.setCursor(14, 1);
      lcd.print("cm");                                              //Move the cursor and print cm
    } //end of preventing lcd write for Interactive mode
    Serial.print("dist=");                                        //Send Distance to Serial so the computer can read it
    Serial.println(Distance);
  }

  //Temperature & Humidity
  if (mil > lcdt) {
    lcdt = mil + 5000;                //Read the temperature every 5 seconds (5000 milliseconds)
    temp = dht.readTemperature();     //Read the temperature sensor and assign it to the temp variable
    humi = dht.readHumidity();        //Get the humidity and assign it to the humi variable
    if(mode == 0){ //only write to the LCD in Standard Mode
      lcd.setCursor(3, 0);              //Move the cursor to the top row (0), 3rd position

      if (temp < 10) {                  //If temp < 10 put a space to make the spacing nice on the screen
        lcd.print(" ");
      }
      lcd.print(int(temp));             //Print the temperature to the screen
      lcd.setCursor(11, 0);             //Move the cursor to the top row, 11th position

      if (humi < 10) {
        lcd.print(" ");                 //Add a space if the humidity is less than 10%
      }
      lcd.print(int(humi));             //Print the humidity to the lcd
    }//end of Standard Mode loop
    Serial.print("temp=");              //Send temperature and humidity to serial monitor
    Serial.println(temp);
    Serial.print("hum=");
    Serial.println(humi);
  }

  //Photocell (measure light)
  if (mil > lit) {
    lit = mil + 2000;                 //Measure light every 2 seconds (2000 milliseconds)
    Serial.print("photo=");         //Prepare to send photo sensor reading
    lcd.setCursor(0, 1);              //Set the cursor to the left side of the second line (1)
    if (analogRead(A1) > 700) {
      if(mode == 0) {
        lcd.print("Bright   "); //If you get a reading of > 700, write Bright on the LCD
      }
      Serial.println("Bright");

    } else if (analogRead(A1) > 550) {
      if(mode == 0) {
        lcd.print("Normal   ");            //If the reading is > 550 and < or = to 700, write Normal
      }
      Serial.println("Normal");
    } else {
      if(mode == 0) {
        lcd.print("Dark     ");            //If the reading is below 500, write Dark
      }
      Serial.println("Dark");
    }
  }

  if(mil > mict){
    mict = mil + 300;
    unsigned long start= millis();  // start sampling
    unsigned int peakToPeak = 0;    // Amplitude Value Variables
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;


    // collect data for 125 milliseconds.
    while (millis() - start < sampleWindow)
    {
      soundValue = analogRead(3); // specify analogue pin number 3.
      if (soundValue < 1024)  // Read data up to the ADC maximum (1024=10bit).
      {
        if (soundValue > signalMax)
        {
          signalMax = soundValue;  // Store the maximum sound value in the signalMax variable.
        }
        else if (soundValue < signalMin)
        {
          signalMin = soundValue;  // store the sound minimum in the variable (signalMin).
        }
      }
    }
    peakToPeak = signalMax - signalMin;  // calculate peak-to-peak amplitude
    double volts = (peakToPeak * 5.0) / 1024; // convert the ADC value to a voltage value. Reference Voltage 5V
    //let's increase the bottom a little bit
    if(volts < 1.5){
      volts = volts*3;
    }else{
      volts = volts *2;
    }
    if(volts <= 1){
      Serial.println("sound=0");
    }else if(volts > 1 && volts <=2){
      Serial.println("sound=1");
    }else if(volts > 2 && volts <=3){
      Serial.println("sound=2");
    }else if(volts > 3 && volts <=4){
      Serial.println("sound=3");
    }else if(volts > 4 && volts <=5){
      Serial.println("sound=5");
    }
  }
}

void standard(){ //This is the standard "mode" that coding array boots into
both(); //run the code that is common to both modes;
//Read the position of the slider bar
bar = analogRead(A0);


//Move the servo based on the position of the slider bar
myservo.write(180 - int(bar / 5.68));

//Pushbutton - If the button is pushed, light up the single led. If not, turn it off
//Buzzer - If the button is pushed, play a quick tone
if (digitalRead(pushbutton) == HIGH) {
  digitalWrite(led, HIGH);
  tone(buz, bar * 1.3 + 50, 40);
} else {
  digitalWrite(led, LOW);
}

//RGB led
//If either the touch sensor is touched scroll through the RGB LED, otherwise, turn it off
if (digitalRead(touch) == HIGH) {
  if (mil > ledt) {
    if(touchwas == false){    //check whether this is different than last time
      Serial.println("touch=true");
      touchwas = true;
    }

    ledt = mil + 120;
    leds++;
    if (leds == 1) {
      digitalWrite(9, HIGH);
      digitalWrite(11, LOW);
    } else if (leds == 2) {
      digitalWrite(10, HIGH);
      digitalWrite(9, LOW);
    } else {
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
    }
    if (leds == 3) {
      leds = 0;
    }
  }
} else {
  if(touchwas == true){    //check whether this is different than last time
    Serial.println("touch=false");
    touchwas = false;
  }
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

}


void interactive(){  //This is the interactive mode!
  both(); //run the code that is common to both modes;
  recvWithStartEndMarkers();  //Look for new data coming in from the serial monitor/pi/pc
  showNewData();  //Parse and show the data received

  if (mil > analogt) {
    bar = analogRead(A0);
    if(bar != oldbar){ //check the previous reading
      myservo.write(180 - int(bar / 5.68));
      Serial.print("bar=");
      Serial.println(bar);
      oldbar = bar; //save this new reading
    }
    touched = digitalRead(touch);
    if(touched == 0 && touchwas == true){
      Serial.println("touch=false");
      touchwas = false;
    }else if(touched == 1 && touchwas == false){
      Serial.println("touch=true");
      touchwas = true;
    }
    analogt = mil + 1000; //tell the loop to read the analog sensor again in one second
  }
}

//This is the intro function that gets called once on boot.  It does the little animations on the LCD
void intro() {
  const static uint8_t storyYang[] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0x6, 0x5,
    0x7, 0xc, 0x18, 0x10, 0x12, 0x12, 0x10, 0x3,
    0x1c, 0x6, 0x3, 0x1, 0x9, 0x9, 0x1, 0x18,
    0, 0, 0, 0, 0, 0, 0xc, 0x14,
    0x2, 0x2, 0x3, 0x1, 0, 0, 0, 0,
    0x2, 0x1, 0, 0x1b, 0xa, 0xa, 0x6, 0,
    0x8, 0x10, 0, 0x1b, 0xa, 0xa, 0xa, 0x6,
    0x8, 0x8, 0x18, 0x10, 0, 0, 0, 0
  };

  const static uint8_t arm_0[] PROGMEM = {0, 0, 0, 0, 0, 0, 0x3, 0x5};
  const static uint8_t arm_3[] PROGMEM = {0, 0, 0, 0, 0, 0, 0x18, 0x14};
  const static uint8_t mouse_5[] PROGMEM = {0x2, 0x1, 0, 0x1b, 0xa, 0xa, 0xa, 0x6};
  const static uint8_t mouse_6[] PROGMEM = {0x8, 0x10, 0, 0x1b, 0xa, 0xa, 0x6, 0};

  const static uint8_t story[] PROGMEM = {
    0, 0, 8, 8, 12, 8, 8, 8, //ㅏ
    0, 0, 31, 16, 16, 16, 15, 0, //ㄷ
    0, 0, 8, 8, 8, 8, 8, 8, //ㅣ
    0, 0, 16, 16, 16, 16, 15, 0, //ㄴ
    0, 0, 4, 4, 10, 17, 0, 0, //ㅅ
    0, 0, 31, 16, 31, 16, 15, 0, //ㅌ
    0, 0, 30, 1, 31, 16, 15, 0, //ㄹ
    0, 4, 4, 31, 0, 0, 0, 0 //ㅗ
  };

  const static char story_str_0[] PROGMEM = {
    'o', 0, 1, 32, 'o', 2, 3, 32, 4, 32, 5, 32, 6, 2
  };

  const static char story_str_1[] PROGMEM = {
    32, 32, 'T', 32, 32, 32, 7, 32, 0xb0, 32, 7, 32, 32, 32
  };

  const static uint8_t kit[] PROGMEM = {
    0, 0, 31, 1, 1, 31, 1, 5, //ㅋ
    0, 0, 15, 8, 8, 8, 7, 0, //ㄷ
    0, 8, 8, 8, 8, 8, 8, 8, //ㅣ
    0, 8, 8, 8, 24, 8, 8, 8, //ㅓ
    0, 0, 31, 1, 31, 16, 31, 0, //ㄹ
    0, 10, 10, 10, 26, 10, 10, 10, //ㅔ
    4, 31, 0, 0, 0, 0, 0, 0, //ㅗ
    0, 31, 0, 0, 0, 0, 0, 0 //ㅡ
  };

  const static char kit_str_0[] PROGMEM = {
    0, 1, 2, 'o', 3, 4, 5, 'o', 2, 0xa6, 2, 'E'
  };

  const static char kit_str_1[] PROGMEM = {
    6, 32, 'o', 32, 32, 32, 32, 32, 32, 32, 32, 7
  };

  int i, x;
  uint8_t temp[8];

  #define CREATECHAR(addr, bitmap) \
  memcpy_P(temp, bitmap + addr * 8, 8); \
  lcd.createChar(addr, temp);

  for (i = 0; i < 8; i++) {
    CREATECHAR(i, storyYang)
  }

  for (i = 0; i < 8; i++) {
    if (i == 0)
    lcd.setCursor(2, 0);
    else if (i == 4)
    lcd.setCursor(2, 1);
    lcd.write((char)i);
  }

  lcd.setCursor(7, 0);
  lcd.print("Arduino");

  lcd.setCursor(8, 1);
  lcd.print("Story");

  for (i = 0; i < 6; i++) {
    if ((i & 1) == 0) {
      memcpy_P(temp, arm_0, 8);
      lcd.createChar(0, temp);
      memcpy_P(temp, arm_3, 8);
      lcd.createChar(3, temp);
      memcpy_P(temp, mouse_5, 8);
      lcd.createChar(5, temp);
      memcpy_P(temp, mouse_6, 8);
      lcd.createChar(6, temp);
    } else {
      CREATECHAR(0, storyYang)
      CREATECHAR(3, storyYang)
      CREATECHAR(5, storyYang)
      CREATECHAR(6, storyYang)
    }
    lcd.setCursor(2 + 0, 0);
    lcd.write((char)0);
    lcd.setCursor(2 + 3, 0);
    lcd.write((char)3);
    lcd.setCursor(2 + 1, 1);
    lcd.write((char)5);
    lcd.write((char)6);
    delay(500);
  }

  for (i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write((char)255);
    lcd.setCursor(i, 1);
    lcd.write((char)255);
    delay(70);
  }

  x = (16 - sizeof(story_str_0)) / 2;
  for (i = 0; i < 8; i++) {
    CREATECHAR(i, story)
  }
  for (i = 0; i < 16; i++) {
    if (i < x || i >= (x + sizeof(story_str_0))) {
      lcd.setCursor(i, 0);
      lcd.write((char)32);
      lcd.setCursor(i, 1);
      lcd.write((char)32);
    } else {
      lcd.setCursor(i, 0);
      lcd.write(pgm_read_byte(story_str_0 + i - x));
      lcd.setCursor(i, 1);
      lcd.write(pgm_read_byte(story_str_1 + i - x));
    }
    delay(70);
  }

  delay(100);

  for (i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.write((char)255);
    lcd.setCursor(i, 1);
    lcd.write((char)255);
    delay(70);
  }

  x = (16 - sizeof(kit_str_0)) / 2;
  for (i = 0; i < 8; i++) {
    CREATECHAR(i, kit)
  }
  for (i = 0; i < 16; i++) {
    if (i < x || i >= (x + sizeof(kit_str_0))) {
      lcd.setCursor(i, 0);
      lcd.write((char)32);
      lcd.setCursor(i, 1);
      lcd.write((char)32);
    } else {
      lcd.setCursor(i, 0);
      lcd.write(pgm_read_byte(kit_str_0 + i - x));
      lcd.setCursor(i, 1);
      lcd.write(pgm_read_byte(kit_str_1 + i - x));
    }
    delay(70);
  }
}

//This function makes the little icons that display on the LCD during the temperature/humidity readings
void makeIcon() {
  const static uint8_t icon_temp0[] PROGMEM = {
    0x4, 0xa, 0xa, 0xe, 0xe, 0x1f, 0x1f, 0xe
  };
  const static uint8_t icon_temp1[] PROGMEM = {
    0x8, 0x14, 0x8, 0x3, 0x4, 0x4, 0x3, 0
  };
  const static uint8_t icon_temp2[] PROGMEM = {
    0xc, 0x12, 0x12, 0xc, 0, 0, 0, 0
  };
  const static uint8_t icon_humi[] PROGMEM = {
    0x4, 0x4, 0xa, 0xa, 0x11, 0x11, 0x11, 0xe
  };
  const static uint8_t icon_sonar[] PROGMEM = {
    0x2, 0x9, 0x5, 0x15, 0x15, 0x5, 0x9, 0x2
  };

  uint8_t temp[8];
  memcpy_P(temp, icon_temp0, 8);
  lcd.createChar(0, temp);

  memcpy_P(temp, icon_temp1, 8);
  lcd.createChar(1, temp);

  memcpy_P(temp, icon_temp2, 8);
  lcd.createChar(2, temp);

  memcpy_P(temp, icon_humi, 8);
  lcd.createChar(3, temp);

  memcpy_P(temp, icon_sonar, 8);
  lcd.createChar(4, temp);
}

//This puts the icons on the right place on the screen
void drawIcon() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.write(0);
  //  lcd.setCursor(5, 0);
  //  lcd.write(1);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.write('C');
  lcd.setCursor(9, 0);
  lcd.write(3);
  lcd.setCursor(13, 0);
  lcd.write('%');
  lcd.setCursor(9, 1);
  lcd.write(4);
  lcd.setCursor(14, 1);
  lcd.print("cm");
}


//Play the mario tune!
void mario() {
  #define REST     1
  // TONES  ==========================================
  // notes in the melody:
  int Mario_melody[] = {
    NOTE_E4, NOTE_E4, REST, NOTE_E4,
    REST, NOTE_C4, NOTE_E4, REST,
    NOTE_G4, REST, REST, NOTE_G3, REST,

    NOTE_C4, REST, REST, NOTE_G3,
    REST, NOTE_E3, REST,
    REST, NOTE_A3, REST, NOTE_B3,
    REST, NOTE_AS3, NOTE_A3, REST,

    NOTE_G3, NOTE_E4, NOTE_G4,
    NOTE_A4, REST, NOTE_F4, NOTE_G4,
    REST, NOTE_E4, REST, NOTE_C4,
    NOTE_D4, NOTE_B3, REST
  };

  int Mario_Notes[] = {
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 2, 4, 2, 2,

    4, 4, 4, 4,
    2, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4,

    4, 2, 4,
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 2
  };

  const int num_elements_in_arr = sizeof(Mario_Notes) / sizeof(Mario_Notes[0]);

  for (int thisNote = 0; thisNote < num_elements_in_arr; thisNote++) // 슈퍼마리오 멜로디 톤 발생
  {
    if (digitalRead(7)) {
      break;
    }
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 500 / Mario_Notes[thisNote];
    tone(buz, Mario_melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    //notone(6);
  }

}

//Play the tetris tune!
void tetris() {
  /*A Theme - Tetris
  with Bass
  Uses Arduino tone library pitches.h [http://arduino.cc/en/Tutorial/tone ]
  by electricmango
  https://electricmango.github.io

  Thanks to Gori Fater for uploading the sheet music on Google.
  http://www.gamemusicthemes.com/sheetmusic/gameboy/tetris/

  Version 1.0.4
  -------------------------------------------------------------------------
  A Theme - Tetris with Bass is licensed under the

  Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)

  You are free to:
  Share — copy and redistribute the material in any medium or format
  Adapt — remix, transform, and build upon the material
  for any purpose, even commercially.
  The licensor cannot revoke these freedoms as long as you follow the license terms.
  Under the following terms:
  Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
  ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.
  No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.
  The full license is available at https://creativecommons.org/licenses/by-sa/4.0/legalcode

  Copyright (c) 2012 ~ 2015 electricmango
  -------------------------------------------------------------------------
  A_Theme___Tetris_with_Bass.ino

  Changed to use progmem
  */

  //notes in the melody:
  const static int melody[] PROGMEM = { /* Changed to use progmem */
    NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
    NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
    NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
    NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
    NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
    NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
    NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
    NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
    NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
    NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
    NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
    NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
    NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
    NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
    NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
    NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
    NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
    NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
    NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3,
    NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
  };

  //note durations: 4 = quarter note, 8 = eighth note, etc
  const static int noteDurations[] PROGMEM = { /* Changed to use progmem */
    8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 4, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
    8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 4, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 4, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
    8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 4, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  };

  //iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < (sizeof(melody) / sizeof(int)); thisNote++) {

    if (digitalRead(7)) { /* Changed to exit melody */
      break;
    }
    /*
    to calculate the note duration, take one second divided by the note type.
    e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    */
    int noteDuration = 1000 / pgm_read_word(&noteDurations[thisNote]); /* Changed to use progmem */
    tone(buz, pgm_read_word(&melody[thisNote]), noteDuration);

    /*
    to distinguish the notes, set a minimum time between them.
    the note's duration + 30% seems to work well:
    */
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    //notone(6); //stop the tone playing:
  }
  digitalWrite(6, LOW);
}


void changeMode(){
  //Play the sound for changing modes
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buz, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    //notone(6);
  }
}

void recvWithStartEndMarkers() {  //This function processes serial input from the Serial monitor, Pi, or PC
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}


void showNewData() {
  if (newData == true) {
    if(strcmp(receivedChars, "ledon") ==  0){
      digitalWrite(led,HIGH);
    }
    if(strcmp(receivedChars, "ledoff") ==  0){
      digitalWrite(led,LOW);
    }

    if(strcmp(receivedChars, "mario") ==  0){
      mario();
    }

    if(strncmp(receivedChars, "r=",2) ==  0){
      char* r = receivedChars + 2;
      int rd = atoi(r);
      analogWrite(red,rd);
      Serial.print("red-");
      Serial.println(rd);
    }
    if(strncmp(receivedChars, "g=",2) ==  0){
      char* g = receivedChars + 2;
      int gr = atoi(g);
      analogWrite(green,gr);
      Serial.print("green-");
      Serial.println(gr);
    }
    if(strncmp(receivedChars, "b=",2) ==  0){
      char* b = receivedChars + 2;
      int bl = atoi(b);
      analogWrite(blue,bl);
      Serial.print("blue-");
      Serial.println(bl);
    }

    if(strncmp(receivedChars, "y=",2) == 0){
      char* screen = receivedChars + 2;
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print(screen);

    }

    if(strncmp(receivedChars, "z=",2) == 0){
      char* screen = receivedChars + 2;
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(screen);
    }

    if(strncmp(receivedChars, "math=",5) == 0){
      char* screen = receivedChars + 5;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Answer:");
      lcd.setCursor(0, 1);
      lcd.print(screen);
    }

    newData = false;
  }
}
