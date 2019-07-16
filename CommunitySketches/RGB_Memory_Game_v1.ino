//RGB Memory Game - Version 1
//This was quick and dirty. Don't judge me.
//This should be modded to take advantage of the built in LCD
//Maybe a slider could adjust the speed?


// LED pin definitions
#define LED_RED   9
#define LED_GREEN 10
#define LED_BLUE  11

#define LED_CORRECT 48
#define LED_WRONG   49

// Button pin definitions
//We're connecting 3 additional buttons to the IO Expansion Shield
//On each button, one wire goes to the IO Pin and the other to ground.
//Be sure to turn off the bottom 3 DIP switches on the digitial side
//of the Arduino (3,4,5) so these buttons don't conflict with the built in sensors
#define BUTTON_BLUE   3
#define BUTTON_GREEN  4
#define BUTTON_RED    5


// Buzzer definitions
//use the existing buzzer, which is already on pin 6
#define BUZZER  6
#define RED_TONE 220
#define GREEN_TONE 262
#define BLUE_TONE 330
#define TONE_DURATION 250

// Game Variables
int start = 8;  //use the built in clicky button as a start/reset button
int go = 0;
int GAME_SPEED = 350; //The bigger this number, the slower the game goes
int GAME_STATUS = 0;
int const GAME_MAX_SEQUENCE = 10;
int GAME_SEQUENCE[GAME_MAX_SEQUENCE];
int GAME_STEP = 0;
int READ_STEP = 0;

void setup(){
  Serial.begin(9600); //You can use the serial monitor to debug your changes to the code.

  randomSeed(analogRead(0));

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_CORRECT, OUTPUT);
  pinMode(LED_WRONG, OUTPUT);
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(start, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
}

void loop(){

  if(go == 0){
    int check = digitalRead(start);
    if(check == HIGH){
      go = 1;
      Serial.println("Start button pushed!");
      resetGame();
    }
  }

  if(go == 1){
  switch(GAME_STATUS){
    case 0:
      resetGame();
      break;
    case 1:
      playSequence();
      break;
    case 2:
      readSequence();
      break;
    case 3:
      gameOver();
      go = 0;
      break;
  }
}
}

void playSequence(){
  // play a step of our sequence
  for(int i=0; i<=GAME_STEP; i++){
    Serial.print("Set LED");
    Serial.println(GAME_SEQUENCE[i]);
    delay(GAME_SPEED*2);
    setLED(GAME_SEQUENCE[i]);
    playTone(GAME_SEQUENCE[i]);
    delay(GAME_SPEED);
    clearLEDs();

  }
  // Go to next step: reading buttons
  GAME_STATUS = 2;
}

void readSequence(){
  // read our buttons
  int button_value = readButtons();

  if(button_value > 0){
    // a button has been pressed
    if(button_value == GAME_SEQUENCE[READ_STEP]){
      // correct value!
      setLED(button_value);
      playTone(button_value);
      digitalWrite(LED_CORRECT, HIGH);
      delay(GAME_SPEED);
      clearLEDs();
      digitalWrite(LED_CORRECT, LOW);

      // Lets speed it up!
      GAME_SPEED = GAME_SPEED-15;

      Serial.println("Correct!");

      if(READ_STEP == GAME_STEP){
        // reset read step
        READ_STEP = 0;
        // Go to next game step
        GAME_STEP++;
        // Go to playback sequence mode of our game
        GAME_STATUS = 1;
        Serial.println("Go To Next Step");
        Serial.println(GAME_STEP);

        // Light all LEDs to indicate next sequence
        setLEDs(true,true,true);
        delay(GAME_SPEED);
        setLEDs(false,false,false);


      }else{
        READ_STEP++;
      }

      delay(10);

    }else{
      // wrong value!
      // Go to game over mode
      GAME_STATUS = 3;
      Serial.println("Game Over!");
    }
  }

  delay(10);
}

void resetGame(){
  // reset steps
  READ_STEP = 0;
  GAME_STEP = 0;

  // create random sequence
  for(int i=0; i<GAME_MAX_SEQUENCE; i++){
    GAME_SEQUENCE[i] = random(3) + 1;
  }

  // Go to next game state; show led sequence
  GAME_STATUS = 1;
}

void gameOver(){
  // Red RGB
  digitalWrite(LED_WRONG, HIGH);
  // Play Pwa Pwa Pwa
    tone(BUZZER, 98, TONE_DURATION);
    delay(TONE_DURATION);
    tone(BUZZER, 93, TONE_DURATION);
    delay(TONE_DURATION);
    tone(BUZZER, 87, TONE_DURATION);
    delay(TONE_DURATION);
    tone(BUZZER, 98, TONE_DURATION);
    delay(TONE_DURATION);
    tone(BUZZER, 93, TONE_DURATION);
    delay(TONE_DURATION);
    tone(BUZZER, 87, TONE_DURATION);
    delay(TONE_DURATION);  tone(BUZZER, 98, TONE_DURATION);
    delay(TONE_DURATION);
    tone(BUZZER, 93, TONE_DURATION);
    delay(TONE_DURATION);
    tone(BUZZER, 87, TONE_DURATION);
    delay(TONE_DURATION);  tone(BUZZER, 98, TONE_DURATION);
    delay(TONE_DURATION);
    tone(BUZZER, 93, TONE_DURATION);
    delay(TONE_DURATION);
    tone(BUZZER, 87, TONE_DURATION);
    delay(TONE_DURATION);
}

// HELPER FUNCTIONS
void setLED(int id){
  switch(id){
    case 0:
      setLEDs(false,false,false);
      break;
    case 1:
      setLEDs(true,false,false);
      break;
    case 2:
      setLEDs(false,true,false);
      break;
    case 3:
      setLEDs(false,false,true);
      break;
  }
}

void playTone(int id){
  switch(id){
    case 0:
      noTone(BUZZER);
      break;
    case 1:
      tone(BUZZER, RED_TONE, TONE_DURATION);
      break;
    case 2:
      tone(BUZZER, GREEN_TONE, TONE_DURATION);
      break;
    case 3:
      tone(BUZZER, BLUE_TONE, TONE_DURATION);
      break;
  }
}

void setLEDs(boolean red, boolean green, boolean blue){
  if (red) digitalWrite(LED_RED, HIGH);
  else digitalWrite(LED_RED, LOW);
  if (green) digitalWrite(LED_GREEN, HIGH);
  else digitalWrite(LED_GREEN, LOW);
  if (blue) digitalWrite(LED_BLUE, HIGH);
  else digitalWrite(LED_BLUE, LOW);
}

void clearLEDs(){
  setLEDs(false,false,false);
}

int readButtons(void){
  if (digitalRead(BUTTON_RED) == 0){Serial.println("1"); return 1;}
  else if (digitalRead(BUTTON_GREEN) == 0) {Serial.println("2"); return 2;}
  else if (digitalRead(BUTTON_BLUE) == 0) {Serial.println("3"); return 3; }

  return 0;
}
