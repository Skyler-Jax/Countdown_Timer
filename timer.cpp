/***************************
 * Console Countdown Timer *
 *     Version 1.1.6       *
 *  by Skyler Jax Hansen   *
 *     Aug. 27th, 2026     *
 ***************************/

/*******************
 * Timer Functions *
 *******************/

#include "variables.h"
#include "functions.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std;
using namespace app;
using namespace display;

//Get timer hours from user
///////////////////////////
int timer::getHours()
{
    cout << " Enter timer hours: (0-24)" << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> input;
    if (checkInput(input) == true) {        //Check if input is a valid positive integer
        if (stoi(input) > 24) {             //Check if input exceeds 24 hours, reset process if so
            input.clear();
            clearScreen(true);
            getHours();
        }
        else if (stoi(input) == 24) {       //Check if exactly 24 hours entered, and set 'AreSet' flags for minutes and seconds if so
            hours = stoi(input);
            hoursAreSet = !hoursAreSet;
            minsAreSet = !minsAreSet;
            secsAreSet = !secsAreSet;
            input.clear();
            clearScreen(false);
        }
        else {
            hours = stoi(input);
            hoursAreSet = !hoursAreSet;     //Store valid hour input and proceed
            input.clear();
            clearScreen(true);
        }
    }
    else {                                  //Reject invalid input, start routine over
        hours = 0;
        input.clear();
        clearScreen(true);
        getHours();
    }
    return hours;
}

// Get timer minutes from user
//////////////////////////////
int timer::getMins()
{
    cout << " Enter timer minutes: (0-59)" << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> input;
    if (checkInput(input) == true) {        //Check if input is a valid positive integer
        if (stoi(input) > 59) {             //Check if input exceeds 59 minutes, reset process if so
            input.clear();
            clearScreen(true);
            getMins();
        }
        else {                              //Store valid minute input and proceed
            mins = stoi(input);
            minsAreSet = !minsAreSet;
            input.clear();
            clearScreen(true);
        }
    }
    else {                                  //Reject invalid input, start routine over
        mins = 0;
        input.clear();
        clearScreen(true);
        getMins();
    }
    return mins;
}

// Get timer seconds from user
//////////////////////////////
int timer::getSecs()
{
    cout << " Enter timer seconds: (0-59)" << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> input;
    if (checkInput(input) == true) {        //Check if input is a valid positive integer
        if (stoi(input) > 59) {             //Check if input exceeds 59 seconds, reset process if so
            input.clear();
            clearScreen(true);
            getSecs();
        }
        else {
            secs = stoi(input);             //Store valid second input and proceed
            secsAreSet = !secsAreSet;
            input.clear();
            clearScreen(false);
        }
    }
    else {                                  //Reject invalid input, start routine over
        secs = 0;
        input.clear();
        clearScreen(true);
        initApp();
    }
    return secs;
}

//1 Hz program master clock
///////////////////////////
void timer::timerClock()
{
    this_thread::sleep_for(chrono::seconds(1));     //Run timer thread for 1 second
    if (hours > 0 || mins > 0 || secs > 0) {        //Decrement hours, mins, secs accordingly
        if (secs >= 0) secs--;
        if (secs < 0) {
            if (mins == 0 && hours > 0) {
                hours--;
                mins = 59;
                secs = 59;
            }
            else {
                mins--;
                secs = 59;
            }
        }
    }
}

//Core program logic; increments timers and sets/syncs visual elements
//////////////////////////////////////////////////////////////////////
void timer::timerCore(int timerSecs)
{
    //Calculate progress bar segment:seconds ratio
    float barRatio = calculateBarRatio();

    //Initialize bar percentage at 0
    int barPercent = 0;

    //Capture starting total seconds
    int startSecs = timerSecs;

    //Initializes clock running indicator by setting to 1 (1 o'clock) from zero (keyboard icon; awaiting input)
    //One icon per each hour hand position, 1 - 12
    clockHands = 1;

    while (timerSecs >= 0) {                        //Loop this timer logic until total seconds reaches 0
        if (timerSecs < 60 && startSecs > 300) {    //Clear screen/update displayed clock, do not flash digits
            clearScreen(true);                      //unless initial timer > 5 minutes and < 60 seconds remain
        }
        else clearScreen(false);
        if (startSecs > 59) {                       //No progress bar for timers under 60 seconds
            displayProgress(false, barPercent);
        }

        //Display total starting/remaining seconds counters
        displaySecs(startSecs, timerSecs);

        //Display optional note/reminder
        displayNote();

        //Run master 1 Hz clock
        timerClock();

        //Decrement timer seconds remaining
        timerSecs--;

        if (clockHands == 12) clockHands = 1;   //Cycle clock running indicator or
        else clockHands++;                      //reset to '1 o'clock' if at '12 o'clock'

        if (tickCount == (barRatio - 1)) {              //Step progress bar per bar ratio
            tickCount = 0;                              //and elapsed ticks calculations
            barPercent = barPercent + 5;                //
            if (barPercent > 100) barPercent = 100;     //
        }                                               //
        else tickCount++;                               //

        //Cycle timer icon color while timer running
        if (iconColor == true) colorSwitch = !colorSwitch;

        continue;
    }

    //Set status indicator to 13 to show completion checkmark upon timer expiration
    clockHands = 13;

    //Remove timer icon color upon timer expiration
    iconColor = false;

    //Ensures progress bar shows 100% in case error in calculations prevents natural completion
    displayProgress(true, 100);

    clearScreen(false);
}
