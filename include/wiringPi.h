#ifndef WIRING_PI_H
#define WIRING_PI_H


#ifdef PLATFORM_LINUX
    #include <wiringPi.h>
#else

    #define	WPI_MODE_PINS		          0
    #define	WPI_MODE_GPIO		          1
    #define	WPI_MODE_GPIO_SYS	        2  // deprecated since 3.2
    #define	WPI_MODE_PHYS		          3
    #define	WPI_MODE_PIFACE		        4
    #define	WPI_MODE_GPIO_DEVICE_BCM  5  // BCM pin numbers like WPI_MODE_GPIO
    #define	WPI_MODE_GPIO_DEVICE_WPI  6  // WiringPi pin numbers like WPI_MODE_PINS
    #define	WPI_MODE_GPIO_DEVICE_PHYS 7  // Physic pin numbers like WPI_MODE_PHYS
    #define	WPI_MODE_UNINITIALISED -1

    // Pin modes

    #define	INPUT			         0
    #define	OUTPUT			       1
    #define	PWM_OUTPUT		     2
    #define	PWM_MS_OUTPUT	     8
    #define	PWM_BAL_OUTPUT     9
    #define	GPIO_CLOCK		     3
    #define	SOFT_PWM_OUTPUT		 4
    #define	SOFT_TONE_OUTPUT	 5
    #define	PWM_TONE_OUTPUT		 6
    #define	PM_OFF		         7   // to input / release line

    #define	LOW			 0
    #define	HIGH			 1

    // Pull up/down/none

    #define	PUD_OFF			 0
    #define	PUD_DOWN		 1
    #define	PUD_UP			 2

    // PWM

    #define	PWM_MODE_MS		0
    #define	PWM_MODE_BAL		1

    // Interrupt levels

    #define	INT_EDGE_SETUP		0
    #define	INT_EDGE_FALLING	1
    #define	INT_EDGE_RISING		2
    #define	INT_EDGE_BOTH		3

    // Pi model types and version numbers
    //	Intended for the GPIO program Use at your own risk.
    // https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#new-style-revision-codes
    // https://github.com/raspberrypi/documentation/blob/develop/documentation/asciidoc/computers/raspberry-pi/revision-codes.adoc

    #define	PI_MODEL_A		    0
    #define	PI_MODEL_B		    1
    #define	PI_MODEL_AP		    2
    #define	PI_MODEL_BP		    3
    #define	PI_MODEL_2		    4
    #define	PI_ALPHA		      5
    #define	PI_MODEL_CM		    6

    #define	PI_MODEL_3B		    8
    #define	PI_MODEL_ZERO		  9
    #define	PI_MODEL_CM3		 10

    #define	PI_MODEL_ZERO_W	 12
    #define	PI_MODEL_3BP 		 13
    #define	PI_MODEL_3AP 		 14

    #define	PI_MODEL_CM3P 	 16
    #define	PI_MODEL_4B 		 17
    #define	PI_MODEL_ZERO_2W 18
    #define	PI_MODEL_400		 19
    #define	PI_MODEL_CM4		 20
    #define	PI_MODEL_CM4S		 21

    #define	PI_MODEL_5		   23
    #define	PI_MODEL_CM5	   24
    #define	PI_MODEL_500	   25
    #define	PI_MODEL_CM5L	   26

    #define PI_MODELS_MAX    27

    #define	PI_VERSION_1		  0
    #define	PI_VERSION_1_1		1
    #define	PI_VERSION_1_2		2
    #define	PI_VERSION_2		  3

    #define	PI_MAKER_SONY		  0
    #define	PI_MAKER_EGOMAN		1
    #define	PI_MAKER_EMBEST		2
    #define	PI_MAKER_UNKNOWN	3

    #define GPIO_LAYOUT_PI1_REV1 1   //Pi 1 A/B Revision 1, 1.1, CM
    #define GPIO_LAYOUT_DEFAULT  2

    const char *piModelNames    [PI_MODELS_MAX] ;
    const char *piProcessor     [ 5] ;
    const char *piRevisionNames [16] ;
    const char *piMakerNames    [16] ;
    const int   piMemorySize    [ 8]{} ;

    //	Intended for the GPIO program Use at your own risk.

    // Threads

    #define	PI_THREAD(X)	void *X (UNU void *dummy)

    // Failure modes

    #define	WPI_FATAL	(1==1)
    #define	WPI_ALMOST	(1==2)

    struct wiringPiNodeStruct{
        int     pinBase ;
        int     pinMax ;

        int          fd ;	// Node specific
        unsigned int data0 ;	//  ditto
        unsigned int data1 ;	//  ditto
        unsigned int data2 ;	//  ditto
        unsigned int data3 ;	//  ditto

        void   (*pinMode)          (struct wiringPiNodeStruct *node, int pin, int mode) {};
        void   (*pullUpDnControl)  (struct wiringPiNodeStruct *node, int pin, int mode) {};
        int    (*digitalRead)      (struct wiringPiNodeStruct *node, int pin) {};
        //unsigned int    (*digitalRead8)     (struct wiringPiNodeStruct *node, int pin) {};
        void   (*digitalWrite)     (struct wiringPiNodeStruct *node, int pin, int value) {};
        //         void   (*digitalWrite8)    (struct wiringPiNodeStruct *node, int pin, int value) {};
        void   (*pwmWrite)         (struct wiringPiNodeStruct *node, int pin, int value) {};
        int    (*analogRead)       (struct wiringPiNodeStruct *node, int pin) {};
        void   (*analogWrite)      (struct wiringPiNodeStruct *node, int pin, int value) {};

        struct wiringPiNodeStruct *next ;
    };

    struct wiringPiNodeStruct *wiringPiNodes ;


    // Export variables for the hardware pointers

    volatile unsigned int *_wiringPiGpio ;
    volatile unsigned int *_wiringPiPwm ;
    volatile unsigned int *_wiringPiClk ;
    volatile unsigned int *_wiringPiPads ;
    volatile unsigned int *_wiringPiTimer ;
    volatile unsigned int *_wiringPiTimerIrqRaw ;

    // Internal
    void piGpioLayoutOops (const char *why);
    int wiringPiFailure (int fatal, const char *message, ...) ;

    // Core wiringPi functions

    struct wiringPiNodeStruct *wiringPiFindNode (int pin) ;
    struct wiringPiNodeStruct *wiringPiNewNode  (int pinBase, int numPins) ;

    enum WPIPinType {
    WPI_PIN_BCM = 1,
    WPI_PIN_WPI,
    WPI_PIN_PHYS,
    };

    void wiringPiVersion	(int *major, int *minor) {};
    int  wiringPiGlobalMemoryAccess(void){return 0;};                 //Interface V3.3
    int  wiringPiUserLevelAccess (void) {return 0;};
    int  wiringPiSetup       (void) {return 0;};
    int  wiringPiSetupSys    (void) {return 0;};
    int  wiringPiSetupGpio   (void) {return 0;};
    int  wiringPiSetupPhys   (void) {return 0;};
    int  wiringPiSetupPinType (enum WPIPinType pinType){return 0;};   //Interface V3.3
    int  wiringPiSetupGpioDevice(enum WPIPinType pinType){return 0;}; //Interface V3.3


    enum WPIPinAlt {
    WPI_ALT_UNKNOWN = -1,
    WPI_ALT_INPUT = 0,
    WPI_ALT_OUTPUT,
    WPI_ALT5,
    WPI_ALT4,
    WPI_ALT0,
    WPI_ALT1,
    WPI_ALT2,
    WPI_ALT3,
    WPI_ALT6,
    WPI_ALT7,
    WPI_ALT8,
    WPI_ALT9,
    WPI_NONE = 0x1F,  // Pi5 default
    };


    int  wiringPiGpioDeviceGetFd();               //Interface V3.3
    void pinModeAlt          (int pin, int mode) {};
    enum WPIPinAlt getPinModeAlt       (int pin) {return WPI_ALT0;};  // Interface V3.5, same as getAlt but wie enum
    void pinMode             (int pin, int mode) {};
    void pullUpDnControl     (int pin, int pud) {};
    int  digitalRead         (int pin) {return 0;};
    void digitalWrite        (int pin, int value) {};
    unsigned int  digitalRead8        (int pin) {return 0;};
    void digitalWrite8       (int pin, int value) {};
    void pwmWrite            (int pin, int value) {};
    int  analogRead          (int pin) {return 0;};
    void analogWrite         (int pin, int value) {};

    // PiFace specifics
    //	(Deprecated)

    int  wiringPiSetupPiFace (void) {return 0;};
    int  wiringPiSetupPiFaceForGpioProg (void) {return 0;};	// Don't use this - for gpio program only

    // On-Board Raspberry Pi hardware specific stuff

    int  piGpioLayout        (void) {return 0;};
    int  piBoardRev          (void) {return 0;};	// Deprecated, but does the same as piGpioLayout
    void piBoardId           (int *model, int *rev, int *mem, int *maker, int *overVolted) {};
    int  piBoard40Pin        (void) {return 0;};                   // Interface V3.7
    int  piRP1Model          (void) {return 0;};                   // Interface V3.14
    int  wpiPinToGpio        (int wpiPin) {return 0;};
    int  physPinToGpio       (int physPin) {return 0;};
    void setPadDrive         (int group, int value) {};
    void setPadDrivePin      (int pin, int value){};     // Interface V3.0
    int  getAlt              (int pin) {return 0;};
    void pwmToneWrite        (int pin, int freq) {};
    void pwmSetMode          (int mode) {};
    void pwmSetRange         (unsigned int range) {};
    void pwmSetClock         (int divisor) {};
    void gpioClockSet        (int pin, int freq) {};
    unsigned int  digitalReadByte     (void) {return 0;};
    unsigned int  digitalReadByte2    (void) {return 0;};
    void digitalWriteByte    (int value) {};
    void digitalWriteByte2   (int value) {};

    // Interrupts
    //	(Also Pi hardware specific)

    int  waitForInterrupt    (int pin, int mS) {return 0;};
    int  wiringPiISR         (int pin, int mode, void (*function)(void)) {return 0;};
    int  wiringPiISRStop     (int pin) {return 0;};  //V3.2
    int  waitForInterruptClose(int pin) {return 0;}; //V3.2

    // Threads

    int  piThreadCreate      (void *(*fn)(void *)) {return 0;};
    void piLock              (int key) {};
    void piUnlock            (int key) {};

    // Schedulling priority

    int piHiPri (const int pri) {return 0;};

    // Extras from arduino land

    void         delay             (unsigned int howLong) {};
    void         delayMicroseconds (unsigned int howLong) {};
    unsigned int millis            (void) {return 0;};
    unsigned int micros            (void) {return 0;};

    unsigned long long piMicros64(void){return 0;};   // Interface V3.7
#endif

#endif