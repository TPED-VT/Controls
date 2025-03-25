#define CATCH_CONFIG_MAIN 
#include "catch2/catch.hpp"

#include "Control_Loop/functions.h"

TEST_CASE("Test 1") {
    State currentState = State::kInit;
    bool test1 = true;
    
    REQUIRE(test1);
}


/*

#include "functions.h"
#include "stateshandle.cpp"
#include "states.cpp"




    TEST 1 - Test1() function
    Check if the Gondola Motor Rotation and Arm Motor Rotation is working properly
    If the Gondola Motor Rotation or Arm Motor Rotation (or both) are not working properly, the operator is advised to stop the ride and call maintenance



bool g_motor = true; // add later a way to see if the motor is working properly 
bool a_motor = true; // add later a way to see if the motor is working properly

bool Test1(State *currentState, bool test1, bool g_motor, bool a_motor) {

    if (g_motor && a_motor) {
        test1 = true;
    }
    else {
        test1 = false;
    }

    getNextState(currentState, test1, true, true);

    return test1;
}

/*

    TEST 2 - Test2() function
    Check if restraints are locked and unlocked properly
    If the restraints are not locked or unlocked properly, the operator is advised to stop the ride and call maintenance



bool restraints = true; // add later a way to see if the restraints are working properly

bool Test2(State *currentState, bool test2, bool restraints) {

    if (restraints) {
        test2 = true; 
    }
    else {
        test2 = false; 
    }
    getNextState(currentState, true, test2, true);

    return test2; 
}

/*

    TEST 3 - Test3() function
    Check if the Emergency Stop Button has not been pressed 
    If the Emergency Stop Button has been pressed, the ride will stop and the operator is advised to call maintenance immediately. 




bool emergency_stop = false; // add later a way to see if the emergency stop button has been pressed

bool Test3(State *currentState, bool test3, bool emergency_stop) {

    if (emergency_stop) {
        test3 = false; 
    }
    else {
        test3 = true; 
    }
    getNextState(currentState, test3);

    return test3; 
}
*/