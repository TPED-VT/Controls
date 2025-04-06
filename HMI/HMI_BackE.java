public class HMI_BackE {
    static {
        System.loadLibrary("HMI_BackE");
    }

    public static void main(String[] agrs) {
        new HMI_BackE().setUpGPIO();
        // new HMI_BackE().getPosition(); // Does this remove two screens?
    }

    public native double getCyclePercent(); // double needs to change: implementation
    public native void startCyclePercent();
    public native int getCycleCount();
    public native void setCyclePercent(int percent);

    public native float[] getPosition();

// states

    public native void getNextState();  
    public native int setState(int state);
    public native int getCurrentState();

// error handling 

    public native String getErrorMessage();
    public native String getStatusMessage();
    public native String getMaintenanceError();
    public native String getMaintenanceMessage();
    public native String getTestStatusMessage();

    // E-STOP function
    public native int setUpGPIO();
    public native boolean eStopPressed();

    // for HMI
    public native int performRestraintCheck();
    public native boolean unlockRestraints(); // implementation
    public native boolean lockRestraints(); // implementation

// restraint handling    
    public native boolean restraintCheck();
    public native boolean isRow1Locked();
    public native boolean isRow2Locked();
    
// ride operation 
    public native boolean isReadyToRun();
    public native String isReadyToRunMessage();
    public native boolean isRideRunning();
    public native void dispatch();
    public native boolean stop();
    public native boolean homeArm();
    public native boolean maintArmCheck();
    public native boolean homeGondola();

// testing 
    public native int getCurrentTest();
    public native int setCurrentTest(int test);
    // public native String statusMessage();
    public native int maintenanceSelection(int access, int test);

}