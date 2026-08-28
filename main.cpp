/***************************
 * Console Countdown Timer *
 *     Version 1.1.6       *
 *  by Skyler Jax Hansen   *
 *     Aug. 27th, 2026     *
 ***************************/

#include "variables.h"  //Header file containing variable declarations
#include "functions.h"  //Header file containing namespace and function declarations
#include "CLI11.hpp"    //Header library to process launch arguments

using namespace app;
using namespace timer;
using namespace display;

int main(int argc, char** argv)
{
    //Set program's main loop as active
    programActive = true;

    //Initial variable initialization/program re-entry point for reset
    zeroVars();

    //Process any launch arguments with CLI11 header library
    CLI::App ccc{"Console Countdown Clock Launch Options"};
    argv = ccc.ensure_utf8(argv);
    ccc.add_option("-h,--hours", hours, "Set timer hours");
    ccc.add_option("-m,--mins", mins, "Set timer minutes");
    ccc.add_option("-s,--secs", secs, "Set timer seconds");
    ccc.add_option("-r,--ring", ringCount, "Set number of rings (2 Default)");
    ccc.add_option("-w,--wait", timerWait, "Wait-to-start 'true'/'false'");
    CLI11_PARSE(ccc, argc, argv);

    //Update appropriate settings flags if time passed by launch arguments
    if (hours > 0 || mins > 0 || secs > 0) {
        hoursAreSet = true;
        minsAreSet = true;
        secsAreSet = true;
        bypassGetNote = true;
    }

    //Main loop repeats as long as programActive flag remains true
    while (programActive == true) {
        //Set up timer, sub-functions handle getting user input and calculating total timer seconds
        initApp();
        //Prompts user whether to add/enable optional note/reminder message
        if (!bypassGetNote) getNote();
        //Prompts user to start timer when setup completes successfully
        if (timerWait) wait2Start();
        //Runs the timer core logic; sub-functions increment/decrement counters and sync visual elements
        timerCore(totalSecs);
        //Notifies timer has expired and rings terminal bell
        timerExpired();
        //Prompts user to reset timer or quit program
        timerReset();
    }
    return 0;
}
