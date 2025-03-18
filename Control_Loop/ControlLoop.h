#ifndef CONTROL_LOOP_H
#define CONTROL_LOOP_H

#include "../Motor_Control/MotorControl.h"

#define NONE_MASK 0 // No errors
#define SEAT_FAULT_1_MASK 1<<0
#define SEAT_FAULT_2_MASK 1<<1
#define HOMING_FAULT_MASK 1<<2
#define MOTOR_1_NOT_RESPONDING_FAULT_MASK 1<<3
#define MOTOR_2_NOT_RESPONDING_FAULT_MASK 1<<4
#define MOTOR_1_POSITION_FAULT_MASK 1<<5
#define MOTOR_2_POSITION_FAULT_MASK 1<<6
#define DRAGON_FAULT_MASK 1<<7
#define POWER_CONNECTION_FAULT_MASK 1<<8
#define EMERGENCY_STOP_MASK 1<<9

// State Definitions
enum class ControlState{
    OFF=0,
    INIT,
    AUTO,
    MAINT
};

enum class RideSequenceState{
    OFF=0,
    PHASE_1,
    PHASE_2,
    PHASE_3,
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
    ControlLoop(int dir, int step, int ms1, int ms2, int sleep, int endstop);
    ~ControlLoop();
    
    void handleOff();

    // Init and auto will combine
    void handleInit();  // Move both motors to home here
    void handleAuto();
    void handleMaint();
    
private:
    // Functions used in the states
    bool restraint1Locked();
    bool restraint2Locked();
    RideError beginHome(MotorControl *m);

    size_t checkError();


    // Member Variables
    ControlState state = ControlState::OFF; // Current state of the ride
    RideSequenceState rideSeq = RideSequenceState::OFF;
    MotorControl* arm;
    MotorControl* gondola;
    size_t errorCode = 0;
    bool motor1Home = false;
    bool motor2Home = false;
};


#endif