
#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include "HMI_BackE.h" // Generated header file from HMI_BackEnd.h
#include <iostream>
#include "C:/Users/ricar/Documents/TPED/Controls/Control_Loop/functions.h" // needs to change
#include <ostream>
#include <thread>
#include <chrono>


using namespace std; 

State currentState = State::kInit;
Sector currentSector = Sector::kSector1;
bool test1 = false; 
bool test2 = false; 
bool test3 = false; 


int cyclePercent = 0; // dummy value testing

void readCyclePercent() {
   for (int i = 0; i < 1000; i++) {
      cyclePercent++;
   }
   cout << cyclePercent << endl;
   this_thread::sleep_for(chrono::seconds(5));
}


JNIEXPORT jint JNICALL Java_HMI_Backe_getPosition(JNIEnv *env, jobject obj) {
   return 1; 
}

// state and sectors machines

JNIEXPORT void JNICALL Java_HMI_1BackE_setState(JNIEnv *env, jobject obj, jint state) {
   currentState = static_cast<State>(state);
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_getCurrentState(JNIEnv *env, jobject obj) { // should it be as KeyAsButton
   return static_cast<jint>(currentState);
} 


// sector machines

JNIEXPORT jint JNICALL Java_HMI_1BackE_getNextState(JNIEnv *env, jobject obj) {
   getNextState(&currentState, &currentSector, test1, test2, test3);
   return static_cast<jlong>(currentState);
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_getCurrentSector(JNIEnv *env, jobject obj) {
   getCurrentSector(&currentState, &currentSector);
   return static_cast<jlong>(currentSector);
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_setNextSector(JNIEnv *env, jobject obj, jint sector) {
   currentSector = static_cast<Sector>(sector);
   return static_cast<jlong>(currentSector);
}


// RIDE FUNCTIONS!!!

JNIEXPORT void JNICALL Java_HMI_1BackE_startCyclePercent(JNIEnv* env, jobject obj) {
   thread cycleThread(readCyclePercent);
   cycleThread.detach(); // LOOKING AT REFERENCES DOES NOT WORK !!!!!

}

JNIEXPORT jint JNICALL Java_HMI_1BackE_getCyclePercent(JNIEnv* env, jobject obj) {
   return cyclePercent;
}

JNIEXPORT void JNICALL Java_HM_BackE_setCyclePercent(JNIEnv* env, jobject obj, jint percent) {
   cyclePercent = percent; 
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRideRunning(JNIEnv *env, jobject thisObj, jboolean running) {
   cout << "isRideRunning is " << running << endl;  
   return JNI_TRUE;
 }
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRow1Locked(JNIEnv *env, jobject thisObjm, jboolean row1locked) {
    cout << "isRow1Locked " << row1locked << endl;  
    return JNI_TRUE;
 }

 JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRow2Locked(JNIEnv *env, jobject thisObj, jboolean row2locked) {
    cout << "isRow2Lock " << row2locked << endl; 
    return JNI_TRUE;
 }
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isReadyToRun(JNIEnv *env, jobject thisObj, jboolean ready) {
    cout << "isReadyToRun " << ready << endl; 
    return JNI_TRUE; 
 }
JNIEXPORT jstring JNICALL Java_HMI_1BackE_getErrorMessage(JNIEnv *env, jobject thisObj, jstring error) {
   return env->NewStringUTF("Received and processed error message"); // not sure on if this is correct
 }

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_lockRestraints(JNIEnv *env, jobject thisObj, jboolean lockedRestraints) {
   cout << "lockRestraints " << lockedRestraints << endl; 
   return JNI_TRUE;
 }

 JNIEXPORT jboolean JNICALL Java_HMI_1BackE_unlockRestraints(JNIEnv *env, jobject thisObj, jboolean unlockRestraints) {
   cout << "unlockRestraints " << unlockRestraints << endl; 
   return JNI_TRUE;
 }

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationGondolaClockwise(JNIEnv *env, jobject thisObj, jboolean GondolaCheck1) {
   cout << "isRotationGondolaClockwise " << GondolaCheck1 << endl;  
   return JNI_TRUE; 
 }

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationGondolaCounterClockwise(JNIEnv *env, jobject thisObj, jboolean GondolaCheck2) {
   cout << "isRotationGondolaClockwise " << GondolaCheck2 << endl;  
   return JNI_TRUE; 
 }

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationArmClockWise(JNIEnv *env, jobject thisObj, jboolean ArmCheck1) {
   cout << "isRotationArmClockwise " << ArmCheck1 << endl;  
   return JNI_TRUE; 
 }

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationArmCounterClockWise(JNIEnv *env, jobject thisObj, jboolean ArmCheck2) {
   cout << "isRotationArmCounterClockwise " << ArmCheck2 << endl;  
   return JNI_TRUE; 
 }



