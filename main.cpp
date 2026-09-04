/***************************
 * Console Countdown Timer *
 *     Version 1.2.0       *
 *  by Skyler Jax Hansen   *
 *     Sep. 4th, 2026      *
 ***************************/

#include "variables.h"
#include "functions.h"
#include "CLI11.hpp"

using namespace app;
using namespace timer;
using namespace display;

int main(int argc, char** argv) {

    // Set program's main loop as active
    programActive = true;

    // Initial variable initialization/program re-entry point for reset
    zeroVars();

    // Process any launch arguments with CLI11 header library
    CLI::App ccc{"Console Countdown Clock Launch Options"};
    argv = ccc.ensure_utf8(argv);
    ccc.add_option("-h,--hours", hours, "Set timer hours");
    ccc.add_option("-m,--mins", mins, "Set timer minutes");
    ccc.add_option("-s,--secs", secs, "Set timer seconds");
    ccc.add_option("-r,--ring", ringCount, "Set number of rings (2 Default)");
    ccc.add_option("-w,--wait", timerWait, "Wait-to-start 'true' or '1'/'false' or '0'");
    CLI11_PARSE(ccc, argc, argv);

    // Update appropriate settings flags if time passed by launch arguments
    if (hours > 0 || mins > 0 || secs > 0) {
        hoursAreSet     = true;
        minsAreSet      = true;
        secsAreSet      = true;
        bypassGetNote   = true;
    }

    // Main loop repeats as long as programActive flag remains true
    while (programActive == true) runTimer();

    return 0;
}
