/*  ArduinoStory CodingArrayKit_STARTER
 *
 *  CAK Starter Code 02_Serial
 *  This sketch shows how to print messages entered on a computer into a serial window.
 */

void setup() {
  Serial.begin(9600);            //Prepare serial communication. Set the communication speed to 9600.

}

void loop() {
  Serial.println("Hello Coding Array Kit ~!");   //Print Hello Coding Array Kit~! in the serial window.
  delay(1000);                               //Wait for 1000 milliseconds (=1 second).
}
