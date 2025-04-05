#include <Servo.h>

Servo dragonServo;                           // Initialize dragon servo object
int pos = 0;                                 // Initialize servo position
int lit = 0;                                 // Initialize eye LEDs brightness
int lava = 0;                                // Initialize lava LED strip brightness
#define RED_PIN 5                            // Define the arduino PWM pin for the lava LED strip
#define EYES_PIN 11                          // Define the arduino PWM pin for the eye LEDs
#define JAW_PIN 9                            // Define the arduino pin for the servo

// Hardware setup
void setup() {
  // LED strip RGB setup code
  pinMode(RED_PIN, OUTPUT);                  // digital PWM pin 5

  // Eye LEDs setup code
  pinMode(EYES_PIN, OUTPUT);                 // digital PWM pin 11
  
  // Servo setup code
  dragonServo.attach(JAW_PIN);               // digital pin 9
  dragonServo.write(pos);                    // Initialize starting position of dragon
}

// Main loop to repeat continuously
void loop() {
  
  // FOR-loop to gradually turn lava LED strip on to full brightness
  for(lava = 0; lava < 255; lava += 1)
  {
    analogWrite(RED_PIN, lava);             // Write new increased brightness to red pin of RGB LED strip (lava)
    delay(5);                               // Wait 5ms before next loop iteration
  }
  
  // 1.275 seconds
    lavaLoop1();
    lavaLoop2();
    
  // Permanent Time: 5.875 seconds
  // FOR-loop to gradually turn on dragon eyes to full brightness:
  for(lit = 0; lit < 255; lit += 1)
  {
    analogWrite(EYES_PIN, lit);             // Write new increased brightness to dragon eyes pin
    delay(5);                               // Wait 5ms before next loop iteration
  }
  
  // Permanent Time: 7.15 seconds
  jawOpen();                                 // FOR-loop to open the dragon jaw
  
  // 7.45 seconds
  lavaLoop1();  // 1.5 seconds
  delay(50);    // 0.05 seconds
  lavaLoop4();  // 0.5 seconds
  
  // Permanent Time: 9.5 seconds
  jawClose();                                // FOR-loop to close the dragon jaw
  
  // 9.8 seconds
  lavaLoop3();  // 2.8 seconds
  
  // Permanent Time: 12.6 seconds
  jawOpen();                                 // FOR-loop to open the dragon jaw
  
  // 12.9 seconds
  lavaLoop4();  // 0.5 seconds
  delay(100);   // 0.1 seconds
  lavaLoop2();  // 1.5 seconds
  lavaLoop4();  // 0.5 seconds
  
  // Permanent Time: 15.5 seconds
  jawClose();                                // FOR-loop to close the dragon jaw
  
  // 15.8 seconds
  lavaLoop1();  // 3.1 seconds
  lavaLoop2();  // 1.5 seconds
  lavaLoop1();  // 3.1 seconds
  lavaLoop4();  // 0.5 seconds
  
  // 24 seconds
  jawOpen();                                 // FOR-loop to open the dragon jaw
  
  // 24.3 seconds
  lavaLoop3(); // 2.8 seconds
  lavaLoop5(); // 0.45 seconds
  
  // 27.55 seconds
  jawClose();                                // FOR-loop to close the dragon jaw
  
  // 27.85 seconds
  lavaLoop3();
  lavaLoop1();
  lavaLoop2();
  lavaLoop1();
  lavaLoop3();
  lavaLoop1();
  
  // 41.05 seconds
  jawOpen();                                 // FOR-loop to open the dragon jaw
  
  // 41.35 seconds
  lavaLoop1();  // 1.5 seconds
  lavaLoop1();  // 1.5 seconds
  
  // 44.35 seconds
  jawClose();                                // FOR-loop to close the dragon jaw
  
  // 44.65 seconds
  lavaLoop4();
  lavaLoop2();
  delay(50);
  lavaLoop3();
  lavaLoop4();
  
  // 53.85 seconds
  jawOpen();                                 // FOR-loop to open the dragon jaw
  
  // 54.15 seconds
  lavaLoop1();    // 1.5 seconds
  lavaLoop2();    // 3.1 seconds
  lavaLoop4();    // 0.5 seconds
  lavaLoop1();    // 1.5 seconds
  lavaLoop2();    // 3.1 seconds
  lavaLoop3();    // 2.8 seconds
  lavaLoop1();    // 1.5 seconds
  
  // Permanent Time: 66.2 seconds
  // FOR-loop to gradually turn off dragon eyes:
  for(lit = 255; lit > 0; lit -= 1)
  {
    analogWrite(EYES_PIN, lit);             // Write new decreased brightness to dragon eyes pin
    delay(5);                               // Wait 5ms before next loop iteration
  }
  
  // 66.5 seconds
  jawClose();                               // FOR-loop to close the dragon jaw
  
  // Total time: 67.775 seconds
}


// Dragon jaw opening function
void jawOpen()
{
  // FOR-loop to open the dragon jaw:
  for(pos = 0; pos <= 30; pos += 1)
  {
    dragonServo.write(pos);                 // Change the position of the servo arm to new position
    delay(10);                              // 10ms delay before next adjustment
  }
}

void jawClose()
{
  // FOR-loop to close the dragon jaw:
  for(pos = 30; pos >= 0; pos -= 1)
  {
    dragonServo.write(pos);                 // Change the position of the servo arm to new position
    delay(10);                              // 10ms delay before next adjustment
  }
}

// Function for lava sequence 1 to sequence LED strip
// Loop takes 1.5 seconds
void lavaLoop1()
{
  for(lava = 255; lava > 105; lava -= 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
  for(lava = 105; lava < 255; lava += 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
}

// Function for lava sequence 2 to sequence LED strip
// Loop takes 3.1 seconds
void lavaLoop2()
{
  for(lava = 255; lava > 145; lava -= 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
  for(lava = 145; lava < 255; lava += 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
  for(lava = 255; lava > 55; lava -= 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
  for(lava = 55; lava < 255; lava += 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
}

// Function for lava sequence 3 to sequence LED strip
// Loop takes 2.8 seconds
void lavaLoop3()
{
  for(lava = 255; lava > 105; lava -= 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
  for(lava = 105; lava < 255; lava += 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
  for(lava = 255; lava > 125; lava -= 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
  for(lava = 125; lava > 255; lava += 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
}

// 0.5 seconds
void lavaLoop4()
{
  for(lava = 255; lava > 205; lava -= 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
  for(lava = 205; lava < 255; lava += 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
}

// 0.45 seconds
void lavaLoop5()
{
  for(lava = 255; lava > 210; lava -= 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
  for(lava = 210; lava < 255; lava += 1)
  {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
}
