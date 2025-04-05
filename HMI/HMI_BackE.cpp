#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include "HMI_BackE.h"  // Generated header file from HMI_1BackEnd.h
#include <iostream>
#include "../Control_Loop/functions.h" // needs to change
#include <ostream>
#include <thread>
#include <chrono>

using namespace std; 

State currentState = State::kInit;
bool RestraintCheck = false; 
bool isHomed = false; 
bool ArmTest = false; 

double cyclePercent = 0.5; // dummy value testing
double c = 0; 

void readCyclePercent() {
    for (int i = 0; i < 1000; i++) {
        cyclePercent++;
    }
    cout << cyclePercent << endl;
    this_thread::sleep_for(chrono::seconds(5));
}

// RASPI STUFF 

// UNCOMMENT!!! IF YOU ARE PULLING TO RASPI 

// JNIEXPORT jint JNICALL Java_HMI_1BackE_setUpGPIO(JNIEnv *env, jobject obj) {
//     if(wiringPiSetup() == -1){
//         std:cerr << "Wring Pi Fail" << std::endl;
//         return -1;
//     }

//     pinMode(ESTOP_IN, INPUT);
//     pinMode(ESTOP_SOURCE, OUTPUT);
//     digitalWrite(ESTOP_SOURCE, HIGH);
//     return 1;
// }

// JNIEXPORT jboolean JNICALL Java_HMI_1BackE_eStopPressed(JNIEnv *env, jobject obj) {
//     cout << "eStopPressed called: " << !digitalRead(ESTOP_IN) << endl;  
//     return !digitalRead(ESTOP_IN);
// }


// STATE HANDLING 

JNIEXPORT void JNICALL Java_HMI_1BackE_getNextState(JNIEnv *env, jobject obj) {
    cout << "getNextState is called" << endl; 
    getNextState();
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_getCurrentState(JNIEnv *env, jobject obj) {
    cout << "getCurrentState called" << endl;
    return static_cast<jint>(currentState);
  
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_setState(JNIEnv *env, jobject obj, jint state) {
    cout << "JNI setState called with state: " << state << endl;
    setState((int)state);
}


// RIDE CONTROL 

JNIEXPORT jint JNICALL Java_HMI_1BackE_start(JNIEnv *env, jobject obj) {
    cout << "start called" << endl;
    start();
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_stop(JNIEnv *env, jobject obj) {
    cout << "stop called" << endl;
    stop();
}

JNIEXPORT void JNICALL Java_HMI_1BackE_reset(JNIEnv* env, jobject obj){
    
    for(int i = 0; i < 40; i++)
        serialPutchar(fd, 'r');
    setState(0);
}

JNIEXPORT void JNICALL Java_HMI_1BackE_resetManual(JNIEnv* env, jobject obj){
    cout << "resetManual called" << endl;
    resetManual();
}


// RESTRAINT CONTROL 

JNIEXPORT jint JNICALL Java_HMI_1BackE_isRow1Locked(JNIEnv *env, jobject obj) {
    cout << "isRow1Locked called" << endl;
    if (isRow1Locked() == PASS) {
        return PASS; 
    } else {
        return ERROR_RESTRAINT;
    }
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_isRow2Locked(JNIEnv *env, jobject obj) {
    cout << "isRow2Locked called" << endl;
    if (isRow2Locked() == PASS) {
        return PASS; 
    } else {
        return ERROR_RESTRAINT;
    }
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_lockRestraints(JNIEnv *env, jobject obj) {
    cout << "lockRestraints called" << endl;
    if (lockRestraints() == PASS) {
        return PASS; 
    } else {
        return ERROR_RESTRAINT;
    }
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_unlockRestraints(JNIEnv *env, jobject obj) {
    cout << "unlockRestraints called" << endl;
    if (unlockRestraints() == PASS) {
        return PASS; 
    } else {
        return ERROR_RESTRAINT;
    }
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_performRestraintCheck(JNIEnv *env, jobject obj) {
    cout << "performRestraintCheck called" << endl;
    return performRestraintCheck();
}

// BACK END 

JNIEXPORT jint JNICALL Java_HMI_1BackE_getPosition(JNIEnv *env, jobject obj) {
    cout << "Position: 0" << endl;
    return 0;
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isReadyToRun(JNIEnv *env, jobject obj) {
    cout << "isReadyToRun called" << endl;
    return isReadyToRun();
}

JNIEXPORT jstring JNICALL Java_HMI_1BackE_isReadyToRunMessage(JNIEnv *env, jobject obj) {
    cout << "isReadyToRunMessage called" << endl;
    string result = isReadyToRunMessage();
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRideRunning(JNIEnv *env, jobject obj) {
    cout << "isRideRunning called" << endl; 
    return JNI_TRUE; 
}


// ERROR HANDLING 

JNIEXPORT jstring JNICALL Java_HMI_1BackE_getErrorMessage(JNIEnv *env, jobject obj) {
    cout << "getErrorMessage called" << endl;
    string result = getErrorMessage();
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL Java_HMI_1BackE_getErrorTestMessage(JNIEnv *env, jobject obj) {
    cout << "getErrorMessage called" << endl;
    string result = getErrorTestMessage();
    return env->NewStringUTF(result.c_str());
}


// RIDE CYCLE OTHER STUFF

JNIEXPORT void JNICALL Java_HMI_1BackE_startCyclePercent(JNIEnv* env, jobject obj) {
    thread cycleThread(readCyclePercent);
    cycleThread.detach();
}

JNIEXPORT jdouble JNICALL Java_HMI_1BackE_getCyclePercent(JNIEnv* env, jobject obj) {
    return static_cast<jdouble>(cyclePercent);
}

JNIEXPORT void JNICALL Java_HMI_1BackE_setCyclePercent(JNIEnv* env, jobject obj, jint percent) {
    cyclePercent = percent; 
}

JNIEXPORT void JNICALL Java_HMI_1BackE_disbatch(JNIEnv* env, jobject obj){
    for(int i = 0; i < 40; i++)
        serialPutchar(fd, 'd');
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_MaintenanceSelection(JNIEnv *env, jobject obj, jint access, jint test) {
    cout << "MaintenanceSelection called" << endl;
    return MaintenanceSelection((int)access, (int)test);
}


// JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationGondolaClockwise(JNIEnv *env, jobject obj) {
//     cout << "isRotationGondolaClockwise called" << endl;  
//     return JNI_TRUE; 
// }

// JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationGondolaCounterClockwise(JNIEnv *env, jobject obj) {
//     cout << "isRotationGondolaCounterClockwise called" << endl;  
//     return JNI_TRUE; 
// }

// JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationArmClockwise(JNIEnv *env, jobject obj) {
//     cout << "isRotationArmClockwise called" << endl;  
//     return JNI_TRUE; 
// }

// JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationArmCounterClockwise(JNIEnv *env, jobject obj) {
//     cout << "isRotationArmCounterClockwise called" << endl;  
//     return JNI_TRUE; 
// }
