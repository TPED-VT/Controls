#include "application.hpp"

void initialize(Application *app) {
    // Creat the application in the INIT mode (AUTO is OFF)
    app->state = INIT;
    app->sect = OFF;
    // Init any LEDs and Buttons

    // Make sure all motors are at their reset position
}