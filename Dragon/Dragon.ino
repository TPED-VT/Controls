#include <Servo.h>

// Global Variables and Definitions
Servo dragonServo;         // Servo object for controlling the dragon jaw
int pos = 90;              // Current servo position (initially at HOME)
int lit = 0;               // Eye LED brightness level
int lava = 0;              // Lava LED strip brightness level
char send = 0;             // Variable for incoming serial command
boolean active = false;    // Indicates if the show is active
volatile bool stopProfile = false;  // Flag to indicate a stop command

#define RED_PIN 5         // PWM pin for the lava LED strip
#define EYES_PIN 11       // PWM pin for the eye LEDs
#define JAW_PIN 9         // Servo control pin for the jaw
#define HOME 90           // Home (closed jaw) position
#define OPEN (HOME + 70)  // Open jaw position

// Modified Macro: Checks if 's' is sent, and if so, cancels the show and returns.
#define CHECK_STOP() {                    \
  if (Serial.available() > 0) {           \
    char tmp = Serial.read();             \
    if (tmp == 's') {                     \
      cancelShow();                       \
      return;                             \
    }                                     \
  }                                       \
  if (stopProfile) return;                \
}

// Function Prototypes
void showProfile();
void jawOpen();
void jawClose();
void lavaLoop(int duration, int loops);
void cancelShow();

void setup() {
  Serial.begin(9600);
  active = false;
  stopProfile = false;
 
  // Setup LED pins
  pinMode(RED_PIN, OUTPUT);
  analogWrite(RED_PIN, 0);
  pinMode(EYES_PIN, OUTPUT);
  analogWrite(EYES_PIN, 0);
 
  // Setup servo
  dragonServo.attach(JAW_PIN);
  dragonServo.write(HOME);  // Start at HOME position
  pos = HOME;
}

void loop() {
  // Read and handle serial commands if available.
  while (Serial.available() > 0) {
    send = Serial.read();
    Serial.println(send);
    if (send == 's') {
      active = false;  // Stop the current show
    }
    // 'd' will start a single cycle if no show is running.
    if (send == 'd' && !active) {
      active = true;
      showProfile();
      active = false;
    }
    // '6' will trigger the 377-cycle mode if no show is running.
    if (send == '6' && !active) {
      active = true;
      for (int i = 0; i < 377 && active; i++) {
        Serial.print("Cycle: ");
        Serial.println(i + 1);
        showProfile();
        if(stopProfile) break;  // Ensure we exit early if stopProfile is set.
      }
      active = false;
    }
  }
}

// Cancel the show: returns servo to HOME and turns off the eye LEDs.
void cancelShow() {
  active = false;
  stopProfile = true;
  // Return the servo to HOME (closed jaw)
  dragonServo.write(HOME);
  pos = HOME;
  // Turn off the eye LEDs (leave lava LED unchanged)
  analogWrite(EYES_PIN, 0);
}

// showProfile: the main 90-second (approximate) animation sequence.
void showProfile() {
  stopProfile = false;  // Clear the stop flag at the beginning
  // Gradually fade in lava LED strip (0 -> 255)
  for (lava = 0; lava < 255 && !stopProfile; lava++) {
    analogWrite(RED_PIN, lava);
    delay(5);
  }
  CHECK_STOP();
  
  // 1.275 seconds
  lavaLoop(1400, 1);      // 1.5 seconds
  lavaLoop(2750, 2);      // 3.1 seconds
  
  
  // Permanent Time: 5.875 seconds
  // FOR-loop to gradually turn on dragon eyes to full brightness:
  for(lit = 0; lit < 255; lit++)
  {
    analogWrite(EYES_PIN, lit);             // Write new increased brightness to dragon eyes pin
    delay(5);                               // Wait 5ms before next loop iteration
  }
  
  // Permanent Time: 7.15 seconds
  jawOpen();                                 // FOR-loop to open the dragon jaw
      
  
  // 7.85 seconds
  lavaLoop(1550, 1);      // 1.65 seconds
      
  // Permanent Time: 9.5 seconds
  jawClose();                                // FOR-loop to close the dragon jaw
  
  // 10.2 seconds
  lavaLoop(2200, 2);      // 2.4 seconds
  
  // Permanent Time: 12.6 seconds
  jawOpen();                                 // FOR-loop to open the dragon jaw
  
  // 13.3 seconds
  lavaLoop(700, 2);       // 0.7 seconds
  lavaLoop(1380, 1);      // 1.5 seconds
      
  // Permanent Time: 15.5 seconds
  jawClose();                                // FOR-loop to close the dragon jaw
      
  // 16.2 seconds
  lavaLoop(3100, 2);      // 3.1 seconds
  lavaLoop(1000, 1);      // 1.5 seconds
  lavaLoop(2460, 2);      // 3.2 seconds
  
  
  jawOpen();                                 // FOR-loop to open the dragon jaw
  // Permanent Time: 23.997 seconds
  
  lavaLoop(2800, 2);      // 2.8 seconds
  lavaLoop(500, 1);        // 0.05 seconds
  
  // 27.55 seconds
  jawClose();                                // FOR-loop to close the dragon jaw
      
  // 28.25 seconds
  lavaLoop(2600, 2);      // 2.8 seconds
  lavaLoop(500, 1);       // 0.5 seconds
  lavaLoop(3100, 2);      // 3.1 seconds
  lavaLoop(500, 1);       // 0.5 seconds
  lavaLoop(2800, 2);      // 2.8 seconds
  lavaLoop(2500, 2);      // 3.1 seconds
  

      
  // 41.06 seconds
  jawOpen();                                 // FOR-loop to open the dragon jaw
      
  // 41.75 seconds
  lavaLoop(500, 1);       // 0.5 seconds
  lavaLoop(1500, 1);      // 1.5 seconds
  lavaLoop(400, 1);       // 0.6 seconds
      
  // 44.35 seconds
  jawClose();                                // FOR-loop to close the dragon jaw
      
  // 45.05 seconds
  lavaLoop(2220, 2);      // 2.8 seconds
  lavaLoop(3200, 2);      // 3.2 seconds
  lavaLoop(2800, 2);      // 2.8 seconds
  
  // 53.85 seconds
  jawOpen();                                 // FOR-loop to open the dragon j
      

  lavaLoop(1500, 1);      // 1.5 seconds
  lavaLoop(3100, 2);      // 3.1 seconds
  lavaLoop(750, 1);       // 0.7 seconds
  delay(25);              // 0.025 seconds
  lavaLoop(1490, 1);      // 1.5 seconds
  lavaLoop(2060, 2);      // 2.8 seconds

  // FOR-loop to gradually turn off dragon eyes:
  for(lit = 255; lit > 0; lit -= 1)
  {
    analogWrite(EYES_PIN, lit);             // Write new decreased brightness to dragon eyes pin
    delay(5);                               // Wait 5ms before next loop iteration
  }

  jawClose();                               // FOR-loop to close the dragon jaw
  
  // Permanent Time (Ride cycle ends): 66.2 seconds
  lavaLoop(3100, 2);      // 3.1 seconds
  lavaLoop(2800, 2);      // 2.8 seconds
  lavaLoop(1500, 1);      // 1.5 seconds
  delay(25);              // 0.025 seconds
  lavaLoop(3100, 2);      // 3.1 seconds
  lavaLoop(2800, 2);      // 2.8 seconds
  lavaLoop(3100, 2);      // 3.1 seconds
  lavaLoop(1500, 1);      // 1.5 seconds
  lavaLoop(3100, 2);      // 3.1 seconds
      
  // FOR-loop to gradually turn off lava:
  for(lava = 255; lava > 0; lava--)
  {
    analogWrite(RED_PIN, lava);             // Write new decreased brightness to dragon eyes pin
    delay(5);                               // Wait 5ms before next loop iteration
  }
  CHECK_STOP();
  // Total time: 90 seconds
}

// Gradually open the jaw from HOME to OPEN.
void jawOpen() {
  for (pos = HOME; pos <= OPEN && !stopProfile; pos++) {
    dragonServo.write(pos);
    delay(10);
  }
  CHECK_STOP();
}

// Gradually close the jaw from OPEN to HOME.
void jawClose() {
  for (pos = OPEN; pos >= HOME && !stopProfile; pos--) {
    dragonServo.write(pos);
    delay(10);
  }
  CHECK_STOP();
}

// Lava Sequence Function

void lavaLoop(int duration, int loops)
{
  int span = duration/(10*loops);
  for(int i = 0; i < loops; i++)
  {
    for(lava = 255; lava > (255 - span) && !stopProfile; lava--)
    {
      analogWrite(RED_PIN, lava);
      delay(5);
    }
    CHECK_STOP();
    for(lava = (255 - span); lava < 255 && !stopProfile; lava++)
    {
      analogWrite(RED_PIN, lava);
      delay(5);
    }
    CHECK_STOP();
  }
}
