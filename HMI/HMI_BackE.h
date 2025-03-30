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
 * Method:    setCyclePercent
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_setCyclePercent
  (JNIEnv *, jobject, jint);

/*
 * Class:     HMI_BackE
 * Method:    getPosition
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_getPosition
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    setState
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_setState
  (JNIEnv *, jobject, jint);

/*
 * Class:     HMI_BackE
 * Method:    getCurrentState
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_getCurrentState
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    getNextSector
 * Signature: (JJZZZ)V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_getNextSector
  (JNIEnv *, jobject, jlong, jlong, jboolean, jboolean, jboolean);

/*
 * Class:     HMI_BackE
 * Method:    getCurrentSector
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_getCurrentSector
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     HMI_BackE
 * Method:    isRideRunning
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRideRunning
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
 * Method:    getErrorMessage
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_getErrorMessage
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    lockRestraints
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_lockRestraints
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    unlockRestraints
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_unlockRestraints
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isRotationGondolaClockwise
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationGondolaClockwise
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isRotationGondolaCounterClockwise
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationGondolaCounterClockwise
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isRotationArmClockwise
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationArmClockwise
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isRotationArmCounterClockwise
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRotationArmCounterClockwise
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
