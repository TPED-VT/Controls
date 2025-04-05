#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <limits>
#include <time.h>
#include <ctime>
#include <fstream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiSPI.h>
#include <cmath>

#define PASS 1
#define ERROR_RESTRAINT -1
#define ERROR_HOME -2
#define ERROR_ARM -3

#define ESTOP_IN 25
#define ESTOP_SOURCE 27


#define CS1_PIN 10  // Chip Select for Encoder 1 (Gondola)
#define CS2_PIN 11  // Chip Select for Encoder 0 (Arm)

#define SPI0_CHANNEL 0 // SPI Bus 0 for Gondola (Encoder 1)
#define SPI1_CHANNEL 1 // SPI Bus 1 for Arm (Encoder 0)

#define READ_COMMAND 0x3F

#define SERIAL_ITERATION 40
#define ARM_HOME_POS 0 // 0 degrees is the reative home position




// int serialPort = serialOpen("/dev/ttyACM", 9600);

// if (serialPort < 0) {
//     fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
//     return -1; 
// }

using namespace std;

enum class State
{
    kInit = 0,
    kAuto = 1,
    kRideOp = 2,
    kMaintenance = 3,
    kOff = 4
};

// handling functions
int InitStateHandle();
int AutoStateHandle();
int RideOpStateHandle();
//int MaintenanceStateHandle(State *currentState, int RestraintCheck, int isHomed, int ArmTest, int test4, int test5);

// other functions 
string getErrorMessage();
// void logErrorMessage(const string& message);

// E-STOP function
int setUpGPIO();
bool eStopPressed();

// hmi functions
string getErrorMessage();
string isReadyToRunMessage();
bool isReadyToRun();
// bool isRideRunning();
int performRestraintCheck();
int isRow1Locked();
int isRow2Locked();
int unlockRestraints(); // implementation
int lockRestraints(); // implementation
bool start(); 
bool stop(); 
bool home();

// Back(end)
uint16_t getPosition(int encoder);
int performRestraintCheck();

// state transition function
void getNextState();
int getCurrentState(); 
int setState(int state);


#endif