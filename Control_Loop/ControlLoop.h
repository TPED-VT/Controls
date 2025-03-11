#ifndef CONTROL_LOOP_H
#define CONTROL_LOOP_H

#include "../Motor_Control/MotorControl.h"

#define MASK_NONE 0 // No errors
#define MASK_SEAT_FAULT_1 1<<0
#define MASK_SEAT_FAULT_2 1<<1
#define MASK_HOMING_FAULT 1<<2
#define MASK_MOTOR_1_NOT_RESPONDING_FAULT 1<<3
#define MASK_MOTOR_2_NOT_RESPONDING_FAULT 1<<4
#define MASK_MOTOR_1_POSITION_FAULT 1<<5
#define MASK_MOTOR_2_POSITION_FAULT 1<<6
#define MASK_DRAGON_FAULT 1<<7
#define MASK_POWER_CONNECTION_FAULT 1<<8
#define MASK_EMERGENCY_STOP 1<<9

// State Definitions
enum class ControlState{
    OFF=0,
    INIT,
    AUTO,
    MAINT
};

// Errors should be a number and then the HMI will handle with the actual error itself
enum class RideError{
    NONE = 0, // No errors
    SEAT_FAULT_1 = 1<<0,
    SEAT_FAULT_2= 1<<1,
    HOMING_FAULT= 1<<2,
    MOTOR_1_NOT_RESPONDING_FAULT= 1<<3,
    MOTOR_2_NOT_RESPONDING_FAULT= 1<<4,
    MOTOR_1_POSITION_FAULT= 1<<5,
    MOTOR_2_POSITION_FAULT= 1<<6,
    DRAGON_FAULT= 1<<7,
    POWER_CONNECTION_FAULT= 1<<8,
    EMERGENCY_STOP= 1<<9,
};
// Be able to control the lock and unlock bit (only in maintainence)
// Track when the restraints are both closed

class ControlLoop{
public:
    ControlLoop();
    ~ControlLoop();
    
    void handleOff();

    // Init and auto will combine
    void handleInit();  // Move both motors to home here
    void handleAuto();

    
    void handleMaint();
    
private:
    ControlState state; // Current state of the ride
    MotorControl* arm;
    MotorControl* gondola;

};


#endif