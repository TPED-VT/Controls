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

// State machines

JNIEXPORT void JNICALL Java_HMI_1BackE_getNextState(JNIEnv *env, jobject obj, jint currentState, jint RestraintCheck, jint isHomed, jint ArmTest) {
    State state = (State) currentState;

    getNextState(&state, (int) RestraintCheck, (int) isHomed, (int) ArmTest);

}

// JNIEXPORT void JNICALL Java_HMI_1BackE_setState(JNIEnv *env, jobject obj, jint state) {
//     currentState = static_cast<State>(state);
// }

// JNIEXPORT jint JNICALL Java_HMI_1BackE_getCurrentState(JNIEnv *env, jobject obj) {
//     // Return type is jint as per the header
//     return static_cast<jint>(currentState);
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

JNIEXPORT jstring JNICALL Java_HMI_1BackE_getErrorMessage(JNIEnv *env, jobject obj, jint RestraintCheck, jint isHomed, jint ArmTest) {
   cout << "getErrorMessage called" << endl; 

   string result = getErrorMessage((int) RestraintCheck, (int) isHomed, (int) ArmTest);
   return env->NewStringUTF(result.c_str());
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_lockRestraints(JNIEnv *env, jobject obj) {
   //  cout << "lockRestraints called" << endl; 
    return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_unlockRestraints(JNIEnv *env, jobject obj) {
   //  cout << "unlockRestraints called" << endl; 
    return JNI_TRUE;
}

JNIEXPORT jstring JNICALL Java_HMI_1BackE_isReadyToRunMessage(JNIEnv *env, jobject obj, jint RestraintCheck, jint isHomed, jint ArmTest) {
   string result = isReadyToRunMessage((int) RestraintCheck, (int) isHomed, (int) ArmTest);
   cout << result << endl; 

   return env->NewStringUTF(result.c_str());
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
