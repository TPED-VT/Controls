const int ARM_STEP_PIN = 3, ARM_DIR_PIN = 8, ARM_ENA_PIN = 9;
const int GONDOLA_STEP_PIN = 5, GONDOLA_DIR_PIN = 10, GONDOLA_ENA_PIN = 11;

volatile int armStepFreq = 0, gondolaStepFreq = 0;
volatile int currentArmStepFreq = 0, currentGondolaStepFreq = 0;
volatile int targetArmStepFreq = 0, targetGondolaStepFreq = 0; 

volatile unsigned long lastArmStep = 0, lastGondolaStep = 0;
volatile unsigned long armStepInterval = 0, gondolaStepInterval = 0;

bool armStepState = LOW, gondolaStepState = LOW, started = false;
int armDir = 0, gondolaDir = 0;  // Store current direction

// Serial parsing variables
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];  // Temporary array for parsing

boolean newData = false;

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
}

void loop() {
  unsigned long now = micros();

  static unsigned long lastRampUpdate = 0;
  if (now - lastRampUpdate >= 10000) {
    lastRampUpdate = now;
    if (currentArmStepFreq < targetArmStepFreq) {
      currentArmStepFreq++;
    } else if (currentArmStepFreq > targetArmStepFreq) {
      currentArmStepFreq--;
    }
    if (currentArmStepFreq > 0) {
      armStepInterval = max(500000L / currentArmStepFreq, 10UL);
    } else {
      armStepInterval = 0;
    }
    if (currentGondolaStepFreq < targetGondolaStepFreq) {
      currentGondolaStepFreq++;
    } else if (currentGondolaStepFreq > targetGondolaStepFreq) {
      currentGondolaStepFreq--;
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
  // Non-blocking serial read and process new data if available
  recvWithStartEndMarkers();
  if (newData) {
    started = true;
    strcpy(tempChars, receivedChars);
    parseData();
    updateFreq();
    newData = false;
  }
}

// ======== Serial Handling Functions ========

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
        receivedChars[ndx] = '\0';  // Null-terminate the string
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
}

void updateFreq() {
  digitalWrite(ARM_STEP_PIN, LOW);
  digitalWrite(GONDOLA_STEP_PIN, LOW);
  noInterrupts();
  digitalWrite(ARM_DIR_PIN, armDir);
  digitalWrite(GONDOLA_DIR_PIN, gondolaDir);
  interrupts();
  targetArmStepFreq = armStepFreq;
  targetGondolaStepFreq = gondolaStepFreq;
  delayMicroseconds(5);
}
