#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <limits>

#define PASS 1

using namespace std;

enum class State
{
    kInit = 0,
    kAuto = 1,
    kRideOp = 2,
    kMaintenance = 3
};


// handling functions
int RideOpStateHandle(State *currentState, int RestraintCheck, int isHomed, int ArmTest);
int InitStateHandle(State *currentState, int RestraintCheck, int isHomed);
int AutoStateHandle(State *currentState, int RestraintCheck, int isHomed, int ArmTest);
int MaintenanceStateHandle(State *currentState, int RestraintCheck, int isHomed, int ArmTest, int test4, int test5);


// other functions 
string getErrorMessage(int RestraintCheck, int isHomed, int ArmTest);
int getPosition();
int performRestraintCheck(bool restraint1, bool restraint2);
int isRow1Locked(bool restraint1);
int isRow2Locked(bool restraint2);

bool unlockRestraints();
bool lockRestraints();


bool isReadyToRun(int RestraintCheck, int isHomed, int ArmTest);
string isReadyToRunMessage(int RestraintCheck, int isHomed, int ArmTest);


// state transition function
void getNextState(State *currentState, int RestraintCheck, int isHomed, int ArmTest);

#endif