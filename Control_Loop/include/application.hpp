#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "autoMode.hpp"
#include <vector>
#include <chrono>
// TODO: Make the Motor type analogous to what it becomes from the motor class
struct Motor{};

////////////////////////////////////////////////////////////////
// Masks for LEDs



////////////////////////////////////////////////////////////////

typedef long LED;   // Set each LED as 0 or 1 with a mask;
typedef enum {
    INIT, AUTO, MAN, MAINT
}Operation_State;


typedef enum {
    NOMINAL,    // No errors; all is good
    MOTOR1,     // Error with Motor1
    MOTOR2      // Error with Motor2
} Errors;

typedef struct Application{
    bool eStop;     // Has the E-Stop been pressed?
    bool GO;        // 'Go' signal for the dragon head
    Operation_State state; // What state is the ride in?
    Sector sect;    // What sector is the ride in (If not in Auto mode, this is 'OFF')
    // TODO: Hannah, please implement this with the GUI
    std::vector<Errors> errorList;  // List of errors in the system 
    // Timer for ride time goes here
    Motor motor;    // TODO: Make sure this is fixed with the Motor class
    
};

/**
 * @brief Sets up any GPIO, internal state variables, and external signal control
 * 
 * @param app The main ride application
 * @return void
 */
void initialize(Application *app);

/**
 * @brief Handle the Initial state. This is different from the initialize 
 * function since that runs before anything. This function is specific to
 * preride checks and things to do before 'opening'. Can consolidate if needed.
 * 
 * @param app The main ride application
 * @return void
 */
void handleInit(Application *app);

/**
 * @brief Handle the Automatic Operation state
 * 
 * @param app The main ride application
 * @return void
 */
void handleAuto(Application *app);

/**
 * @brief Handle the Manual Operation state
 * 
 * @param app The main ride application
 * @return void
 */
void handleManual(Application *app);

/**
 * @brief Handle the Maintenance state
 * 
 * @param app The main ride application
 * @return void
 */
void handleMaint(Application *app);
#endif // !APPLICATION_HPP