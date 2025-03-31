#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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

enum class Sector {
    kSector0 = 0, 
    kSector1 = 1, 
    kSector2 = 2, 
    kSector3 = 3, 
    kSector4 = 4
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
void RideOpStateHandle(State *currentState, Sector *currentSector, bool test1, bool test2, bool test3);
void InitStateHandle(State *currentState, bool test1, bool test2, bool test3);
void AutoStateHandle(State *currentState, bool test1, bool test2, bool test3);
void MaintenanceStateHandle(State *currentState, bool test1, bool test2, bool test3);


// state transition function
int getNextState(State *currentState, Sector *currentSector, bool test1, bool test2, bool test3);
int getCurrentSector(State *currentState, Sector *currentSector);
int getNextSector(State *currentState, Sector *currentSector);

#endif