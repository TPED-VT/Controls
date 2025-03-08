#ifndef CONTROL_LOOP_H
#define CONTROL_LOOP_H

#include "../Motor_Control/MotorControl.h"

// State Definitions
enum class ControlState{
    OFF=0,
    INIT,
    AUTO,
    MAINT
};

class ControlLoop{
public:
    ControlLoop();
    ~ControlLoop();
    
    void handleOff();
    void handleInit();
    void handleAuto();
    void handleMaint();
    
private:
    ControlState state; // Current state of the ride
    MotorControl* arm;
    MotorControl* gondola;

};


#endif