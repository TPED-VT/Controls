#ifndef CONTROL_LOOP_H
#define CONTROL_LOOP_H

// State Definitions
enum class ControlState{
    OFF=0,
    INIT,
    AUTO
};

class ControlLoop{
public:
    ControlLoop();
    
private:
    ControlState state; // Current state of the ride

};


#endif