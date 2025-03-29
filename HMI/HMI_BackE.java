
public class HMI_BackE {
    static {
        System.loadLibrary("HMI_BackE");
    }

    public native int getCyclePercent(); // double needs to change
    public native void startCyclePercent();
    public native void setCyclePercent(int percent);


    public native boolean isRideRunning();

    public native boolean isRow1Locked();
    public native boolean isRow2Locked();

    public native boolean isReadyToRun();

    public native String getErrorMessage();

    public native boolean lockRestraints();
    public native boolean unlockRestraints();

    public native boolean isRotationGondolaClockwise();
    public native boolean isRotationGondolaCounterClockwise();

    public native boolean isRotationArmClockwise();
    public native boolean isRotationArmCounterClockwise();
}
