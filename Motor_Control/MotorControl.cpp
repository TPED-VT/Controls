#include "MotorControl.h"


MotorControl::MotorControl(int dir, int step, int ms1, int ms2, int sleep):EasyStepper(dir, step, ms1, ms2, sleep) {

}

MotorControl::MotorControl(int dir, int step, int ms1, int ms2, int sleep, int endstop):EasyStepper(dir, step, ms1, ms2, sleep, endstop){

}

void MotorControl::setSpeed(float newSpeed) {
}

void MotorControl::setDirection(bool dir) {
}

void MotorControl::moveWithSCurve(float angle, float duration) {
}

void MotorControl::toPos(float degree) {
}

float MotorControl::getSpeed(void) {
    float returnValue;
    return returnValue;
}

bool MotorControl::getDirection(void) {
    bool returnValue;
    return returnValue;
}