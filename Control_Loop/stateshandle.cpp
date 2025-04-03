#include "functions.h"
#include "../Motor_Control/functions.h"
#include <fstream>
#include <chrono>
using namespace std;

// Function prototypes

// State currentState = State::kInit;


// java stuff 
int RestraintCheck_java = 0;
int isHomed_java = 0;
int ArmTest_java = 0;

// state transition function
void getNextState(State *currentState, int RestraintCheck, int isHomed, int ArmTest)
{
    switch (*currentState)
    {
    case State::kInit: // checks tests 1,2
        InitStateHandle(currentState, RestraintCheck, isHomed);
        break;

    case State::kAuto: // checks tests 1,2,3
        AutoStateHandle(currentState, RestraintCheck, isHomed, ArmTest);
        break;

    case State::kRideOp: // arm motor rotation and gondola motor rotation (apart of auto state for now)
        RideOpStateHandle(currentState, RestraintCheck, isHomed, ArmTest);
        break;

    case State::kMaintenance:
        // MaintenanceStateHandle(currentState, currentTest, RestraintCheck, isHomed, ArmTest, test4, test5);
        break;
    }
}

// handling functions
int RideOpStateHandle(State *currentState, int RestraintCheck, int isHomed, int ArmTest)
{
    // start ride
    // putChar(serialPort, 'D');

    // target values and current values
    int targetArmMotorFrequency = 200;
    int targetGondolaMotorFrequency = 100;
    int currentArmMotorFrequency = 150;

    bool restraint = false;

    // timer

    auto start = chrono::steady_clock::now();
    while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() < 65)
    { // during ride cycle

        if (restraint)
        {
            RestraintCheck = PASS;
        }
        else
        {
            RestraintCheck = -1;
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

    // AFTER RIDE CYCLE

    if (getPosition() == 0)
    {
        *currentState = State::kAuto;
    }
    else
    {
        isHomed = ERROR_HOME;
        return isHomed;
    }

    return PASS;
}

int InitStateHandle(State *currentState, int RestraintCheck, int isHomed)
{

    // check RestraintCheck
    // method to get the bool value

    bool restraint1 = false;
    bool restraint2 = false;

    int r = performRestraintCheck(restraint1, restraint2);

    if (r > 0)
    {
        RestraintCheck = PASS;
        // return RestraintCheck;
    }
    else
    {
        RestraintCheck = ERROR_RESTRAINT;
        return RestraintCheck;
    }

    // check if ride is home position
    // get homed location

    if (getPosition() == 0)
    {
        isHomed = PASS;
    }
    else
    {
        isHomed = ERROR_HOME;
        return isHomed;
    }

    *currentState = State::kAuto;
    return PASS;
}

int AutoStateHandle(State *currentState, int RestraintCheck, int isHomed, int ArmTest)
{
    bool status = isReadyToRun(RestraintCheck, isHomed, ArmTest);
    int status_num = 0;

    if (status)
    {
        status_num = 1;
    }
    else
    {
        status_num = -1;
        return status_num;
    }

    *currentState = State::kRideOp;
    return PASS;
}

// other functions

string getErrorMessage(int RestraintCheck, int isHomed, int ArmTest)
{
    string message = "";

    if (RestraintCheck < 0)
    {
        message += "ERROR 101 (RESTRAINTS)";
    }
    if (isHomed < 0)
    {
        message += "ERROR 102 (NOT HOMED)";
    }
    if (ArmTest < 0)
    {
        message += "ERROR 103";
    }
    if (message.empty())
    {
        return "NO ERRORS/n";
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
    tm *localtm = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtm);

    file << "[" << timestamp << "]" << message << endl;
    file.close();
}

// hmi functions

string getErrorMessage()
{
    string message = "";

    if (RestraintCheck_java < 0) {
        message += "ERROR 101 (RESTRAINT)";
    } 
    if (isHomed_java < 0) {
        message += "ERROR 102 (NOT HOMED)";
    }
    if (ArmTest_java < 0) {
        message += "ERROR 103 (ARMS)"
    }
    if (message.empty()) {
        message += "NO ERRORS";
    }
    logErrorMessage(message);
    return message; 
}

bool start()
{
    int r = performRestraintCheck();
    if (r == PASS)
    {
        RestraintCheck_java = PASS;
    }
    else
    {
        RestraintCheck_java = ERROR_RESTRAINT;
    }
    if (getPosition() == 0)
    {
        isHomed_java = PASS;
    }
    else
    {
        isHomed_java = ERROR_HOME;
    }
    if (ArmTest_java == PASS)
    {
        ArmTest_java = PASS;
    }
    else
    {
        ArmTest_java = ERROR_HOME;
    }

    getNextState(&currentState, RestraintCheck_java, isHomed_java, ArmTest_java);
    return true;
}

bool stop()
{
    currentState = State::kOff;
    RestraintCheck_java = 0;
    isHomed_java = 0;
    ArmTest_java = 0;

    return true;
}

int performRestraintCheck() {
    bool restraint1 = true; 
    bool restraint2 = false; 

    int check1 = isRow1Locked(restraint1);
    int check2 = isRow2Locked(restraint2);

    if (check1 = PASS && check2 = PASS) {
        RestraintCheck_java = PASS; 
    } else {
        RestraintCheck_java = ERROR_RESTRAINT;
    }

    return RestraintCheck_java;
}


bool isReadyToRun() {
    string message = getErrorMessage();

    if (message == "NO ERRORS") {
        return true; 
    } else {
        return false; 
    }

}

string isReadyToRunMessage() {
    string ready_to_run = "RIDE IS READY TO RUN";
    string cannot_run = "RIDE IS NOT READY TO RUN";

    if (isReadyToRun()) {
        return ready_to_run;
    } else {
        return cannot_run;
    }
}

// State getCurrentState() {
//     return currentState;
// }

// // need to verify with AARON!!!

// void getNextState() {
//     switch (currentState) {
//     case State::kInit: // checks tests 1,2
//         InitStateHandle(&currentState, RestraintCheck_java, isHomed_java);
//         break;

//     case State::kAuto: // checks tests 1,2,3
//         AutoStateHandle(&currentState, RestraintCheck_java, isHomed_java, ArmTest_java);
//         break;

//     case State::kRideOp: // arm motor rotation and gondola motor rotation (apart of auto state for now)
//         RideOpStateHandle(&currentState, RestraintCheck_java, isHomed_java, ArmTest_java);
//         break;

//     case State::kMaintenance:
//         // MaintenanceStateHandle(&currentState, currentTest, RestraintCheck_java, isHomed_java, ArmTest_java, test4, test5);
//         break;
//     }
// }

int sendState(int state) {

    if (getCurrentState() == (int) State::kInit || getCurrentState() == (int) State::kAuto || getCurrentState() == (int) State::kRideOp || getCurrentState() == (int) State::kMaintenance) {
        currentState = (State) state;
        return state; 
    }
    return -1;
}



bool isReadyToRun(int RestraintCheck, int isHomed, int ArmTest)
{
    return (getErrorMessage(RestraintCheck, isHomed, ArmTest) == "NO ERRORS");
}

string isReadyToRunMessage(int RestraintCheck, int isHomed, int ArmTest)
{
    string ready_to_run = "RIDE IS READY TO RUN";
    string cannot_run = "RIDE IS NOT READY TO RUN";

    if (isReadyToRun(RestraintCheck, isHomed, ArmTest) == PASS)
    {
        return ready_to_run;
    }
    else
    {
        return cannot_run;
    }
}

int getPosition()
{
    return 0;
}


int performRestraintCheck(bool restraint1, bool restraint2)
{
    // method to get the bool value of restraint check

    if (isRow1Locked(restraint1) == PASS && isRow2Locked(restraint2) == PASS)
    {
        return PASS;
    }
    else
    {
        return ERROR_RESTRAINT;
    }
}

int isRow1Locked(bool restraint1)
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

int isRow2Locked(bool restraint2)
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
    // some method to unlock the RestraintCheck???
    return PASS;
}
bool lockRestraints()
{
    // some method to lock the RestraintCheck???

    return PASS;
}
