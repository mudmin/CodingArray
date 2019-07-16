#include <Wire.h>
#include <LiquidCrystal_I2C.h>



byte cnum[8][8] = {
  B00000, B00100, B00100, B00100, B00100, B00100, B00000, B00000,
  B00000, B01110, B00010, B01110, B01000, B01110, B00000, B00000,
  B00000, B01110, B00010, B00110, B00010, B01110, B00000, B00000,
  B00000, B01010, B01010, B01110, B00010, B00010, B00000, B00000,
  B00000, B01110, B01000, B01110, B00010, B01110, B00000, B00000,
  B00000, B01110, B01000, B01110, B01010, B01110, B00000, B00000,
  B00000, B01110, B00010, B00010, B00010, B00010, B00000, B00000,
  B00000, B01110, B01010, B01110, B01010, B01110, B00000, B00000
};

byte cnum2[8][8] = {
  B11111, B11011, B11011, B11011, B11011, B11011, B11111, B00000,
  B11111, B10001, B11101, B10001, B10111, B10001, B11111, B00000,
  B11111, B10001, B11101, B11001, B11101, B10001, B11111, B00000,
  B11111, B10101, B10101, B10001, B11101, B11101, B11111, B00000,
  B11111, B10001, B10111, B10001, B11101, B10001, B11111, B00000,
  B11111, B10001, B10111, B10001, B10101, B10001, B11111, B00000,
  B11111, B10001, B11101, B11101, B11101, B11101, B11111, B00000,
  B11111, B10001, B10101, B10001, B10101, B10001, B11111, B00000
};

char board[16] = {0};
byte state[16] = {0};
int pos, prevPos, prevKey, count, life;
bool initall;
bool gamerun;
#define LIFE 8

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(7, INPUT);
  pinMode(8, INPUT);

  lcd.init();
  lcd.clear();
  lcd.backlight(); // lcd.noBacklight();

  for (int i = 0; i < 8; i++)
    lcd.createChar(i, cnum[i]);

  randomSeed(analogRead(A1));

  initall = true;
  gamerun = false;
  count = 8;
  life = LIFE;
  lcd.setCursor(0, 0);
  lcd.print("   flip flop");
  lcd.setCursor(0, 1);
  lcd.print("  Press button");
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);
  pos = map(val, 0, 1023, 0, 15);
  int key = digitalRead(8);

  if (pos != prevPos) {
    if (gamerun)
      drawSelected();
    prevPos = pos;
  }

  if (key && !prevKey) {
    tone(6, 392, 100);
    update();
  }
  prevKey = key;
}

void initBoard() {
  int dx, dy, count;
  for (int i = 0; i < 16; i++) {
    state[i] = 0;
    board[i] = 0;
  }
  for (int i = 1; i <= 8; i++) {
    count = 2;
    while (count--) {
      while (1) {
        dx = random(8);
        dy = random(2);
        if (board[dx + (8 * dy)] == 0) {
          board[dx + (8 * dy)] = i;
          break;
        }
      }
    }
  }
}

char testBoard() {
  char result = -1;
  for (int i = 0; i < 16; i++) {
    if (state[i] == 1) {
      result = i;
      break;
    }
  }
  return result;
}

void setFont(char c, bool invert) {
  lcd.createChar(c - 1, invert ? cnum2[c - 1] : cnum[c - 1]);
}

void drawBoard() {
  int i;
  char c;

  lcd.setCursor(1, 0);
  for (i = 0; i < 8; i++) {
    if (state[i] == 0) {
      c = 0xa5;
    } else {
      c = board[i] - 1;
    }
    lcd.write(c);
  }
  lcd.setCursor(1, 1);
  for (i = 8; i < 16; i++) {
    if (state[i] == 0) {
      c = 0xa5;
    } else {
      c = board[i] - 1;
    }
    lcd.write(c);
  }
}

void drawPanel()
{
  lcd.setCursor(10, 0);
  //  lcd.print(" [");
  //  lcd.print(life);
  //  lcd.print("] ");
  lcd.write(' ');
  lcd.write((char)0xef);
  lcd.write((char)0xeb);
  lcd.print(life);
  lcd.write(' ');
  lcd.setCursor(11, 1);
  lcd.print(count);
  lcd.print("/8");
}

void drawSelected()
{
  lcd.setCursor((pos % 8) + 1, pos / 8);
  lcd.cursor();
}

void drawClear()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Game Clear!");
  lcd.setCursor(0, 1);
  lcd.print("  Press button");
}

void drawOver()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   GAME OVER!");
  lcd.setCursor(0, 1);
  lcd.print(" Press button");
}

void drawInit()
{
  lcd.noCursor();
  lcd.clear();
  initBoard();
  for (int i = 0; i < 8; i++)
    lcd.createChar(i, cnum[i]);
  for (int i = 0; i < 16; i++)
    state[i] = 2;
  drawBoard();
  lcd.setCursor(10, 0);
  lcd.print("Ready");
  for (int i = 3; i > 0; i--) {
    lcd.setCursor(12, 1);
    lcd.print(i);
    delay(1000);
  }
  for (int i = 0; i < 16; i++)
    state[i] = 0;
  drawBoard();
  drawPanel();
  drawSelected();
}

void update()
{
  if (initall) {
    initall = false;
    gamerun = true;
    count = 8;
    life = LIFE;
    drawInit();
    return;
  }

  if (state[pos] != 0)
    return;

  lcd.noCursor();
  char item = testBoard();

  if (item == -1) {
    state[pos] = 1;
    setFont(board[pos], true);
    drawBoard();
    drawSelected();

  } else if (board[pos] == board[item]) {
    state[pos] = 2;
    state[item] = 2;
    setFont(board[pos], true);
    setFont(board[item], true);
    count--;
    drawBoard();
    drawPanel();
    delay(1000);
    if (count == 0) {
      drawClear();
      initall = true;
      gamerun = false;
    } else {
      setFont(board[pos], false);
      setFont(board[item], false);
      drawBoard();
      drawSelected();
    }

  } else {
    state[pos] = 1;
    state[item] = 1;
    setFont(board[pos], true);
    setFont(board[item], true);
    life--;
    drawBoard();
    drawPanel();
    state[pos] = 0;
    state[item] = 0;
    tone(6, 392, 50);
    delay(200);
    tone(6, 262, 700);
    delay(750);
    if (life == 0) {
      drawOver();
      initall = true;
      gamerun = false;
    } else {
      setFont(board[pos], false);
      setFont(board[item], false);
      drawBoard();
      drawSelected();
    }
  }
}
