#pragma once

#include <iostream>
#include <limits>

using namespace std;

enum class State
{
    kInit = 0,
    kAuto = 1,
    kRideOp = 2,
    kMaintenance = 3
};

enum class StateTest {
    kTest1 = 0, 
    kTest2 = 1,
    kTest3 = 0,
    kTest4 = 0,
    kTest5 = 0 
};


// handling functions
void RideShowStateHandle();
void RideOpStateHandle(State *currentState, bool test1, bool test2, bool test3);
void InitStateHandle(State *currentState, bool test1, bool test2, bool test3);
void AutoStateHandle(State *currentState, bool test1, bool test2, bool test3);
void MaintenanceStateHandle(State *currentState, bool test1, bool test2, bool test3);


// state transition function
void getNextState(State *currentState, bool test1, bool test2, bool test3);