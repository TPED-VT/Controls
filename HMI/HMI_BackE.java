
public class HMI_BackE {
    static {
        try {
            System.load("C:/Users/ricar/Documents/TPED/Controls/native/HMI_BackE.dll");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Failed to load HMI_BackE.dll: " + e.getMessage());
            throw e; 
        }
    }
    

    public static void main(String[] agrs) {
        // new HMI_BackE().getPosition();
        System.out.println("Hello World");
    }

    public native int getCyclePercent(); // double needs to change
    public native void startCyclePercent();
    public native void setCyclePercent(int percent);

    public native void getPosition();

    // states

    public native void setState(int state); // not sure
    public native int getCurrentState();
    public native void getNextSector(long currentState, long currentSector, boolean test1, boolean test2, boolean test3);
    public native void getCurrentSector(long currentState, long currentSector);
    
    
// others

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
