public class HMI_BackE {
    static {
        System.loadLibrary("HMI_BackE");
    }

    public static void main(String[] agrs) {
        new HMI_BackE().getPosition();
    }

    public native double getCyclePercent(); // double needs to change
    public native void startCyclePercent();
    public native void setCyclePercent(int percent);

    public native int getPosition();

// states

    public native void getNextState(int currentState, int RestraintCheck, int isHomed, int ArmTest);    
    
// other functions 
// error handling 

    public native String getErrorMessage(int RestraintCheck, int isHomed);
    public native void logErrorMessage(String message);

// restraint handling    
    public native boolean restraintCheck(boolean restraint);
    public native int isRow1Locked(boolean restraint1);
    public native int isRow2Locked(boolean restraint2);
    
    public native boolean lockRestraints();
    public native boolean unlockRestraints();

// ride operation 

    public native boolean isReadyToRun(int RestraintCheck, int isHomed, int ArmTest);
    public native String isReadyToRunMessage(int RestraintCheck, int isHomed, int ArmTest);
    public native boolean isRideRunning();





    // public native boolean isRotationGondolaClockwise();
    // public native boolean isRotationGondolaCounterClockwise();

    // public native boolean isRotationArmClockwise();
    // public native boolean isRotationArmCounterClockwise();



}
