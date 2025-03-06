#include "EasyStepper.h"
#include "wiringPi.h"

#define true 1
#define false 0

EasyStepper::EasyStepper(int dir, int step, int ms1, int ms2, int sleep) {
	init(dir, step, ms1, ms2, sleep, -1);
}

EasyStepper::EasyStepper(int dir, int step, int ms1, int ms2, int sleep, int endstop) {
	init(dir, step, ms1, ms2, sleep, endstop);
}

void EasyStepper::init(int dir, int step, int ms1, int ms2, int sleep, int endstop) {
	pinMode(dir, OUTPUT);
	pinMode(step, OUTPUT);
	pinMode(ms1, OUTPUT);
	pinMode(ms2, OUTPUT);
	pinMode(sleep, OUTPUT);
	
	_easingDivider = 3;
	
	mDir = dir;
	mStep = step;
	mMs1 = ms1;
	mMs2 = ms2;
	mSleep = sleep;
	mEndStop = endstop;
	
	flippedMotor = 0;
}

void EasyStepper::setMaxSpeed(int maxSpeed) {
	_maxSpeed = maxSpeed;
}

void EasyStepper::setEasingAmount(int divider) {
	_easingDivider = divider;
}

void EasyStepper::sleep(int state) {
	digitalWrite(mSleep, state);
}

void EasyStepper::setMicrostepping(int fraction) {
	MS1_MODE(fraction);
	MS2_MODE(fraction);
}

void EasyStepper::step(int numOfSteps) {
	switch(flippedMotor) {
		case 0:
			if(numOfSteps < 0) {
				digitalWrite(mDir, HIGH);
				flippedDir = true;
				stepsRemaining = -numOfSteps;
			}
			else {
				digitalWrite(mDir, LOW);
				flippedDir = false;
				stepsRemaining = numOfSteps;
			}
			break;
		case 1:
			if(numOfSteps < 0) {
				digitalWrite(mDir, LOW);
				flippedDir = true;
				stepsRemaining = -numOfSteps;
			}
			else {
				digitalWrite(mDir, HIGH);
				flippedDir = false;
				stepsRemaining = numOfSteps;
			}
			break;
	}
}

void EasyStepper::flipDirection() {
	flippedMotor = 1;
}

void EasyStepper::stepTo(int pos) {
	int steps = (currentPos*-1) + pos;
	step(steps);
}

void EasyStepper::update() {
	if((unsigned long)(micros() - previous_timer) >= 500) {
		previous_timer = micros();
		
		// Run motor if there are steps to perform
		if(stepsRemaining > 0) {
			if((timer+1) % _maxSpeed == 0) {
				digitalWrite(mStep, LOW);
				digitalWrite(mStep, HIGH);
				if(flippedDir) {
					currentPos--;
				}
				else {
					currentPos++;
				}
				stepsRemaining--;
			}
		}
		timer = (timer + 1) % 100;
	}
}

void EasyStepper::setPosition(int pos) {
	currentPos = pos;
}

void EasyStepper::stepWithEasing(int numOfSteps, int type) {
	switch(type) {
		// Sine wave
		case 0:
			if((unsigned long)(micros() - previous_timer) >= 500) {
				previous_timer = micros();
		
				// Run motor
				if(stepsRemaining > 0) {
					// Is it time to microstep yet?
					if(stepsRemaining == numOfSteps/_easingDivider && microStepping == 0) {
						stepsRemaining *= 8;
						digitalWrite(mMs1, MS1_MODE(8));
						digitalWrite(mMs2, MS2_MODE(8));
						microStepping = 1;
					}
					else if(stepsRemaining > numOfSteps/_easingDivider) {
						if((timer+1) % _maxSpeed == 0) {
							digitalWrite(mStep, LOW);
							digitalWrite(mStep, HIGH);
							stepsRemaining--;
						}
					}
					else {
						if((timer+1) % (currentSpeed/8) == 0) {
							digitalWrite(mStep, LOW);
							digitalWrite(mStep, HIGH);
							stepsRemaining--;
							currentSpeed = map(stepsRemaining, numOfSteps/_easingDivider, 1, _maxSpeed, _minSpeed);
						}
					}
				}
			}
			break;
	}
}

int EasyStepper::readEndStop() {
	return analogRead(mEndStop);
}

int EasyStepper::isMoving() {
	if(stepsRemaining != 0) {
		return true;
	}
	else {
		return false;
	}
}

int EasyStepper::MS1_MODE(int stepMode) {
	switch(stepMode) {
		case 1:
			stepMode = 0;
			break;
		case 2:
			stepMode = 1;
			break;
		case 4:
			stepMode = 0;
			break;
		case 8:
			stepMode = 1;
			break;
	}
	return stepMode;
}

int EasyStepper::MS2_MODE(int stepMode) {
	switch(stepMode) {
		case 1:
			stepMode = 0;
			break;
		case 2:
			stepMode = 0;
			break;
		case 4:
			stepMode = 1;
			break;
		case 8:
			stepMode = 1;
			break;
	}
	return stepMode;
}