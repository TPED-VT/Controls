/*
	EasyStepper.h - Library for the EasyStepper motor driver
	for Arduino
	
	www.mikevanis.com
	
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

#ifndef EasyStepper_h
#define EasyStepper_h

#ifdef PLATFORM_LINUX
    #include <EasyStepper.h>
#else

/******************
	Definitions
*******************/

//typedef uint8_t byte;
long map(long x, long in_min, long in_max, long out_min, long out_max) {

	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

  }
class EasyStepper {
public:
	EasyStepper(int dir, int step, int ms1, int ms2, int sleep);
	EasyStepper(int dir, int step, int ms1, int ms2, int sleep, int endstop);
	void setMaxSpeed(int maxSpeed);
	void setEasingAmount(int divider);
	void setMicrostepping(int fraction);
	void sleep(int state);
	void step(int numOfSteps);
	void stepTo(int pos);
	void stepWithEasing(int numOfSteps, int type);
	void update();
	void setPosition(int pos);
	void flipDirection();
	
	int readEndStop();
	int isMoving();

private:
	void init(int dir, int step, int ms1, int ms2, int sleep, int endstop);
	int MS1_MODE(int stepMode);
	int MS2_MODE(int stepMode);
	
	// Timing
	unsigned long previous_timer;
	unsigned long timer;
	
	// Internal pins
	int mDir;
	int mStep;
	int mMs1;
	int mMs2;
	int mSleep;
	int mEndStop;
	
	int numOfSteps;
	int stepsRemaining;
	int antiClockwise;
	int microStepping;
	int _minSpeed;
	int _maxSpeed;
	int currentSpeed;
	int _easingDivider;
	int currentPos;
	int flippedDir;
	int flippedMotor;
};

#endif

#endif