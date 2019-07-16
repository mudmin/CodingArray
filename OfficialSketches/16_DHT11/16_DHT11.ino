
/*  ArduinoStory CodingArrayKit_STARTER
* 
*   CAK Starter code 16_DHT11
* 
*   This sketch uses the temperature sensor DHT11 module connected to digital pin 12. 
*   Measure the ambient temperature and humidity
*   Outputs result values to I2C LCD. 
*/

// Library for DHT11 Module Use 
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
 
// library for I2C LCD use 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// set the temperature sensor 
#define DHTPIN            12         // DHT sensor to pin 12. 
#define DHTTYPE            DHT11     // DHT 11.

DHT_Unified dht(DHTPIN,DHTTYPE);      // form a dht object. 

uint32_t delayMS;

//LCD settings 
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD I2C address. 16kans2joules LCD use
                            

void setup() {
  Serial.begin(9600);      // initiate serial communication at 9600 speed 

  // Initialize LCD 
  lcd.init();
  lcd.backlight();                // turn on the backlight (lcd.noBacklight() turns off the backlight).
  lcd.setCursor(0,0);                 // First line first column 
  lcd.print("Hello~~~");
  lcd.setCursor(0,1);                // the first column of the second line 
  lcd.print("DHT Sensor Start");
  delay(1000);
    lcd.clear(); 
 // start DHT sensor
  dht.begin();             
  Serial.println("DHT11 Unified Sensor Example");

  // print temperature sensor information
  sensor_t sensor;
  
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print ("Sensor:    "); Serial.println(sensor.name);
  Serial.print ("Driver Ver: "); Serial.println(sensor.version);
  Serial.print ("Unique ID: "); Serial.println(sensor.sensor_id);
  Serial.print ("Max Value: "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print ("Min Value: "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print ("Resolution:"); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");

  // Print the Humidity Sensor Information 
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print ("Sensor:     "); Serial.println(sensor.name);
  Serial.print ("Driver Ver: "); Serial.println(sensor.version);
  Serial.print ("Unique ID:  "); Serial.println(sensor.sensor_id);
  Serial.print ("Max Value:  "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print ("Min Value:  "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print ("Resolution: "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");

  // Time to read the sensor 
  delayMS =sensor.min_delay /1000;
}


void loop() {
  // Delay between measurements.
  delay(delayMS);
  
  sensors_event_t event;  
  dht.temperature().getEvent(&event);  // Get temperature event and print its value. 
  
  if(isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
    
  }
  
  else{
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
    
    lcd.setCursor(0,0);                           // First line first column 
    lcd.print("Temp    : " );                     // output message 
    lcd.print(event.temperature,0);               // Output without decimal point of measurement temperature
    lcd.print(" [C]");                            // Output in units 
  }
  
  dht.humidity().getEvent(&event);                // Get humidity event and print its value.
  if(isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
    
  }
  else{
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");
   
    lcd.setCursor(0,1);                           // the first column of the second line
    lcd.print("Humidity: " );                     // output message 
    lcd.print(event.relative_humidity,0);         // output measurement humidity 
    lcd.print(" [%]");                            // Output in units 
 
  }
  
  // indicate temperature and humidity results on LCD 
    
   
 
 delay(1000);                      // delay of 1000 milliseconds to reliably read values
}
