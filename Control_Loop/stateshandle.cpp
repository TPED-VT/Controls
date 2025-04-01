#include "functions.h"
#include "../Motor_Control/functions.h"

// state transition function
void getNextState(State *currentState, StateTest *currentTest, int test1, int test2, int test3, bool test4, bool test5)
{
    switch (*currentState)
    {
    case State::kInit: // checks tests 1,2
        InitStateHandle(currentState, test1, test2);
        break;

    case State::kAuto: // checks tests 1,2,3
        AutoStateHandle(currentState, test1, test2, test3);
        break;

    case State::kRideOp: // arm motor rotation and gondola motor rotation (apart of auto state for now)
        RideOpStateHandle(currentState, test1, test2, test3);
        break;

    case State::kMaintenance:
        // MaintenanceStateHandle(currentState, currentTest, test1, test2, test3, test4, test5);
        break;
    }
}


// handling functions
int RideOpStateHandle(State *currentState, int test1, int test2, int test3)
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
            test1 = PASS;
        }
        else
        {
            test1 = -1;
            return test1;
            break;
        }

        // check if gondola/arm is not "abnormal"

        if (currentArmMotorFrequency <= targetArmMotorFrequency)
        {
            test3 = PASS;
        }
        else
        {
            test3 = -1;
            return test3;
        }
    }

    // AFTER RIDE CYCLE

    if (getPosition() == 0)
    {
        *currentState = State::kAuto;
    }
    else
    {
        test2 = -1;
        return test2;
    }

    return PASS;
}


int InitStateHandle(State *currentState, int test1, int test2)
{

    // check restraints
    // method to get the bool value

    bool restraint = false;

    if (restraint)
    {
        test1 = PASS;
        // return test1;
    }
    else
    {
        test1 = -1;
        return test1;
    }

    // check if ride is home position
    // get homed location

    if (getPosition() = 0)
    {
        test2 = PASS;
    }
    else
    {
        test2 = -1;
        return test2;
    }

    *currentState = State::kAuto;
    return PASS;
}

int AutoStateHandle(State *currentState, bool status, int test1, int test2, int test3)
{
    if (getErrorMessage(test1, test2, test3) == "NO ERRORS")
    {
        status = true;
    }
    else
    {
        status = false;
    }

    *currentState = State::kRideOp;
    return PASS;
}

// other functions


string getErrorMessage(int test1, int test2, int test3)
{
    string test1_error = "TEST 1 HAS FAILED";
    string test2_error = "TEST 2 HAS FAILED";
    string test3_error = "TEST 3 HAS FAILED";
    string no_errors = "NO ERRORS";

    if (test1 < 0)
    {
        return test1_error;
    }
    else if (test2 < 0)
    {
        return test2_error;
    }
    else if (test3 < 0)
    {
        return test3_error;
    }
    else
    {
        return no_errors;
    }

    return no_errors;
}

bool isReadyToRun(int test1, int test2)
{
    return (getErrorMessage(test1, test2) == "NO ERRORS");
}

string isReadyToRunMessage(bool status, int test1, int test2)
{
    string ready_to_run = "RIDE IS READY TO RUN";
    string cannot_run = "RIDE IS NOT READY TO RUN";

    if (isReadyToRun(status) == PASS)
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

bool restraintCheck(bool restraint)
{
    // method to get the bool value of restraint check

    if (restraint)
    {
        return PASS;
    }
    else
    {
        return -1;
    }
}
