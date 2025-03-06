#ifndef WIRING_PI_WINDOWS_H
#define WIRING_PI_WINDOWS_H


#ifdef PLATFORM_LINUX
    #include <wiringPi.h>
#else
    // Mock functions from wiringPi.h
    // Add any necessary functions here with the proper look as the real function
    inline void pinMode(int pin, int mode) {}
    inline void digitalWrite(int pin, int value) {}
    inline int wiringPiSetup(void) {return 1;}
    inline int digitalRead(int pin) { return 0; }
    inline void delay(unsigned int howLong) {}
#endif

#endif