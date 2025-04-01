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
void RideOpStateHandle(State *currentState, int test1, int test2, int test3);
void InitStateHandle(State *currentState, int test1, int test2, int test3);
void AutoStateHandle(State *currentState, int test1, int test2, int test3);
void MaintenanceStateHandle(State *currentState, int test1, int test2, int test3, int test4, int test5);


// other functions 
string getErrorMessage(int test1, int test2);
int getPosition();
bool restraintCheck(bool restraint);

bool isReadyToRun(int test1, int test2);
string isReadyToRunMessage(int test1, int test2);


// state transition function
void getNextState(State *currentState, int test1, int test2, int test3);

#endif