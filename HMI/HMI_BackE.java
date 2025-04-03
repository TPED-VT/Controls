

public class HMI_BackE {
    static {
        System.loadLibrary("HMI_BackE");
    }

    public static void main(String[] agrs) {
        new HMI_BackE().setUpGPIO();
        new HMI_BackE().getPosition();
    }

    public native double getCyclePercent(); // double needs to change: implementation
    public native void startCyclePercent();
    public native void setCyclePercent(int percent);

    public native int getPosition();

// states

    public native void getNextState(int currentState, int RestraintCheck, int isHomed, int ArmTest);    
    
// other functions 


// error handling 

    public native String getErrorMessage(int RestraintCheck, int isHomed, int ArmTest);
    public native void logErrorMessage(String message);

    // E-STOP function
    public native int setUpGPIO();
    public native boolean eStopPressed();
    // for HMI
    public native String getErrorMessage();
    public native String isReadyToRunMessage();
    public native boolean isReadyToRun();
    public native int performRestraintCheck();
    public native int isRow1Locked();
    public native int isRow2Locked();
    public native boolean unlockRestraints(); // implementation
    public native boolean lockRestraints(); // implementation


// restraint handling    
    public native boolean restraintCheck(boolean restraint);
    public native int isRow1Locked(boolean restraint1);
    public native int isRow2Locked(boolean restraint2);
    
// ride operation 
    public native boolean isReadyToRun(int RestraintCheck, int isHomed, int ArmTest);
    public native String isReadyToRunMessage(int RestraintCheck, int isHomed, int ArmTest);
    public native boolean isRideRunning();



}
