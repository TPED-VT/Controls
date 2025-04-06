/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class HMI_BackE */

#ifndef _Included_HMI_BackE
#define _Included_HMI_BackE
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     HMI_BackE
 * Method:    getCyclePercent
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_HMI_1BackE_getCyclePercent
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    startCyclePercent
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_startCyclePercent
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    getCycleCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_getCycleCount
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    setCyclePercent
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_setCyclePercent
  (JNIEnv *, jobject, jint);

/*
 * Class:     HMI_BackE
 * Method:    getPosition
 * Signature: ()[F
 */
JNIEXPORT jfloatArray JNICALL Java_HMI_1BackE_getPosition
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    getNextState
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_getNextState
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    setState
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_setState
  (JNIEnv *, jobject, jint);

/*
 * Class:     HMI_BackE
 * Method:    getCurrentState
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_getCurrentState
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    getErrorMessage
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_getErrorMessage
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    getStatusMessage
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_getStatusMessage
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    getMaintenanceError
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_getMaintenanceError
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    getMaintenanceMessage
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_getMaintenanceMessage
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    getTestStatusMessage
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_getTestStatusMessage
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    setUpGPIO
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_setUpGPIO
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    eStopPressed
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_eStopPressed
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    performRestraintCheck
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_performRestraintCheck
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    unlockRestraints
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_unlockRestraints
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    lockRestraints
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_lockRestraints
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    restraintCheck
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_restraintCheck
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isRow1Locked
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRow1Locked
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isRow2Locked
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRow2Locked
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isReadyToRun
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isReadyToRun
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isReadyToRunMessage
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_isReadyToRunMessage
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isRideRunning
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRideRunning
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    dispatch
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_dispatch
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    stop
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_stop
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    homeArm
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_homeArm
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    homeGondola
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_homeGondola
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    getCurrentTest
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_getCurrentTest
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    setCurrentTest
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_setCurrentTest
  (JNIEnv *, jobject, jint);

/*
 * Class:     HMI_BackE
 * Method:    statusMessage
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_statusMessage
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    maintenanceSelection
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_maintenanceSelection
  (JNIEnv *, jobject, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
