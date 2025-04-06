#include "functions.h"
#include "../Motor_Control/functions.h"
#include <fstream>
#include <chrono>
using namespace std;

// GLOBAL VARIABLES //

State currentState = State::kInit;
Test currentTest = Tests::RestraintTest;

int RestraintCheck = 0;
int isHomed = 0;
int ArmTest = 0;
int GondolaTest = 0;

bool armHomed = false; 
bool gondolaHomed = false;  

int access = 0; 
int test = 0; 
int cycleCount = 0; 

bool restraint1 = PASS;
bool restraint2 = PASS;

// STATE HANDLE FUNCTIONS //

int InitStateHandle()
{

    int r = performRestraintCheck();

    if (r > 0)
    {
        RestraintCheck = PASS;
    }
    else
    {
        RestraintCheck = ERROR_RESTRAINT;
        return RestraintCheck;
    }

    if (getPosition(SPI0_CHANNEL) == 0)
    {
        isHomed = PASS;
    }
    else
    {
        isHomed = ERROR_HOME;
        return isHomed;
    }

    currentState = State::kAuto;
    return PASS;
}

int AutoStateHandle()
{

    int status = isReadyToRun();

    if (status > 0)
    {
        currentState = State::kRideOp; // might need the option for a ride op to say its good
        return PASS;
    }
    else
    {
        return -1;
    }
}

int RideOpStateHandle()
{
    for (int i = 0; i < 40; i++)
    {
        putchar('d');
    }
    int targetArmMotorFrequency = 100;
    int targetGondolaMotorFrequency = 999;
    int currentArmMotorFrequency = 748;

    auto start = chrono::steady_clock::now();
    while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() < 65)
    {
        if (RestraintCheck > 0)
        {
            RestraintCheck = PASS;
        }
        else
        {
            RestraintCheck = ERROR_RESTRAINT;
            currentState = State::kInit;
            return RestraintCheck;
        }

        // check if gondola/arm is not "abnormal" fix this

        if (currentArmMotorFrequency <= targetArmMotorFrequency)
        {
            ArmTest = PASS;
        }
        else
        {
            ArmTest = ERROR_ARM;
            return ArmTest;
        }

    }

    // logic to see when the ride ends

    this_thread::sleep_for(chrono::seconds(25));

    if (getPosition(SPI0_CHANNEL) == 0)
    {
        isHomed = PASS;
    }
    else
    {
        isHomed = ERROR_HOME;
        return isHomed;
    }

    cycleCount++;
    currentState = State::kAuto;
    return PASS;
}


int MaintenanceSelection(int access, int test) {
    if (access == 1)
    {
        currentState = State::kMaintenance;
        return PASS;
    }

    if (test == 0)
    {
        int result = RestraintTest();
        if (result > 0)
        {
            RestraintCheck = result;
        }
        else
        {
            RestraintCheck = ERROR_RESTRAINT;
            return ERROR_RESTRAINT;
        }
        return result;
    }
    else if (test == 1)
    {
        int result = ArmMotorTest();
        if (result > 0)
        {
           ArmTest = result;
        }
        else 
        {
            ArmTest = ERROR_ARM;
            return ERROR_ARM;
        }
        return result;
    }
    else if (test == 2)
    {
        int result = GondolaMotorTest();
        if (result > 0)
        {
            GondolaTest = result;
        } else {
            GondolaTest = ERROR_GONDOLA;
            return ERROR_GONDOLA;
        }

        return result;
    }
    else if (test == 3)
    {
        int result = isHomedTest();
        if (result > 0) {
            isHomed = result; 
        } else {
            isHomed = ERROR_HOME;
            return ERROR_HOME;
        }
        return result;
    }
    return PASS;
}

int MaintenanceStateHandle()
{
    if (currentState == State::kMaintenance)
    {
        int result = MaintenanceSelection();
        if (result != PASS)
        {
            return result;
        }
        else
        {
            currentState = State::kAuto;
            return PASS;
        }
    }
    return -1;
}


// TESTING FUNCTIONS //

int RestraintTest()
{
    currentTest = Test::RestraintTest;
    unlockRestraints();

    int check1 = isRow1Unlocked();
    int check2 = isRow2Unlocked();

    if (check1 == ERROR_RESTRAINT && check2 == ERROR_RESTRAINT)
    {
        return PASS;
    }
    else
    {
        return ERROR_RESTRAINT;
    }

    this_thread::sleep_for(chrono::seconds(15)); // sleep for 15 seconds;

    lockRestraints();

    int check3 = isRow1Locked();
    int check4 = isRow2Locked();

    if (check3 == PASS && check4 == PASS)
    {
        return PASS;
    }
    else
    {
        return ERROR_RESTRAINT;
    }


    return PASS;
}

int ArmMotorTest()
{
    // ENCODER VALUE IMPLEMENTATION


    currentTest = Test::ArmMotorTest;
    return PASS;
}

int GondolaMotorTest()
{

    // ENCODER VALUE IMPLEMENTATION
    currentTest = Test::GondolaMotorTest;
    return PASS;
}


int isHomedTest()
{
    currentTest = Test::isHomedTest;
    int gp = (int)getPosition();

    // setPosition(); add functionaly
    // Home(); add functionally 

    this_thread::sleep_for(chrono::seconds(15)); // wait for it to home

    if (isHomed())
    {
        return PASS;
    }
    else
    {
        return ERROR_HOME;
    }

    return PASS;
}

// STATE FUNCTIONS //

void getNextState()
{
    switch (currentState)
    {
    case State::kInit:
        InitStateHandle();
        break;

    case State::kAuto:
        AutoStateHandle();
        break;

    case State::kRideOp:
        RideOpStateHandle();
        break;

    case State::kMaintenance:
        MaintenanceStateHandle();
        break;
    }
}

int getCurrentState()
{
    return (int)currentState;
}

int setState(int state)
{
   currentState = (State)state;
   return (int)currentState;
}


// TEST FUNCTIONS //
int getCurrentTest()
{
    return (int)currentTest;
}

int setCurrentTest(int test)
{
    currentTest = (Test)test;
    return (int)currentTest;
}

// ERROR MESSAGES //

string getErrorMessage()
{
    string message = "";

    if (RestraintCheck < 0)
    {
        message += "ERROR 101 (RESTRAINT)";
    }
    if (isHomed < 0)
    {
        message += "ERROR 1203 (HOMING FAULT)";
    }
    if (ArmTest < 0)
    {
        message += "ERROR 1201 (MAIN MOTOR)";
    }
    if (message.empty())
    {
        message += "NO ERRORS";
    }
    return message;
}

string getMaintenanceError()
{
    string message = "";

    if (RestraintCheck < 0) {
        message += "ERROR 101 (RESTRAINT)";
    }
    if (isHomed < 0) {
        message += "ERROR 1203 (HOMING FAULT)";
    }
    if (ArmTest < 0) {
        message += "ERROR 1201 (MAIN MOTOR)";
    }
    if (GondolaTest < 0) {
        message += "ERROR 1202 (GONDOLA MOTOR)";
    }
    if (message.empty()) {
        message += "NO ERRORS";
    }
    return message;
}


string statusMessage() {
    string message = "";
    if (currentState == State::kInit) {
        message += "INITIALIZING";
    } 
    if (currentState == State::kAuto) {
        message += "LOADING"
    } else if (isReadyToRun() == true) {
        message += "READY TO RUN";
    }
    if (currentState == State::kRideOp) {
        message += "RUNNING";
    }
    if (currentState == State::kMaintenance) {
        message += "MAINTENANCE";
    }
    if (currentState == State::kOff) {
        message += "OFF";
    }

    return message; 
}


string getTestStatusMessage() {
    string message = "";

    if (currentTest == Test::RestraintTest) {
        message += "Restraint Test";
    } else if (RestraintTest() == ERROR_RESTRAINT) {
        message += "ERROR 101 (RESTRAINT)";
    } else if (RestraintTest() == PASS) {
        message += "Restraint Test Passed";
    }
    
    if (currentTest == Tests::ArmMotorTest) {
        message += "Main Motor Test";
    } else if (ArmMotorTest() == ERROR_ARM) {
        message += "ERROR 1201 (MAIN MOTOR)";
    } else if (ArmMotorTest() == PASS) {
        message += "Main Motor Test Passed";
    }

    if (currentTest == Test::GondolaMotorTest) {
        message += "Gondola Motor Test";
    } else if (GondolaMotorTest() == ERROR_GONDOLA) {
        message += "ERROR 1202 (GONDOLA MOTOR)";
    } else if (GondolaMotorTest() == PASS) {
        message += "Gondola Motor Test Passed";
    }

    if (currentTest == Test::isHomedTest) {
        message += "Homing Test";
    } else if (isHomedTest() == ERROR_HOME) {
        message += "ERROR 1203 (HOMING FAULT)";
    } else if (isHomedTest() == PASS) {
        message += "Homing Test Passed";

    return message;
}

}

int performRestraintCheck()
{

    int check1 = isRow1Locked(restraint1);
    int check2 = isRow2Locked(restraint2);

    if (check1 == PASS && check2 == PASS)
    {
        RestraintCheck = PASS;
    }
    else
    {
        RestraintCheck = ERROR_RESTRAINT;
    }

    return RestraintCheck;
}

bool isReadyToRun()
{
    string message = getErrorMessage();

    if (message == "NO ERRORS")
    {
        return true;
    }
    else
    {
        return false;
    }
}

string isReadyToRunMessage() {
    string message = "";

    if (isReadyToRun() == true) {
        message += "READY TO RUN";
    } else {
        message += "NOT READY TO RUN";
    }

    return message; 
}

// HMI FUNCTIONS  //

bool start()
{
    int r = performRestraintCheck();
    if (r == PASS)
    {
        RestraintCheck = PASS;
    }
    else
    {
        RestraintCheck = ERROR_RESTRAINT;
    }
    if (getPosition(SPI0_CHANNEL) == 0)
    {
        isHomed = PASS;
    }
    else
    {
        isHomed = ERROR_HOME;
    }
    if (ArmTest == PASS)
    {
        ArmTest = PASS;
    }
    else
    {
        ArmTest = ERROR_HOME;
    }

    getNextState();
    return true;
}


void resetManual()
{
    State currentState = State::kOff;
    RestraintCheck = 0;
    isHomed = 0;
    ArmTest = 0;
}

bool stop()
{
    State currentState = State::kOff;
    return true;
}

int getCycleCount() {
    return cycleCount;
}

int setState(int state){
    currentState = state;
    return currentState;
}

// BACKEND FUNCTIONS //

uint16_t getPosition(int encoder)
{
    
    unsigned char buf[2];

    // Select the encoder
    if(encoder == 1){   
        wiringPiSPIDataRW(encoder-1, buf, 2); // Send command
        

        // Deselect the encoder
        digitalWrite(CS1_PIN, HIGH);
    }

    uint16_t position = ((buf[0] << 8) | buf[1]) & 0x3FFF;  // This is the current position
    return fmod((position*360/16384),360);
}


int isRow1Locked()
{
    if (restraint1)
    {
        return PASS;
    }
    else
    {
        return ERROR_RESTRAINT;
    }
}

int isRow2Locked()
{
    if (restraint2)
    {
        return PASS;
    }
    else
    {
        return ERROR_RESTRAINT;
    }
}

bool unlockRestraints()
{
    // some method to unlock the restraint???
    return PASS;
}
bool lockRestraints()
{
    // some method to lock the restraint???

    return PASS;
}

bool homeArm() {

    uint16_t top = 180; 
    bool dir = getPosition(1) > top;
    uint16_t pos = getPosition(1);
    
    while (!(pos <= 2 || pos >= 358)) {
        pos = getPosition(1);
        if (dir)
            serialPuts(fd, "<0,0,10,0>");
        else
            serialPuts(fd, "<0,0,10,1>");
    
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
    }
    
    // Stop motor
    for (int i = 0; i < SERIAL_ITERATION; i++) {
        serialPuts(fd, "<0,0,0,0>");
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    
    armHomed = true;
    return stop();

}


// RASPI FUNCTIONS

// UNCOMMENT!!!!!!! WHEN PULLING TO PI!!!!!!!

// int setUpGPIO(){
//     if(wiringPiSetupGpio() == -1){
//         std:cerr << "Wring Pi Fail" << std::endl;
//         return -1;
//     }

//     pinMode(ESTOP_IN, INPUT);
//     pinMode(ESTOP_SOURCE, OUTPUT);
//     digitalWrite(ESTOP_SOURCE, HIGH);
//     return 1;
// }

// bool eStopPressed(){

//     return digitalRead(ESTOP_IN);
// }
