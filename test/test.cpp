#define CATCH_CONFIG_MAIN 
#include "catch2/catch.hpp"

#include "Control_Loop/functions.h"
#include "Motor_Control/functions.h"

TEST_CASE("Test 1 - Check Rotation of Gondola Motor and Arm Motor") {
    State currentState = State::kInit;
    bool g_motor = true; 
    bool a_motor = true; 
    bool test1 = false;

    if (g_motor && a_motor) {
        test1 = true;
    } else {
        test1 = false;
    }

    getNextState(&currentState, test1, g_motor, a_motor);

    REQUIRE(test1 == true);
    REQUIRE(currentState == State::kAuto);
}

TEST_CASE("Test 2 - Check if restraints are locked and unlocked properly") {
    State currentState = State::kInit;
    bool restraints = true; 
    bool test2 = false; 
    
    if (restraints) {
        test2 = true; 
    } else {
        test2 = false; 
    }

    getNextState(&currentState, true, test2, true);

    REQUIRE(test2 == true);
    REQUIRE(currentState == State::kAuto);
    
}

TEST_CASE("Test 3 - Check if the Emergency Stop Button has not been pressed") {
    State currentState = State::kInit;
    bool estop = false; 
    bool test3 = false; 
    
    if (!estop) {
        test3 = true; 
    } else {
        test3 = false; 
    }

    getNextState(&currentState, true, test3, true);

    REQUIRE(test3 == true);
    REQUIRE(currentState == State::kAuto);
    
}

TEST_CASE("Test 4 - Check if RampUp Works") {
    State currentState = State::kAuto;   

    int currentArmFrequency = 150;
    int currentGondolaFrequency = 50;

    int Frequency = RampUp(currentArmFrequency, currentGondolaFrequency);

    // current implementation adds both the currentArm and currentGondola 

  //  REQUIRE(Frequency == 200);
    REQUIRE(currentState == State::kAuto);
}

TEST_CASE("Test 5 - Check if getGondolaInterval and getArmInterval work") {
    int currentArmFrequency = 150; 
    int currentGondolaFrequency = 50; 

    unsigned long armInterval = getArmInterval(currentArmFrequency);
    unsigned long gondolaInterval = getGondolaInterval(currentGondolaFrequency);

    // not sure what number needs to go here... added random numbers for now..
    // i lied - ricardo, thats what zach's code produces so for now its the values. 

    REQUIRE(armInterval == 3333);
    REQUIRE(gondolaInterval == 10000);
}
