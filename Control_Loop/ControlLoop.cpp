#include "ControlLoop.h"

ControlLoop::ControlLoop(int dir, int step, int ms1, int ms2, int sleep, int endstop){
    gondola = new MotorControl(dir, step);
    arm = new MotorControl(dir, step);
    state = ControlState::OFF;
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