/***************************
 * Console Countdown Timer *
 *     Version 1.1.5       *
 *  by Skyler Jax Hansen   *
 *     Aug. 25th, 2026     *
 ***************************/

#include "variables.h"  //Header file containing variable declarations
#include "functions.h"  //Header file containing namespace and function declarations

using namespace app;
using namespace timer;
using namespace display;

int main(int argc, char** argv)
{
    //Set program's main loop as active
    programActive = true;

    //Initial variable initialization/program re-entry point for reset
    zeroVars();

    //Main loop repeats as long as programActive flag remains true
    while (programActive == true) {
        initApp();              //Set up timer, sub-functions handle getting user input and calculating total timer seconds
        getNote();              //Prompts user whether to add/enable optional note/reminder message
        wait2Start();           //Prompts user to start timer when setup completes successfully
        timerCore(totalSecs);   //Runs the timer core logic, sub-functions increment/decrement counters and sync visual elements
        timerExpired();         //Notifies timer expired and rings terminal bell
        timerReset();           //Propmpts user to reset timer or quit program
    }
    return 0;
}
