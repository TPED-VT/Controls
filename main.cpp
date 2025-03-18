// #include "include/wiringPi.h"
// Put the wiringPi I2C library for use in here
#include <iostream>
#include "Motor_Control/MotorControl.h"

#define DIR_PIN 1
#define STEP_PIN 2

#define	LED	0

// TODO: Encoder here

int main(){
    MotorControl motor(DIR_PIN, STEP_PIN);
    bool running = true;
    char input;
    while(running){
        if(_kbhit()){
            input = _getch();
            if(input == 'd')
                motor.rotate(CLOCKWISE);
            if(input == 'a')
                motor.rotate(COUNTER_CLOCKWISE);
        }
    }
    return 0;
}