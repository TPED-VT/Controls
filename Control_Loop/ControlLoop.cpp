// void getNextSector(State *currentState, Sector *currentSector, bool test1, bool test2, bool test3) {
//     switch (*currentSector) {
//         case Sector::kSector1:
//             RideOpStateHandle(currentState, currentSector, test1, test2, test3);
//             break;
//         case Sector::kSector2:
//             RideOpStateHandle(currentState, currentSector, test1, test2, test3);
//             break;
//         case Sector::kSector3:
//             RideOpStateHandle(currentState, currentSector, test1, test2, test3);
//             break;
//         case Sector::kSector4:
//             RideOpStateHandle(currentState, currentSector, test1, test2, test3);
//             break;
//     }
// }

// void getCurrentSector(State *currentState, Sector *currentSector) {
//     if (*currentState == State::kRideOp) {
//         switch (*currentSector) {
//             case Sector::kSector1:
//                 *currentSector = Sector::kSector2;
//                 break;
//             case Sector::kSector2:
//                 *currentSector = Sector::kSector3;
//                 break;
//             case Sector::kSector3:
//                 *currentSector = Sector::kSector4;
//                 break;
//             case Sector::kSector4:
//                 *currentSector = Sector::kSector1;
//                 break;
//         }
//     }
// }

// int RideOpStateHandle(State *currentState, Sector *currentSector, int test1, int test2, int test3)
// {

    /*

    Ride Operator State Handle

    1. intialize the target arm and gondola motor frequencies
    2. get the current arm and gondola motor frequencies
    3. make sure to ramp up the arm and gondola motor frequencies based on the sector

    */


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
//}
