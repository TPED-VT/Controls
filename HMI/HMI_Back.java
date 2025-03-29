
public class HMI_Back {
    static {
        System.loadLibrary("HMI_Back");
    }

    public native int getCyclePercent(int percent);

    public native boolean isRideRunning(boolean running);

    public native boolean isRow1Locked(boolean row1locked);
    public native boolean isRow2Locked(boolean row2locked);

    public native boolean isReadyToRun(boolean ready);

    public native String getErrorMessage(String errorMessage);

    public native boolean lockRestraints(boolean lock);
    public native boolean unlockRestraints(boolean unlock);

    public native boolean isRotationGondolaClockwise(boolean clockwise_b);
    public native boolean isRotationGondolaCounterClockwise(boolean counterclockwise_b);

    public native boolean isRotationArmClockwise(boolean clockwise_a);
    public native boolean isRotationArmCounterClockwise(boolean counterclockwise_a);
}
