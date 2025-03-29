
#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include "HMI_BackE.h" // Generated header file from HMI_BackEnd.h
#include <iostream>
#include <ostream>
#include <thread>
#include <chrono>


using namespace std; 

int cyclePercent = 0; // dummy value testing

void readCyclePercent() {
   for (int i = 0; i < 1000; i++) {
      cyclePercent++;
   }
   cout << cyclePercent << endl;
   this_thread::sleep_for(chrono::seconds(5));
}

// 

JNIEXPORT void JNICALL Java_HMI_BackE_startCyclePercent(JNIEnv* env, jobject obj) {
   thread cycleThread(readCyclePercent);
   cycleThread.detach(); // LOOKING AT REFERENCES DOES NOT WORK !!!!!

}

JNIEXPORT jint JNICALL Java_HMI_BackE_getCyclePercent(JNIEnv* env, jobject obj) {
   return cyclePercent;
}

JNIEXPORT void JNICALL Java_HM_BackE_setCyclePercent(JNIEnv* env, jobject obj, jint percent) {
   cyclePercent = percent; 
}

JNIEXPORT jboolean JNICALL Java_HMI_BackE_isRideRunning(JNIEnv *env, jobject thisObj, jboolean running) {
   cout << "isRideRunning is " << running << endl;  
   return JNI_TRUE;
 }
JNIEXPORT jboolean JNICALL Java_HMI_BackE_isRow1Locked(JNIEnv *env, jobject thisObjm, jboolean row1locked) {
    cout << "isRow1Locked " << row1locked << endl;  
    return JNI_TRUE;
 }

 JNIEXPORT jboolean JNICALL Java_HMI_BackE_isRow2Locked(JNIEnv *env, jobject thisObj, jboolean row2locked) {
    cout << "isRow2Lock " << row2locked << endl; 
    return JNI_TRUE;
 }
JNIEXPORT jboolean JNICALL Java_HMI_BackE_isReadyToRun(JNIEnv *env, jobject thisObj, jboolean ready) {
    cout << "isReadyToRun " << ready << endl; 
    return JNI_TRUE; 
 }
JNIEXPORT jstring JNICALL Java_HMI_BackE_getErrorMessage(JNIEnv *env, jobject thisObj, jstring error) {
   return env->NewStringUTF("Received and processed error message"); // not sure on if this is correct
 }

JNIEXPORT jboolean JNICALL Java_HMI_BackE_lockRestraints(JNIEnv *env, jobject thisObj, jboolean lockedRestraints) {
   cout << "lockRestraints " << lockedRestraints << endl; 
   return JNI_TRUE;
 }

 JNIEXPORT jboolean JNICALL Java_HMI_BackE_unlockRestraints(JNIEnv *env, jobject thisObj, jboolean unlockRestraints) {
   cout << "unlockRestraints " << unlockRestraints << endl; 
   return JNI_TRUE;
 }

JNIEXPORT jboolean JNICALL Java_HMI_BackE_isRotationGondolaClockwise(JNIEnv *env, jobject thisObj, jboolean GondolaCheck1) {
   cout << "isRotationGondolaClockwise " << GondolaCheck1 << endl;  
   return JNI_TRUE; 
 }

JNIEXPORT jboolean JNICALL Java_HMI_BackE_isRotationGondolaCounterClockwise(JNIEnv *env, jobject thisObj, jboolean GondolaCheck2) {
   cout << "isRotationGondolaClockwise " << GondolaCheck2 << endl;  
   return JNI_TRUE; 
 }

JNIEXPORT jboolean JNICALL Java_HMI_BackE_isRotationArmClockWise(JNIEnv *env, jobject thisObj, jboolean ArmCheck1) {
   cout << "isRotationArmClockwise " << ArmCheck1 << endl;  
   return JNI_TRUE; 
 }

JNIEXPORT jboolean JNICALL Java_HMI_BackE_isRotationArmCounterClockWise(JNIEnv *env, jobject thisObj, jboolean ArmCheck2) {
   cout << "isRotationArmCounterClockwise " << ArmCheck2 << endl;  
   return JNI_TRUE; 
 }

