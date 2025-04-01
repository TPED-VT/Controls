#include "functions.h"
#include "../Motor_Control/functions.h"

// Function prototypes

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

    // target values and current values
    int targetArmMotorFrequency = 200;
    int targetGondolaMotorFrequency = 100;
    int currentArmMotorFrequency = 150;

    bool restraint = false;

    for (int i = 0; i < 1000; i++)
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
            ArmTest = -1;
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
        isHomed = -1;
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
        RestraintCheck = -1;
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
        isHomed = -1;
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
    string test1_error = "TEST 1 HAS FAILED";
    string test2_error = "TEST 2 HAS FAILED";
    string test3_error = "TEST 3 HAS FAILED";
    string no_errors = "NO ERRORS";

    if (RestraintCheck < 0)
    {
        return test1_error;
    }
    else if (isHomed < 0)
    {
        return test2_error;
    }
    else if (ArmTest < 0)
    {
        return test3_error;
    }
    else
    {
        return no_errors;
    }

    return no_errors;
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
    return 12;
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
        return -1;
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
        return -1;
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
        return -1;
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


