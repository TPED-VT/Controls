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
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_getPosition
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    getNextState
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_getNextState
  (JNIEnv *, jobject, jint, jint, jint, jint);

/*
 * Class:     HMI_BackE
 * Method:    getErrorMessage
 * Signature: (III)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_getErrorMessage__III
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     HMI_BackE
 * Method:    logErrorMessage
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_HMI_1BackE_logErrorMessage
  (JNIEnv *, jobject, jstring);

/*
 * Class:     HMI_BackE
 * Method:    getErrorMessage
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_getErrorMessage__
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isReadyToRunMessage
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_isReadyToRunMessage__
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isReadyToRun
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isReadyToRun__
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
 * Method:    isRow1Locked
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_isRow1Locked__
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    isRow2Locked
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_isRow2Locked__
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
 * Method:    lockRestraints
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_lockRestraints
  (JNIEnv *, jobject);

/*
 * Class:     HMI_BackE
 * Method:    restraintCheck
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_restraintCheck
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     HMI_BackE
 * Method:    isRow1Locked
 * Signature: (Z)I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_isRow1Locked__Z
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     HMI_BackE
 * Method:    isRow2Locked
 * Signature: (Z)I
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_isRow2Locked__Z
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     HMI_BackE
 * Method:    isReadyToRun
 * Signature: (III)Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isReadyToRun__III
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     HMI_BackE
 * Method:    isReadyToRunMessage
 * Signature: (III)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_HMI_1BackE_isReadyToRunMessage__III
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     HMI_BackE
 * Method:    isRideRunning
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRideRunning
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
