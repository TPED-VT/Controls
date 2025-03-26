#pragma once

#include "functions.h"

// state transition function
void getNextState(State *currentState, bool test1, bool test2, bool test3)
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
        RideOpStateHandle(currentState, test1, test2, test3);
        break;

    // case State::kMaintenance: // 
    //     MaintenanceStateHandle(currentState, currentTest, password, test1, test2, test3, test4, test5);
    //     break;
    }
}


//handling functions
void RideShowStateHandle()
{
    cout << "Ride Show State" << endl;
}

void RideOpStateHandle(State *currentState, bool test1, bool test2, bool test3)
{
    for (int motorRotation = 0; motorRotation < 10; motorRotation++) // temp values
    {
        string motorRotationDirection;
        if (motorRotation % 2 == 0)
        {
            motorRotationDirection = "arm";
        }
        else
        {
            motorRotationDirection = "gondola";
        }

        cout << "Motor rotation: " << motorRotationDirection << endl;

        RideShowStateHandle(); // display ride show state
    }

    cout << "All motor rotations completed successfully. Remaining in Auto state." << endl;
    *currentState = State::kAuto;
}

void InitStateHandle(State *currentState, bool test1, bool test2, bool test3) {

    *currentState = State::kAuto;
}

void AutoStateHandle(State *currentState, bool test1, bool test2, bool test3)
{
    *currentState = State::kRideOp;
}



// void MaintenanceStateHandle(State *currentState, StateTest *currentTest, string password, bool test1, bool test3, bool test4, bool test5)
// {
//     cout << "Enter password: ";
//     cin >> password;

//     if (password != "hokie") {
//         cout << "Invalid Password. Enter a valid password to access Maintenance State." << endl;
//         *currentState = State::kAuto;
//     } else {
//         cout << "Password accepted. Accessing Maintenance State..." << endl;
//         *currentState = State::kMaintenance;

//         cout << "Select Advanced Tests" << endl
//              << "1. Test 4" << endl
//              << "2. Test 5" << endl;
//         cin >> *currentTest;

//         switch (*currentTest)
//         {
//             case StateTest::kTest4:
//                 if (!test4) {
//                     cout << "Test 4 has failed." << endl;
//                     cout << "Try again?" << endl;
//                     cin >> *currentTest;
//                 }
//                 break;

//             case StateTest::kTest5:
//                 if (!test5) {
//                     cout << "Test 5 has failed." << endl;
//                     cout << "Try again?" << endl;
//                     cin >> *currentTest;
//                 }
//                 break;

//             default:
//                 cout << "Invalid test selection." << endl;
//                 break;
//         }
//     }

//     cout << "Press Enter to return to Auto state..." << endl;
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');
//     *currentState = State::kAuto;
// }

// ignore the mat function needs to be added with HMI, PROOF OF CONCEPT NOT FINAL CODE!!!!!!!