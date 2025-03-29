// Save as "HelloJNI.c"
#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include "HMI_Back.h" // Generated header file from HMI_BackEnd.h
 
JNIEXPORT void JNICALL Java_HMI_Back_getCyclePercent(JNIEnv *env, jobject thisObj) {
   printf("Hello World!\n");
   return;
}