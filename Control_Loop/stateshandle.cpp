#include "functions.h"
#include "../Motor_Control/functions.h"
#include <fstream>
#include <chrono>
using namespace std;

// GLOBAL VARIABLES //

State currentState = State::kInit;
int RestraintCheck = 0;
int isHomed = 0;
int ArmTest = 0;

bool restraint1 = PASS;
bool restraint2 = PASS;


// STATE HANDLE FUNCTIONS // 

int InitStateHandle()
{

    int r = performRestraintCheck(restraint1, restraint2);

    if (r > 0)
    {
        RestraintCheck = PASS;
    }
    else
    {
        RestraintCheck = ERROR_RESTRAINT;
        return RestraintCheck;
    }

    if (getPosition() == 0)
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

    putchar('D');

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
            return RestraintCheck;
        }

        // check if gondola/arm is not "abnormal"

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

    if (getPosition() == 0)
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
        // MaintenanceStateHandle();
        break;
    }
}

int getCurrentState()
{
    return (int)currentState;
}

int setState(int state)
{

   if (state == 0) {
    currentState = State::kInit;
   } else if (state == 1) {
    currentState = State::kAuto;
   } else if (state == 2) {
    currentState = State::kRideOp;
   } else if (state == 3) {
    currentState = State::kMaintenance;
   } else if (state == 4) {
    currentState = State::kOff;
   }

   return (int)currentState;
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
        message += "ERROR 102 (NOT HOMED)";
    }
    if (ArmTest < 0)
    {
        message += "ERROR 103 (ARMS)";
    }
    if (message.empty())
    {
        message += "NO ERRORS";
    }
    logErrorMessage(message);
    return message;
}


void logErrorMessage(const string &message)
{
    ofstream file("error_log.text", ios::app);
    if (!file.is_open())
    {
        return;
    }

    // get time

    time_t now = time(0);
    tm localtm;
    localtime_s(&localtm, &now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &localtm);

    file << "[" << timestamp << "]" << message << endl;
    file.close();
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
    if (getPosition() == 0)
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

bool stop()
{
    State currentState = State::kOff;
    RestraintCheck = 0;
    isHomed = 0;
    ArmTest = 0;

    return true;
}


// BACKEND FUNCTIONS // 

int getPosition()
{
    return 0;
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
