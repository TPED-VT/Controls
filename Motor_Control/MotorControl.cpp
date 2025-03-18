#include "MotorControl.h"


MotorControl::MotorControl(int dirPin, int stepPin){
    wiringPiSetup();
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, LOW);
}

void MotorControl::setSpeed(float newSpeed) {
    speed = newSpeed;
}

void MotorControl::setDirection(bool d) {
    dir = d;
}

void MotorControl::moveWithSCurve(float max_velocity, float max_acceleration, int total_steps) {
    double total_time = (2.0 * max_velocity) / max_acceleration + (float)total_steps / max_velocity;
    auto start_time = std::chrono::high_resolution_clock::now();
    int steps_moved = 0;

    digitalWrite(dir, HIGH);  // Set direction

    while (steps_moved < total_steps) {
        auto elapsed_time = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - start_time).count();
        long step_delay = (long)stepDelay(elapsed_time, total_time, max_velocity);

        if (steps_moved < total_steps) {
            digitalWrite(stepPin, HIGH);
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            digitalWrite(stepPin, LOW);
            std::this_thread::sleep_for(std::chrono::microseconds(step_delay));
            steps_moved++;
        }
    }
}
// Function to compute step delay based on S-curve motion profile
double MotorControl::stepDelay(float time, double total_time, float max_velocity) {
    double t = time / total_time; // Normalize
    double velocity;

    // S-curve velocity profile
    if (t < 0.25) {
        velocity = max_velocity * (4*pow(t,3));  // Cubic acceleration
    } else if (t < 0.5) {
        velocity = max_velocity * (1 - pow(-1*(t - 0.25), 3)); // Transition
    } else if (t < 0.75) {
        velocity = max_velocity; // Constant velocity phase
    } else {
        velocity = max_velocity * pow(1 - (t - 0.75) * 4, 3);  // Cubic deceleration
    }

    return (velocity > 0) ? (long)(1e6 / velocity) : 1e6; // Convert to microseconds
}

void MotorControl::rotate(bool direction){
    digitalWrite(dirPin, direction);
    while(_kbhit()){  // Check for a key being pressed
        digitalWrite(stepPin, HIGH);
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        digitalWrite(stepPin, LOW);
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }
}

void MotorControl::toPos(float degree) {
}

float MotorControl::getSpeed(void) {
    return speed;
}

bool MotorControl::getDirection(void) {

    return dir;
}