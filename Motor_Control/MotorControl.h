#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <chrono>
// #include <cmath>
#include <thread>
#include <conio.h>  // For testing only

// Header file includes
#include "../include/wiringPi.h"
// #include "../include/EasyStepper.h"

// Constants
#define CLOCKWISE 1
#define COUNTER_CLOCKWISE 0


#define STEPS_PER_REV 200    // From Datasheet
#define STEPS_PER_DEGREE 1.8 // From Datasheet

/**
 * @brief Wrapper class from the EasyStepper class. Works by simplifying the functions
 * in the Motor Control class use case.
 * @brief Derived from EasyStepper for use in the MotorControl functions
 */
class MotorControl {// : public EasyStepper{
public:

    /**
     * @brief Derived constructor of the MotorControl class from EasyStepper. This will be
     * used for each motor in the system.
     */
    MotorControl(int dirPin, int stepPin);


    /**
     * @brief Sets the target position for the motor to go to.
     * Use the setters to determine the position needed and go there within a certain range.
     * 
     * @param degree The value (in degrees) of the location that the motor will spin to
     * 
     */
    void toPos(float degree);

    /**
     * @brief Gets the motor's speed based on the 'newSpeed' paramater
     * 
     * @return Decimal value of the speed 
     */
    float getSpeed(void);

    /**
     * @brief Gets the direction of the motor
     * 
     * @return Direction that the motor will go
     */
    bool getDirection(void);

    // A testing function to check for movement
    void rotate(bool direction);

private:

    /**
     * @brief Sets the motor's speed based on the 'newSpeed' paramater
     * 
     * @param newSpeed Decimal value of the speed 
     */
    void setSpeed(float newSpeed);

    /**
     * @brief Sets the direction of the motor
     * 
     * @param dir Direction that the motor will go
     * @return void
     */
    void setDirection(bool d);

    /**
     * @brief Creates an S-Curve profile to move in a smooth manor to 
     * a given position
     * 
     * @param angle The angle to put the motor to
     * @param duration How long the movement will take
     * @return void
     */
    void moveWithSCurve(float max_velocity, float max_acceleration, int total_steps);

    double stepDelay(float currentTime, double totalTime, float maxVelo);
    
    bool dir = CLOCKWISE;   // Direction the motor is moving in (default is clockwise)
    float speed;    // Speed of the motor
    float curPos;   // Current position of the motors
    float targPos;  // Target position of the motors
    float error;     // Acceptable range that the angle can be within to be valid
    float home;   // Home position of the motor

    // Pins
    int dirPin;
    int stepPin;
};



#endif