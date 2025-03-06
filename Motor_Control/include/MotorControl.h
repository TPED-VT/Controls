#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#define CLOCKWISE 1
#define COUNTER_CLOCKWISE 2

class MotorControl{
public:

    /**
     * @brief Default constructor of the MotorControl class. This will be
     * used for each motor in the system.
     */
    MotorControl(void);

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
    void setDirection(bool dir);

    bool dir = CLOCKWISE;   // Direction the motor is moving in (default is clockwise)
    float speed;    // Speed of the motor
    float curPos;   // Current position of the motors
    float targPos;  // Target position of the motors
    float error;     // Acceptable range that the angle can be within to be valid
};



#endif