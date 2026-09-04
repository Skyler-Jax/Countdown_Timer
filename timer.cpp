/***************************
 * Console Countdown Timer *
 *     Version 1.2.0       *
 *  by Skyler Jax Hansen   *
 *     Sep. 4th, 2026      *
 ***************************/

/*******************
 * Timer Functions *
 *******************/

#include "variables.h"
#include "functions.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace app;
using namespace display;

// Get timer hours from user
////////////////////////////
int timer::getHours() {
    cout << " Enter timer hours: (0-24)" << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> input;

    /*
     * Check if input is a valid positive integer. If so, check that the input is 24 hours or less,
     * 24 hours being considered the maximum value timer duration by the program. If the input is
     * exactly 24 hours, toggle the bool flags for hours, minutes and seconds as well to prevent
     * exceeding 24 hour max. If the value is less than 24, toggle only the hours' bool flag, store
     * the result, and continue. Otherwise, invalid entry restarts the function.
     */
    if (checkInput(input) == true) {
        if (stoi(input) > 24) {
            input.clear();
            clearScreen(true);
            getHours();
        } else if (stoi(input) == 24) {
            hours = stoi(input);
            hoursAreSet = !hoursAreSet;
            minsAreSet = !minsAreSet;
            secsAreSet = !secsAreSet;
            input.clear();
            clearScreen(false);
        } else {
            hours = stoi(input);
            hoursAreSet = !hoursAreSet;
            input.clear();
            clearScreen(true);
        }
    } else {
        hours = 0;
        input.clear();
        clearScreen(true);
        getHours();
    }

    return hours;
}

// Get timer minutes from user
//////////////////////////////
int timer::getMins() {
    cout << " Enter timer minutes: (0-59)" << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> input;

    /*
     * Check if input is a valid positive integer. If so, check that the input is between 0 and 59
     * minutes. If the input is within a valid range toggle the bool flag for minutess, store the
     * result, and continue. Otherwise, invalid entry restarts the function.
     */
    if (checkInput(input) == true) {
        if (stoi(input) > 59) {
            input.clear();
            clearScreen(true);
            getMins();
        } else {
            mins = stoi(input);
            minsAreSet = !minsAreSet;
            input.clear();
            clearScreen(true);
        }
    } else {
        mins = 0;
        input.clear();
        clearScreen(true);
        getMins();
    }

    return mins;
}

// Get timer seconds from user
//////////////////////////////
int timer::getSecs() {
    cout << " Enter timer seconds: (0-59)" << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> input;

    /*
     * Check if input is a valid positive integer. If so, check that the input is between 0 and 59
     * seconds. If the input is within a valid range toggle the bool flag for seconds, store the
     * result, and continue. Otherwise, invalid entry restarts the function.
     */
    if (checkInput(input) == true) {
        if (stoi(input) > 59) {
            input.clear();
            clearScreen(true);
            getSecs();
        } else {
            secs = stoi(input);
            secsAreSet = !secsAreSet;
            input.clear();
            clearScreen(false);
        }
    } else {
        secs = 0;
        input.clear();
        clearScreen(true);
        initApp();
    }

    return secs;
}

// 1 Hz program master clock
////////////////////////////
void timer::timerClock() {

    // Run timer thread for 1 second
    this_thread::sleep_for(chrono::seconds(1));

    // Decrement hours, mins, secs accordingly
    if (hours > 0 || mins > 0 || secs > 0) {
        if (secs >= 0) secs--;
        if (secs < 0) {
            if (mins == 0 && hours > 0) {
                hours--;
                mins = 59;
                secs = 59;
            } else {
                mins--;
                secs = 59;
            }
        }
    }

    // Decrement timer seconds remaining
    totalSecs--;
}


// Core timer program logic; increments timers and sets/syncs visual elements
/////////////////////////////////////////////////////////////////////////////
void timer::timerCore() {

    /* If the function is called while timer is enabled (was not paused), calculate progress bar segment:seconds ratio,
     * initialize bar percentage at 0, capture starting total seconds, set timer expired flag to false, and set timer
     * status clock icon position to 1 o'clock'
     */
    if (cleanStart) {
        timerCoreConfig();
    } //else {
        //timerEnabled = true;
    //}

    // Keep running this loop unless timer is paused/interrupted
    while (timerEnabled || (!timerEnabled && !timerHasExpired && programActive)) {
    //while (timerEnabled) {

        // Check for Linux keypress at the very top of the cycle
        if (pauseTimer()) {
            getchar();
            cin.clear();
            timerEnabled = false;
            break;
        }

        // Run this timer logic until total seconds reaches 0
        if (totalSecs >= 0) {

            // Clear screen/update displayed clock, flash digits when timer nears expiration when initial
            // duration was greater than 5 minutes
            if (totalSecs < 60 && startSecs > 300) {
                clearScreen(true);
            } else clearScreen(false);

            // Only call progress bar to display if initial duration was 1 minute or more
            if (startSecs > 59) {
                displayProgress(false, barPercent);
            }

            // Display program elements on screen
            displaySecs(startSecs, totalSecs);
            displayNote();
            timerClock();

            // Cycle clock running indicator or reset to '1 o'clock' if at '12 o'clock'
            if (clockHands == 12) clockHands = 1;
            else clockHands++;

            // Step progress bar per bar ratio and elapsed ticks calculations
            if (tickCount == (barRatio - 1)) {
                tickCount = 0;
                barPercent = barPercent + 5;
                if (barPercent > 100) barPercent = 100; // Prevents progress indication from exceeding 100% if calcs go awry
            } else tickCount++;

            //Cycle timer icon color while timer running
            if (iconColor == true) colorSwitch = !colorSwitch;

        } else if (totalSecs < 0) {
            // Set timer expired flag
            timerHasExpired = !timerHasExpired;

            // Disable the timer loop so function can exit
            timerEnabled = !timerEnabled;

            // Set status indicator to 13 to show completion checkmark upon timer expiration
            clockHands = 13;

            // Remove timer icon color upon timer expiration
            iconColor = false;

            // Ensures progress bar shows 100% in case error in calculations prevents natural completion
            displayProgress(true, 100);

            clearScreen(false);

            // Jump to timer expired routine
            timerExpired();
        }
    }

    // Run this logic if the timer loop exits before expiration
    if (!timerEnabled && !timerHasExpired) {

        // Jump to timer paused routing
        timerPaused();
    }
}

// Set up timer core for a clean void app::wait2Start()
///////////////////////////////////////////////////////
void timer::timerCoreConfig() {
    barRatio = calculateBarRatio();
    barPercent = 0;
    startSecs = totalSecs;
    timerHasExpired = false;
    clockHands = 1;
    cleanStart = !cleanStart;
}

