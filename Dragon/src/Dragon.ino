#include <Servo.h>
#include <adruino.h>
 
Servo dragonServo;
int pos = 0;
 
void setup() {
  // Servo setup code
  dragonServo.attach(9);  	// digital pin 9
}
 
void loop() {
  // FOR-loop to open the dragon jaw:
  for(pos = 0; pos <= -30; pos -= 1)
  {
    dragonServo.write(pos);   // Change the position of the servo arm to new position
    delay(5);             	// 5ms delay before next adjustment
  }
  delay(4000);            	// delay for dragon roar/effects
 
  // FOR-loop to close the dragon jaw:
  for(pos = -30; pos >= 0; pos += 1)
  {
    dragonServo.write(pos);   // Change the position of the servo arm to new position
    delay(5);             	// 5ms delay before next adjustment
  }
}
