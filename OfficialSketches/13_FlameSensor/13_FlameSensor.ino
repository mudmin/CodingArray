
/* Coding Array STARTER Kit for Arduino
* 
*  CAK Starter code 13_FlameSensor
* 
*  This sketch uses the flame sensor module connected to analogue A5. 
*  Detects flame strength around (prepare lighter and bring flame near module) 
*  If the threshold value set is exceeded, an audible alarm will be 
*  
*/

#define PI 3.141592       // Set circumference PI value 

int flameSensor =A5;                 // Connect flame detection sensor to analogue pin A5 
int Buzzer =6;                       // connect the piezo buzzer to pin 6.
int sensorReading =0;               // Variables for storing sensor output values
int threshold = 1000;

void setup() {
  pinMode(Buzzer, OUTPUT);           // Output settings for piezo buzzer pins 
  pinMode(flameSensor, INPUT);       // set flame sensor pin to input 
  Serial.begin(9600);               // initiate serial communication at 9600 speed
}


void loop() {
  sensorReading = analogRead(flameSensor);  //save an analogue value of the flame detection sensor

  Serial.println(sensorReading);        //Print the value of the flame detection sensor to the serial window

  if(sensorReading >=threshold) {            // flame detection sensor value greater than 1000
 
    Serial.println("Fire !!");           // Fire! Outputs on screen 
    playTone();                          // Alarm negative

  } else {                            // If flame detection sensor value is less
    noTone(Buzzer);                      //off Peugeot Booger 
  }

  delay(500);                       //  0.5 second interval 
}


// set alarm negative function

void playTone() {
  float sinVal;           // save the sine wave value 
  int toneVal;            // store value for alarm sound generation
 
  for(int i =0 ; i < 180; i++) {
    sinVal =sin(i * PI/180);                 //calculate the sin value by changing the angle to the radian value
    toneVal = 2000+(int(sinVal * 1000));      //translate alarm to frequency 
    tone(Buzzer,toneVal);                   //frequency generated from Peugeot speakers
    delay(10);                              //alarm sound frequency rate adjustment 
  }
}
