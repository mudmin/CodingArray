#include <Arduino.h>
#include "pitches.h"
#include <Wire.h>
#include <Servo.h>
Servo myservo;
#include <DHT.h>
#define DHTPIN 12
#define DHTTYPE DHT11
#define buz 6
DHT dht(DHTPIN, DHTTYPE);
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int threshold = 15;               // 거리 임계값 설정  (초음파 센서)


long mil = 0;
long ledt = 0;
long buzt = 0;
long lcdt = 0;
long dist = 0;
long lit = 0;
float temp, humi;
unsigned long dura = 0;
float dst = 0;
int leds = 0;
int bar = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);               // 5번에triger핀연결
  pinMode(4, INPUT);                // 4번 핀에 echo핀 연결
  myservo.attach(3);
  dht.begin();

  bar = analogRead(A0);
  bar = analogRead(A0);

  myservo.write(180 - int(bar / 5.68));

  lcd.init();
  lcd.backlight();
  //  lcd.setCursor(0, 0);
  //  lcd.print("Hello, world!");
  //  lcd.setCursor(0, 1);
  //  lcd.print("I'm Coding Array");

  intro();

  if (bar < 512) {
    mario();
  } else {
    tetris();
  }

  makeIcon();
  drawIcon();
}



void loop() {
  float Duration, Distance;

  // put your main code here, to run repeatedly:
  mil = millis();


  //가변저항 수치
  bar = analogRead(A0);


  //서보
  myservo.write(180 - int(bar / 5.68));



  //초음파 센서로 거리 측정
  if (mil > dist) {
    dist = mil + 200;
    digitalWrite(5, LOW);
    delayMicroseconds(2);
    digitalWrite(5, HIGH);                                     // 초음파 쏜다.
    delayMicroseconds(10);                                                 // 10밀리초 동안
    digitalWrite(5, LOW);                                      // 초음파 끈다.
    Duration = pulseIn(4, HIGH);                               // echo핀이 HIGH 유지한 시간 저장
    Distance = ((float)(340 * Duration) / 10000) / 2;          // 거리를 cm로환산
    lcd.setCursor(10, 1);
    if (Distance < 100) {
      lcd.print(Distance, 10);
    } else {
      lcd.print(" ");
      lcd.print(int(Distance));
    }
    lcd.setCursor(14, 1);
    lcd.print("cm");   // 단위출력
  }

  //택트스위치
  if (digitalRead(8) == HIGH) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }


  //온습도
  if (mil > lcdt) {
    lcdt = mil + 5000;
    lcd.setCursor(3, 0);
    temp = dht.readTemperature();
    if (temp < 10) {
      lcd.print(" ");
    }
    lcd.print(int(temp));
    lcd.setCursor(11, 0);
    humi = dht.readHumidity();
    if (humi < 10) {
      lcd.print(" ");
    }
    lcd.print(int(humi));
  }

  //조도측정
  if (mil > lit) {
    lit = mil + 2000;
    lcd.setCursor(0, 1);
    if (analogRead(A1) > 700) {
      lcd.print("Brilliant");
    } else if (analogRead(A1) > 550) {
      lcd.print("Bright   ");
    } else {
      lcd.print("Darkness ");
    }
  }



  //부저울림 시작
  if (mil > buzt) {
    buzt = mil + 700;
    tone(buz, bar * 1.3 + 50, 40);
  }


  //RGB led
  if (digitalRead(7) == HIGH || analogRead(A2) < 480) {
    if (mil > ledt) {
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
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }
}

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

  delay(1000);

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
    tone(6, Mario_melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(6);
  }

}


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
    tone(6, pgm_read_word(&melody[thisNote]), noteDuration);

    /*
      to distinguish the notes, set a minimum time between them.
      the note's duration + 30% seems to work well:
    */
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(6); //stop the tone playing:
  }
  digitalWrite(6, LOW);
}
