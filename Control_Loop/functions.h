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
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <cstring>

#define AMT22_CMD_POSITION 0x10

#define PASS 1
#define ERROR_RESTRAINT -1
#define ERROR_HOME -2
#define ERROR_ARM -3
#define ERROR_GONDOLA -4

#define ESTOP_IN 25
#define ESTOP_SOURCE 27

#define CS1_PIN 10  // Chip Select for Encoder 1 (Gondola)
#define CS2_PIN 11  // Chip Select for Encoder 0 (Arm)

#define SPI0_CHANNEL 0 // SPI Bus 0 for Gondola (Encoder 1)
#define SPI1_CHANNEL 1 // SPI Bus 1 for Arm (Encoder 0)

#define READ_COMMAND 0x3F

#define SERIAL_ITERATION 40
#define ARM_HOME_POS 0 // 0 degrees is the reative home position

using namespace std;

enum class State
{
    kInit = 0,
    kAuto = 1,
    kRideOp = 2,
    kMaintenance = 3,
    kOff = 4
};

enum class Test {
    RestraintTest = 0, 
    ArmMotorTest = 1, 
    GondolaMotorTest = 2,
    isHomedTest = 3
};

int setupSPI(const char* device);
uint16_t readAMT22Position(int dd);

// handling functions
int InitStateHandle();
int AutoStateHandle();
int RideOpStateHandle();
int MaintenanceStateHandle();

// other functions 
string getErrorMessage();
string getMaintenanceError();

// E-STOP function
int setUpGPIO();
bool eStopPressed();

// hmi functions
string getErrorMessage();
string isReadyToRunMessage();

// status
string getTestStatusMessage();
string statusMessage();

string getMaintenanceError();
bool isReadyToRun();

// other stuff

int performRestraintCheck();
int isRow1Locked();
int isRow1Unlocked();
int isRow2Locked();
int isRow2Unlocked();
bool unlockRestraints(); 
bool lockRestraints(); 
bool start(); 
bool stop(); 
void resetManual();

// stuff 
bool homeArm();

// test stuff 
int getCurrentTest(); 
int setCurrentTest(int test);
int RestraintTest();
int ArmMotorTest();
int GondolaMotorTest();
int isHomedTest();

// Back(end)
uint16_t getPosition(int encoder);
int performRestraintCheck();
int MaintenanceSelection(int access, int test);

// state transition function
void getNextState();
int getCurrentState(); 
int setState(int state);
int getCycleCount();


#endif