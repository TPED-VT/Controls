const int ARM_STEP_PIN = 3, ARM_DIR_PIN = 8, ARM_ENA_PIN = 9;
const int GONDOLA_STEP_PIN = 5, GONDOLA_DIR_PIN = 10, GONDOLA_ENA_PIN = 11;

volatile int armStepFreq = 0, gondolaStepFreq = 0;
volatile int currentArmStepFreq = 0, currentGondolaStepFreq = 0;
volatile int targetArmStepFreq = 0, targetGondolaStepFreq = 0;

volatile unsigned long lastArmStep = 0, lastGondolaStep = 0;
volatile unsigned long armStepInterval = 0, gondolaStepInterval = 0;

bool armStepState = LOW, gondolaStepState = LOW;
bool started = false;
bool sequenceStarted = false;
int armDir = 0, gondolaDir = 0;

int oldArmDirVal = 0, oldGondolaDirVal = 0;
int newArmDirVal = 0, newGondolaDirVal = 0;
int finalArmStepFreqVal = -1, finalGondolaStepFreqVal = -1;

// For serial parsing
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
boolean newData = false;

struct Command {
  int armF;
  int armD;
  int gondF;
  int gondD;
  unsigned long duration;  // ms
};

Command commands[] = {
  { 80, 1, 35, 0, 2500 },
  { 80, 1, 90, 1, 2500 },
  { 0, 0, 0, 0, 3000 },
  { 400, 0, 20, 0, 1500 },
  { 0, 0, 3000, 0, 1700 },
  { 1000, 1, 0, 0, 1500 },
  { 100, 1, 0, 0, 2000 },
  { 1000, 1, 0, 0, 800 },
  { 80, 1, 50, 1, 2000 },
  { 80, 0, 80, 0, 2300 },
  { 90, 0, 90, 1, 1800 },
  { 120, 0, 0, 1, 3000 },
  { 0, 0, 600, 1, 1000 },
  { 200, 1, 840, 1, 1250 },
  { 90, 1, 40, 1, 5000 },
  { 40, 0, 80, 0, 2300 },
  { 40, 0, 100, 1, 2300 },
  { 40, 0, 100, 0, 2300 },
  { 40, 0, 80, 1, 2300 },
  { 40, 0, 80, 1, 1500 },
  { 40, 0, 80, 1, 1500 },
  { 850, 0, 1100, 1, 8000 },
  { 100, 0, 80, 0, 7000 },
  { 100, 0, 0, 0, 2500 },
  { 0, 0, 0, 0, 5000 },
  { 50, 0, 0, 0, 2730 },
  { 0, 0, 50, 0, 2390 },
  {0,0,0,0,18000}
};

const int totalCommands = sizeof(commands) / sizeof(commands[0]);
int currentCommandIndex = 0;
unsigned long commandStartTime = 0;

// --- New global variables for repeated sequence ---
bool multiSequence = false;         // Flag to indicate '6' was entered
int sequenceIteration = 0;            // Counts how many full sequences have been run
const int totalIterations = 377;      // Total cycles to run when '6' is entered

void setup() {
  Serial.begin(9600);

  pinMode(ARM_STEP_PIN, OUTPUT);
  pinMode(ARM_DIR_PIN, OUTPUT);
  pinMode(ARM_ENA_PIN, OUTPUT);
  pinMode(GONDOLA_STEP_PIN, OUTPUT);
  pinMode(GONDOLA_DIR_PIN, OUTPUT);
  pinMode(GONDOLA_ENA_PIN, OUTPUT);

  digitalWrite(ARM_ENA_PIN, LOW);
  digitalWrite(GONDOLA_ENA_PIN, LOW);
  digitalWrite(ARM_STEP_PIN, LOW);
  digitalWrite(GONDOLA_STEP_PIN, LOW);

  // Initialize old directions
  oldArmDirVal = armDir;
  oldGondolaDirVal = gondolaDir;
  for (int i = 0; i < 40; i++){
    Serial.println("e");
    delayMicroseconds(5);
  }
}

// ===================== LOOP =====================
void loop() {
  // -------- Immediate check for the 'p' command --------
  if (Serial.available() > 0) {
    // Peek at the next character without removing it
    char c = Serial.peek();
    if (c == 'p') {
      // Remove the 'p' and flush any additional characters
      while (Serial.available() > 0) {
        Serial.read();
      }
      // Cancel the sequence and ramp down
      sequenceStarted = false;
      started = true;  // Ensure the ramping code still runs
      armStepFreq = 0;
      gondolaStepFreq = 0;
      targetArmStepFreq = 0;
      targetGondolaStepFreq = 0;
      Serial.println("p");
    }
  }
  
  // -------- Preloaded sequence start check --------
  if (!sequenceStarted && Serial.available() > 0) {
    char c = Serial.peek();
    // Use 'd' for a single run or '6' for 377 repeats.
    if (c == 'd') {
      Serial.read();
      sequenceStarted = true;
      started = true;
      currentCommandIndex = 0;
      loadCommand(commands[0]);
      commandStartTime = millis();
    }
    else if (c == '6') {
      Serial.read();
      multiSequence = true;         // Set flag for repeated sequence
      sequenceIteration = 0;          // Reset the iteration counter
      sequenceStarted = true;
      started = true;
      currentCommandIndex = 0;
      loadCommand(commands[0]);
      commandStartTime = millis();
    }
  }

  unsigned long now = micros();
  static unsigned long lastRampUpdate = 0;
  if (now - lastRampUpdate >= 10000) {
    lastRampUpdate = now;

    if (currentArmStepFreq < targetArmStepFreq) {
      currentArmStepFreq += 2;
    } else if (currentArmStepFreq > targetArmStepFreq) {
      currentArmStepFreq -= 2;
    }
    if (currentArmStepFreq > 0) {
      armStepInterval = max(500000L / currentArmStepFreq, 10UL);
    } else {
      armStepInterval = 0;
    }

    if (currentGondolaStepFreq < targetGondolaStepFreq) {
      currentGondolaStepFreq += 3;
    } else if (currentGondolaStepFreq > targetGondolaStepFreq) {
      currentGondolaStepFreq -= 3;
    }
    if (currentGondolaStepFreq > 0) {
      gondolaStepInterval = max(500000L / currentGondolaStepFreq, 10UL);
    } else {
      gondolaStepInterval = 0;
    }
  }

  if (currentArmStepFreq > 0 && started && (now - lastArmStep >= armStepInterval)) {
    lastArmStep = now;
    armStepState = !armStepState;
    digitalWrite(ARM_STEP_PIN, armStepState);
  }

  if (currentGondolaStepFreq > 0 && started && (now - lastGondolaStep >= gondolaStepInterval)) {
    lastGondolaStep = now;
    gondolaStepState = !gondolaStepState;
    digitalWrite(GONDOLA_STEP_PIN, gondolaStepState);
  }

  if (currentArmStepFreq == 0 && targetArmStepFreq == 0 && finalArmStepFreqVal != -1) {
    digitalWrite(ARM_DIR_PIN, newArmDirVal);
    oldArmDirVal = newArmDirVal;
    targetArmStepFreq = finalArmStepFreqVal;
    finalArmStepFreqVal = -1;
  }
  if (currentGondolaStepFreq == 0 && targetGondolaStepFreq == 0 && finalGondolaStepFreqVal != -1) {
    digitalWrite(GONDOLA_DIR_PIN, newGondolaDirVal);
    oldGondolaDirVal = newGondolaDirVal;
    targetGondolaStepFreq = finalGondolaStepFreqVal;
    finalGondolaStepFreqVal = -1;
  }

  // -------- Process serial commands (with markers) --------
  recvWithStartEndMarkers();
  if (newData) {
    // Only process non-'p' commands here; if 'p' were sent, it would have been caught above.
    strcpy(tempChars, receivedChars);
    parseData();
    updateFreq();
    newData = false;
  }

  // -------- Process preloaded command sequence if running --------
  if (sequenceStarted) {
    if ((millis() - commandStartTime) >= commands[currentCommandIndex].duration) {
      currentCommandIndex++;
      if (currentCommandIndex >= totalCommands) {
        // If running in multi-sequence mode, repeat the entire sequence 377 times.
        if (multiSequence) {
          sequenceIteration++;
          if (sequenceIteration < totalIterations) {
            currentCommandIndex = 0;
            loadCommand(commands[currentCommandIndex]);
            commandStartTime = millis();
          } else {
            // Finished 377 iterations; reset flags and ramp down.
            sequenceStarted = false;
            multiSequence = false;
            started = false;
            armStepFreq = 0;
            gondolaStepFreq = 0;
            targetArmStepFreq = 0;
            targetGondolaStepFreq = 0;
            for (int i = 0; i < 40; i++){
              Serial.println("e");
              delayMicroseconds(5);
            }
          }
        } else {
          // Single run mode (triggered by 'd')
          sequenceStarted = false;
          started = false;
          armStepFreq = 0;
          gondolaStepFreq = 0;
          targetArmStepFreq = 0;
          targetGondolaStepFreq = 0;
          for (int i = 0; i < 40; i++){
            Serial.println("e");
            delayMicroseconds(5);
          }
        }
      } else {
        loadCommand(commands[currentCommandIndex]);
        commandStartTime = millis();
      }
    }
  }
}

void loadCommand(const Command& cmd) {
  armStepFreq = cmd.armF;
  armDir = cmd.armD;
  gondolaStepFreq = cmd.gondF;
  gondolaDir = cmd.gondD;

  newArmDirVal = armDir;
  newGondolaDirVal = gondolaDir;

  if (armDir != oldArmDirVal) {
    finalArmStepFreqVal = armStepFreq;
    targetArmStepFreq = 0;
  } else {
    targetArmStepFreq = armStepFreq;
  }

  if (gondolaDir != oldGondolaDirVal) {
    finalGondolaStepFreqVal = gondolaStepFreq;
    targetGondolaStepFreq = 0;
  } else {
    targetGondolaStepFreq = gondolaStepFreq;
  }

  updateFreq();
}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      } else {
        receivedChars[ndx] = '\0';  // end of string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    } else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void parseData() {
  char* strtokIndx;

  strtokIndx = strtok(tempChars, ",");
  armStepFreq = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  armDir = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  gondolaStepFreq = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  gondolaDir = atoi(strtokIndx);

  newArmDirVal = armDir;
  newGondolaDirVal = gondolaDir;

  if (armDir != oldArmDirVal) {
    finalArmStepFreqVal = armStepFreq;
    targetArmStepFreq = 0;
  } else {
    targetArmStepFreq = armStepFreq;
  }
  if (gondolaDir != oldGondolaDirVal) {
    finalGondolaStepFreqVal = gondolaStepFreq;
    targetGondolaStepFreq = 0;
  } else {
    targetGondolaStepFreq = gondolaStepFreq;
  }
}

void updateFreq() {
  digitalWrite(ARM_STEP_PIN, LOW);
  digitalWrite(GONDOLA_STEP_PIN, LOW);
  noInterrupts();

  if (finalArmStepFreqVal == -1) {
    digitalWrite(ARM_DIR_PIN, armDir);
  }
  if (finalGondolaStepFreqVal == -1) {
    digitalWrite(GONDOLA_DIR_PIN, gondolaDir);
  }

  interrupts();

  if (finalArmStepFreqVal == -1) {
    targetArmStepFreq = armStepFreq;
  }
  if (finalGondolaStepFreqVal == -1) {
    targetGondolaStepFreq = gondolaStepFreq;
  }

  delayMicroseconds(5);
}