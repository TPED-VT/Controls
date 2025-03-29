
#include "functions.h"
#include "../Motor_Control/functions.h"

// state transition function
void getNextState(State *currentState, Sector *currentSector, bool test1, bool test2, bool test3)
{
    switch (*currentState)
    {
    case State::kInit:
        InitStateHandle(currentState, test1, test2, test3);
        break;

    case State::kAuto: // checks tests 1,2,3 
        AutoStateHandle(currentState, test1, test2, test3);
        break;

    case State::kRideOp: // arm motor rotation and gondola motor rotation (apart of auto state for now)
        RideOpStateHandle(currentState, currentSector, test1, test2, test3);
        break;

    // case State::kMaintenance: // 
    //     MaintenanceStateHandle(currentState, currentTest, password, test1, test2, test3, test4, test5);
    //     break;
    }
}

void getNextSector(State *currentState, Sector *currentSector, bool test1, bool test2, bool test3) {
    switch (*currentSector) {
        case Sector::kSector1:
            RideOpStateHandle(currentState, currentSector, test1, test2, test3);
            break; 
        case Sector::kSector2:
            RideOpStateHandle(currentState, currentSector, test1, test2, test3);
            break;
        case Sector::kSector3:
            RideOpStateHandle(currentState, currentSector, test1, test2, test3);
            break;
        case Sector::kSector4:
            RideOpStateHandle(currentState, currentSector, test1, test2, test3);
            break; 
    }
}

//handling functions
void RideShowStateHandle(State *currentState, Sector *currentSector, bool test1, bool test2, bool test3) {

    int dummy = 2; // we need a variable to check if the ride show state has ended
 
  if (*currentState != State::kRideOp) {
    cout << "unable to do rideop :(" << endl; 
    } else {
       getNextSector(currentState, currentSector, test1, test2, test3);
  }
  
 if (*currentSector == Sector::kSector4) {
    if (dummy == 2) {
        *currentState = State::kAuto; 
    }
 } 
 
}


void RideOpStateHandle(State *currentState, Sector *currentSector, bool test1, bool test2, bool test3)
{

    /*
    
    Ride Operator State Handle

    1. intialize the target arm and gondola motor frequencies
    2. get the current arm and gondola motor frequencies 
    3. make sure to ramp up the arm and gondola motor frequencies based on the sector

    */

    int targetArmMotorFrequency = 200; 
    int targetGondolaMotorFrequency = 100;

    int currentArmMotorFrequency = 150; 



    // switch (*currentState) {
    //     case State::kRideOp: {
    //         for (int i = 0; i < 50; i++) {
    //            int  currentArmMotorFrequency == getCurrentArmFrequency();
    //            int  currentGondolaMotorFrequency == getCurrentGondolaFrequency();
    //         }

    //         RampUp(currentArmMotorFrequency, currentGondolaMotorFrequency);
    //         break;
    //     }
    // }
    //     cout << "All motor rotations completed successfully. Remaining in Auto state." << endl;
    //     *currentState = State::kAuto;
    }


void InitStateHandle(State *currentState, bool test1, bool test2, bool test3) {

    *currentState = State::kAuto;
}

void AutoStateHandle(State *currentState, bool test1, bool test2, bool test3)
{
    *currentState = State::kRideOp;
}