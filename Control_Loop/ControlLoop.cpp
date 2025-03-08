#include "ControlLoop.h"
int dir;
int step;
int ms1;
int ms2;
int sleep;
int endstop;
ControlLoop::ControlLoop(){
    gondola = new MotorControl(dir, step, ms1, ms2, sleep);
    arm = new MotorControl(dir, step, ms1, ms2, sleep, endstop);
}

ControlLoop::~ControlLoop(){
    delete gondola;
    delete arm;
}
void ControlLoop::handleOff() {
}
void ControlLoop::handleInit() {
}
void ControlLoop::handleAuto() {

    // Ride Phase 1

    // Ride Phase 2

    // Ride Phase 3 

    //...
}
void ControlLoop::handleMaint() {
}