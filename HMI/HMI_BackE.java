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

    public native void getNextState();  
    public native int setState();
    public native int getCurrentState();

// error handling 

    public native String getErrorMessage();
    public native void logErrorMessage();

    // E-STOP function
    public native int setUpGPIO();
    public native boolean eStopPressed();

    // for HMI
    public native int performRestraintCheck();
    public native boolean unlockRestraints(); // implementation
    public native boolean lockRestraints(); // implementation


// restraint handling    
    public native boolean restraintCheck();
    public native int isRow1Locked();
    public native int isRow2Locked();
    
// ride operation 
    public native boolean isReadyToRun();
    public native String isReadyToRunMessage();
    public native boolean isRideRunning();



}