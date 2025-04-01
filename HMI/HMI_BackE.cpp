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
Sector currentSector = Sector::kSector1;
bool test1 = false; 
bool test2 = false; 
bool test3 = false; 

double cyclePercent = 0.5; // dummy value testing

void readCyclePercent() {
    for (int i = 0; i < 1000; i++) {
        cyclePercent++;
    }
    cout << cyclePercent << endl;
    this_thread::sleep_for(chrono::seconds(5));
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_getPosition(JNIEnv *env, jobject obj) {
    // Update return type to void as per header
    cout << "Position: 1" << endl;
    return 1;
}

// State and sector machines

JNIEXPORT void JNICALL Java_HMI_1BackE_setState(JNIEnv *env, jobject obj, jint state) {
    currentState = static_cast<State>(state);
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_getCurrentState(JNIEnv *env, jobject obj) {
    // Return type is jint as per the header
    return static_cast<jint>(currentState);
}

// Sector functions

// JNIEXPORT jint JNICALL Java_HMI_1BackE_getNextSector(JNIEnv *env, jobject obj) {
//     getNextState(&currentState, &currentSector, test1, test2, test3);
//     return static_cast<jint>(currentSector); // Corrected return type
// }

// JNIEXPORT jint JNICALL Java_HMI_1BackE_getCurrentSector(JNIEnv *env, jobject obj) {
//     getCurrentSector(&currentState, &currentSector);
//     return static_cast<jint>(currentSector); // Corrected return type
// }

// JNIEXPORT jint JNICALL Java_HMI_1BackE_setNextSector(JNIEnv *env, jobject obj, jint sector) {
//     currentSector = static_cast<Sector>(sector);
//     return static_cast<jint>(currentSector); // Corrected return type
// }

// Ride functions

JNIEXPORT void JNICALL Java_HMI_1BackE_startCyclePercent(JNIEnv* env, jobject obj) {
    thread cycleThread(readCyclePercent);
    cycleThread.detach();
}

JNIEXPORT jdouble JNICALL Java_HMI_1BackE_getCyclePercent(JNIEnv* env, jobject obj) {
    // Return type is jdouble as per the header
    return static_cast<jdouble>(cyclePercent);
}

JNIEXPORT void JNICALL Java_HMI_1BackE_setCyclePercent(JNIEnv* env, jobject obj, jint percent) {
    cyclePercent = percent; 
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRideRunning(JNIEnv *env, jobject obj) {
    cout << "isRideRunning called" << endl;  
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRow1Locked(JNIEnv *env, jobject obj) {
    cout << "isRow1Locked called" << endl;  
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRow2Locked(JNIEnv *env, jobject obj) {
    cout << "isRow2Locked called" << endl; 
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isReadyToRun(JNIEnv *env, jobject obj) {
    cout << "isReadyToRun called" << endl; 
    return JNI_TRUE; 
}

JNIEXPORT jstring JNICALL Java_HMI_1BackE_getErrorMessage(JNIEnv *env, jobject obj) {
    return env->NewStringUTF("Received and processed error message");
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_lockRestraints(JNIEnv *env, jobject obj) {
   //  cout << "lockRestraints called" << endl; 
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_unlockRestraints(JNIEnv *env, jobject obj) {
   //  cout << "unlockRestraints called" << endl; 
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationGondolaClockwise(JNIEnv *env, jobject obj) {
    cout << "isRotationGondolaClockwise called" << endl;  
    return JNI_TRUE; 
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationGondolaCounterClockwise(JNIEnv *env, jobject obj) {
    cout << "isRotationGondolaCounterClockwise called" << endl;  
    return JNI_TRUE; 
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationArmClockwise(JNIEnv *env, jobject obj) {
    cout << "isRotationArmClockwise called" << endl;  
    return JNI_TRUE; 
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationArmCounterClockwise(JNIEnv *env, jobject obj) {
    cout << "isRotationArmCounterClockwise called" << endl;  
    return JNI_TRUE; 
}
