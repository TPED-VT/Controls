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
void lavaLoop1();
void lavaLoop2();
void lavaLoop3();
void lavaLoop4();
void lavaLoop5();
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
    CHECK_STOP();
  }
  if (stopProfile) return;
 
  lavaLoop1();
  if (stopProfile) return;
  lavaLoop2();
  if (stopProfile) return;
 
  // Gradually fade in dragon eyes
  for (lit = 0; lit < 255 && !stopProfile; lit++) {
    analogWrite(EYES_PIN, lit);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
 
  // Jaw movements and further lava sequences:
  jawOpen();
  if (stopProfile) return;
 
  lavaLoop1();
  delay(50);
  lavaLoop4();
  if (stopProfile) return;
 
  jawClose();
  if (stopProfile) return;
 
  lavaLoop3();
  if (stopProfile) return;
 
  jawOpen();
  if (stopProfile) return;
 
  lavaLoop4();
  delay(100);
  lavaLoop2();
  lavaLoop4();
  if (stopProfile) return;
 
  jawClose();
  if (stopProfile) return;
 
  lavaLoop1();
  lavaLoop2();
  lavaLoop1();
  lavaLoop4();
  if (stopProfile) return;
 
  jawOpen();
  if (stopProfile) return;
 
  lavaLoop3();
  lavaLoop5();
  if (stopProfile) return;
 
  jawClose();
  if (stopProfile) return;
 
  lavaLoop3();
  lavaLoop1();
  lavaLoop2();
  lavaLoop1();
  lavaLoop3();
  lavaLoop1();
  if (stopProfile) return;
 
  jawOpen();
  if (stopProfile) return;
 
  lavaLoop1();
  lavaLoop1();
  if (stopProfile) return;
 
  jawClose();
  if (stopProfile) return;
 
  lavaLoop4();
  lavaLoop2();
  delay(50);
  lavaLoop3();
  lavaLoop4();
  if (stopProfile) return;
 
  jawOpen();
  if (stopProfile) return;
 
  lavaLoop1();
  lavaLoop2();
  lavaLoop4();
  delay(75);
  lavaLoop1();
  lavaLoop2();
  lavaLoop3();
  if (stopProfile) return;
 
  // Fade out dragon eyes (turn off eyes gradually)
  for (lit = 255; lit > 0 && !stopProfile; lit--) {
    analogWrite(EYES_PIN, lit);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
 
  // Ensure jaw is closed
  jawClose();
  if (stopProfile) return;
 
  lavaLoop2();
  lavaLoop3();
  lavaLoop1();
  delay(225);
  lavaLoop2();
  lavaLoop3();
  lavaLoop2();
  lavaLoop3();
  lavaLoop2();
  if (stopProfile) return;
 
  // Dragon jaw "sleep" state: 18-second hold with closed jaw and eye LEDs off.
  unsigned long sleepStart = millis();
  dragonServo.write(HOME);
  pos = HOME;
  while (millis() - sleepStart < 18000 && !stopProfile) {
    CHECK_STOP();
    delay(100);
  }
}

// Gradually open the jaw from HOME to OPEN.
void jawOpen() {
  for (pos = HOME; pos <= OPEN && !stopProfile; pos++) {
    dragonServo.write(pos);
    delay(10);
    CHECK_STOP();
  }
}

// Gradually close the jaw from OPEN to HOME.
void jawClose() {
  for (pos = OPEN; pos >= HOME && !stopProfile; pos--) {
    dragonServo.write(pos);
    delay(10);
    CHECK_STOP();
  }
}

// Lava Sequence Functions

// lavaLoop1: Approximately 1.5 seconds loop.
void lavaLoop1() {
  for (lava = 255; lava > 105 && !stopProfile; lava--) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
  for (lava = 105; lava < 255 && !stopProfile; lava++) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
}

// lavaLoop2: Approximately 3.1 seconds loop.
void lavaLoop2() {
  for (lava = 255; lava > 145 && !stopProfile; lava--) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
  for (lava = 145; lava < 255 && !stopProfile; lava++) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
  for (lava = 255; lava > 55 && !stopProfile; lava--) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
  for (lava = 55; lava < 255 && !stopProfile; lava++) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
}

// lavaLoop3: Approximately 2.8 seconds loop.
void lavaLoop3() {
  for (lava = 255; lava > 105 && !stopProfile; lava--) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
  for (lava = 105; lava < 255 && !stopProfile; lava++) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
  for (lava = 255; lava > 125 && !stopProfile; lava--) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
  for (lava = 125; lava > 105 && !stopProfile; lava--) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
}

// lavaLoop4: Approximately 0.5 seconds loop.
void lavaLoop4() {
  for (lava = 255; lava > 205 && !stopProfile; lava--) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
  for (lava = 205; lava < 255 && !stopProfile; lava++) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
}

// lavaLoop5: Approximately 0.45 seconds loop.
void lavaLoop5() {
  for (lava = 255; lava > 210 && !stopProfile; lava--) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
  if (stopProfile) return;
  for (lava = 210; lava < 255 && !stopProfile; lava++) {
    analogWrite(RED_PIN, lava);
    delay(5);
    CHECK_STOP();
  }
}
