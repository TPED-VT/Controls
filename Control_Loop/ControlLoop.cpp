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
