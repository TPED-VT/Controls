#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include "HMI_BackE.h"  // Generated header file from HMI_1BackEnd.h
#include <iostream>
#include "../Control_Loop/functions.h" // needs to change
#include <ostream>
#include <thread>
#include <chrono>

using namespace std; 

double cyclePercent = 0.5; // dummy value testing
double c = 0; 
// Open serial port
int fd;
int dragonSerial;
bool armHomed = false;
bool gondolaHomed = false;

void readCyclePercent() {
    for (int i = 0; i < 1000; i++) {
        cyclePercent++;
    }
    cout << cyclePercent << endl;
    this_thread::sleep_for(chrono::seconds(5));
}

/*
 *  Sets all paramaters needed for the GPIO at runtime
 */
JNIEXPORT jint JNICALL Java_HMI_1BackE_setUpGPIO(JNIEnv *env, jobject obj) {
    
    // Serial
    if(wiringPiSetup() == -1){
        std:cerr << "Wring Pi Fail" << std::endl;
        return -1;
    }

    // Initialize SPI0
    if (wiringPiSPISetup(SPI0_CHANNEL, 500000) < 0) {
        std::cerr << "Error setting up SPI for Gondola" << std::endl;
        return -1;
    }

    // Initialize SPI1
    if (wiringPiSPISetup(SPI1_CHANNEL, 500000) < 0) {
        std::cerr << "Error setting up SPI for Arm" << std::endl;
        return -1;
    }

    fd = serialOpen("/dev/ttyACM0", 9600);
    dragonSerial = serialOpen("/dev/ttyACM1", 9600);

    // Set E-Stop paramaters
    pinMode(ESTOP_IN, INPUT);
    pinMode(ESTOP_SOURCE, OUTPUT);
    digitalWrite(ESTOP_SOURCE, HIGH);

    return 1;
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_eStopPressed(JNIEnv *env, jobject obj) {
    // cout << "eStopPressed called: " << !digitalRead(ESTOP_IN) << endl;  
    return !digitalRead(ESTOP_IN);
}


// STATE HANDLING 

JNIEXPORT void JNICALL Java_HMI_1BackE_getNextState(JNIEnv *env, jobject obj) {
    // cout << "getNextState is called" << endl; 
    getNextState();
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_getCurrentState(JNIEnv *env, jobject obj) {
    // cout << "getCurrentState called" << endl;
    return static_cast<jint>(getCurrentState());
  
}


// RIDE CONTROL 

JNIEXPORT jint JNICALL Java_HMI_1BackE_start(JNIEnv *env, jobject obj) {
    // cout << "start called" << endl;
    return start();
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_stop(JNIEnv *env, jobject obj) {
    for(int i = 0; i < SERIAL_ITERATION; i++){
        serialPuts(fd, "<0,0,0,0>"); // Stop the ride immediately
        serialPutchar(dragonSerial, 's');
    }
    return stop();
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_homeArm(JNIEnv *env, jobject obj) {
    uint16_t top = 180; 
    bool dir = getPosition(1) > top;
    uint16_t pos = getPosition(1);

    pos = getPosition(1);
            if (dir)
                serialPuts(fd, "<0,0,10,0>");
            else
                serialPuts(fd, "<0,0,10,1>");
    
        while (!(pos <= 2 || pos >= 358)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
        }
    }

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_maintArmCheck(JNIEnv *env, jobject obj) {
        uint16_t top = 180; 
        bool dir = getPosition(1) > top;
        uint16_t pos = getPosition(1);

        pos = getPosition(1);
            if (dir)
                serialPuts(fd, "<0,0,10,0>");
            else
                serialPuts(fd, "<0,0,10,1>");
    
        while (!(pos <= 2 || pos >= 358)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
        }

    // Stop motor
    for (int i = 0; i < SERIAL_ITERATION; i++) {
        serialPuts(fd, "<0,0,0,0>");
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    armHomed = true;
    return stop();
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_homeGondola(JNIEnv *env, jobject obj) {
    uint16_t top = 180; 
    bool dir = getPosition(2) > top;
    uint16_t pos = getPosition(2);
    cout << "Current Pos: " << pos << endl;
    while (!(pos <= 2 || pos >= 358)) {
        pos = getPosition(2);
        if (dir)
            serialPuts(fd, "<0,0,10,0>");
        else
            serialPuts(fd, "<0,0,10,1>");

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        cout << "Current Pos: " << pos << endl;
    }

    // Stop motor
    for (int i = 0; i < SERIAL_ITERATION; i++) {
        serialPuts(fd, "<0,0,0,0>");
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    gondolaHomed = true;
    return stop();
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_maintenanceSelection(JNIEnv *env, jobject obj, jint access, jint test) {
    int result = MaintenanceSelection((int)access, (int)test);
    return result; 
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_setState(JNIEnv *env, jobject obj, jint state) {
    return setState(state);
}

// RESTRAINT CONTROL 

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRow1Locked(JNIEnv *env, jobject obj) {
    // cout << "isRow1Locked called" << endl;
    if (isRow1Locked() == PASS) {
        return true; 
    } else {
        return false;
    }
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRow2Locked(JNIEnv *env, jobject obj) {
    // cout << "isRow2Locked called" << endl;
    if (isRow2Locked() == PASS) {
        return true; 
    } else {
        return false;
    }
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_lockRestraints(JNIEnv *env, jobject obj) {
    // cout << "lockRestraints called" << endl;
    if (lockRestraints() == PASS) {
        return true; 
    } else {
        return false;
    }
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_unlockRestraints(JNIEnv *env, jobject obj) {
    // cout << "unlockRestraints called" << endl;
    if (unlockRestraints() == PASS) {
        return true; 
    } else {
        return false;
    }
}

JNIEXPORT jint JNICALL Java_HMI_1BackE_performRestraintCheck(JNIEnv *env, jobject obj) {
    // cout << "performRestraintCheck called" << endl;
    return performRestraintCheck();
}

// BACK END 

JNIEXPORT jfloatArray JNICALL Java_HMI_1BackE_getPosition(JNIEnv *env, jobject obj) {
    // Read encoder positions
    uint16_t pos1 = getPosition(1);
    // uint16_t pos2 = getPosition(CS2_PIN);
    // Return an array directly from the JNI function (instead of creating a new array)
    jfloat result[2] = {pos1, 0};
    
    // Create a local reference to the result array and return it
    jfloatArray jResult = env->NewFloatArray(2);
    env->SetFloatArrayRegion(jResult, 0, 2, result);
    
    return jResult;  // Return the result as a JNI float array
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isReadyToRun(JNIEnv *env, jobject obj) {
    // cout << "isReadyToRun called" << endl;
    return isReadyToRun();
}

JNIEXPORT jstring JNICALL Java_HMI_1BackE_isReadyToRunMessage(JNIEnv *env, jobject obj) {
    // cout << "isReadyToRunMessage called" << endl;
    string result = isReadyToRunMessage();
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jboolean JNICALL Java_HMI_1BackE_isRideRunning(JNIEnv *env, jobject obj) {
    // cout << "isRideRunning called" << endl; 
    return JNI_TRUE; 
}


// ERROR HANDLING 

JNIEXPORT jstring JNICALL Java_HMI_1BackE_getErrorMessage(JNIEnv *env, jobject obj) {
    // cout << "getErrorMessage called" << endl;
    string result = getErrorMessage();
    return env->NewStringUTF(result.c_str());

}

JNIEXPORT jstring JNICALL Java_HMI_1BackE_getstatusMessage(JNIEnv* env, jobject obj) {
    // cout << "getStatusMessage called" << endl;
    string result = "sTRING";
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL Java_HMI_1BackE_getMaintenanceError(JNIEnv* env, jobject obj) {
    // cout << "getMaintenanceError called" << endl;
    string result = getMaintenanceError();
    return env->NewStringUTF(result.c_str());
}

JNIEXPORT jstring JNICALL Java_HMI_1BackE_getTestStatusMessage(JNIEnv* env, jobject obj) {
    // cout << "getTestStatusMessage called" << endl;
    string result = getTestStatusMessage();
    return env->NewStringUTF(result.c_str());
}





// JNIEXPORT void JNICALL Java_HMI_1BackE_logErrorMessage(JNIEnv *env, jobject obj, jstring message) {
//     cout << "logErrorMessage called" << endl;

//     const char* newMessage = env->GetStringUTFChars(message, nullptr);
//     logErrorMessage(string(newMessage));
//     env->ReleaseStringUTFChars(message, newMessage);
// }


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

JNIEXPORT jint JNICALL Java_HMI_1BackE_getCycleCount(JNIEnv* env, jobject obj) {
    return getCycleCount(); 
}

JNIEXPORT void JNICALL Java_HMI_1BackE_disbatch(JNIEnv* env, jobject obj){
    for(int i = 0; i < SERIAL_ITERATION; i++)
        serialPutchar(fd, 'd');
}

JNIEXPORT void JNICALL Java_HMI_1BackE_reset(JNIEnv* env, jobject obj){
    
    for(int i = 0; i < SERIAL_ITERATION; i++)
        serialPutchar(fd, 'r');
    setState(0);
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