/***************************
 * Console Countdown Timer *
 *     Version 1.1.5       *
 *  by Skyler Jax Hansen   *
 *     Aug. 25th, 2026     *
 ***************************/

#include "variables.h"
#include "functions.h"
#include <iostream>
#include <chrono>
#include <string>
#include <thread>

using namespace std;
using namespace app;
using namespace display;
using namespace timer;

/*****************************
 * General Program Functions *
 *****************************/

//Step 1: Clear/initialize all variables to prepare for timer setup
///////////////////////////////////////////////////////////////////
void app::zeroVars()
{
    hours = 0;
    mins = 0;
    secs = 0;
    tickCount = 0;
    clockHands = 0;
    hours2Secs = 0;
    mins2Secs = 0;
    totalSecs = 0;
    hoursAreSet = false;
    minsAreSet = false;
    secsAreSet = false;
    noteIsSet = false;
    showTimerNote = false;
    iconColor = false;
    colorSwitch = false;
    input.clear();
    option.clear();
}

//Step 2a: Get time values from user and initialize timerCore()
///////////////////////////////////////////////////////////////
void app::initApp()
{
    clearScreen(true); //'true' resets screen with flashing timer clock display during setting

    if (hoursAreSet == false) hours = getHours();

    //Convert entered hours into seconds
    hours2Secs = hours * 60 * 60;

    if (minsAreSet == false) mins = getMins();

    //Converted entered minutes into seconds
    mins2Secs = mins * 60;

    if (secsAreSet == false) secs = getSecs();

    //Store sum of hours2Secs + mins2Secs + secs for other functions' use
    totalSecs = hours2Secs + mins2Secs + secs;

    iconColor = true; //Change icon timer color from white to green, indicates successful timer set routine

    clearScreen(0); //'false' resets screen with solid timer clock display, used at all other times besides when setting
}

//Step 2b: Checks whether user entered valid positive integer to set time with
//////////////////////////////////////////////////////////////////////////////
bool app::checkInput(const string& input)
{
    return !input.empty() && all_of(input.begin(), input.end(), [](unsigned char c) {
        return isdigit(c);
    });
}

//Step 3: Promp user for optional timer note/reminder
/////////////////////////////////////////////////////
void app::getNote()
{
    cout << " Attach note to timer? (Y/N)" << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> option;
    if (option == "Y" || option == "y") {       //Sets flag for next step of function to grab note text from user
        noteIsSet = !noteIsSet;                 //
        showTimerNote = !showTimerNote;         //Sets flag for displayNote() function to activate note output during countdown
        option.clear();
        clearScreen(false);
    }
    else if (option == "N" || option == "n") {  //Continues through program loop if no note desired
        option.clear();
        clearScreen(false);
    }
    else {                                      //Returns to top of getNote() with no valid input, in case of accidental skip-over
        option.clear();
        clearScreen(false);
        getNote();
    }
    if (noteIsSet == true) {                    //Gets note text from user to store in note[64] character array
        cout << " Enter reminder/note for this timer:" << endl << TEXT_FG_BLUE << "   " << TEXT_RESET;
        cin.ignore();
        cin.get(note, 63);
        clearScreen(0);
    }
}

//Step 4: Pause after gathering information, wait for user to start timer
/////////////////////////////////////////////////////////////////////////
void app::wait2Start()
{
    cout << " Timer set, press Enter to start..." << TEXT_FG_GREEN << TEXT_BLINK << "  " << TEXT_RESET;
    cin.ignore();
    cin.get();
}

//Step 5: Calculates appropriate bar segnemt:seconds ratio for progress bar
///////////////////////////////////////////////////////////////////////////
int app::calculateBarRatio()
{
    int sum = 0;
    int ratio = 0;
    if (secs > 0 && secs < 10) sum = hours2Secs + mins2Secs + 10;
    if (secs > 10 && secs < 20) sum = hours2Secs + mins2Secs + 20;
    if (secs > 20 && secs < 30) sum = hours2Secs + mins2Secs + 30;
    if (secs > 30 && secs < 40) sum = hours2Secs + mins2Secs + 40;
    if (secs > 40 && secs < 50) sum = hours2Secs + mins2Secs + 50;
    if (secs > 50 && secs < 60) sum = hours2Secs + mins2Secs + 60;
    else sum = hours2Secs + mins2Secs + secs;
    ratio = sum / 20;
    return ratio;
}

//Step 6: Handle timer reset or program exit
////////////////////////////////////////////
void app::timerReset()
{
    cout << " R to   or Q to  " << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> option;
    if (option == "Q" || option == "q") {
        programActive = !programActive;
        cout << CONSOLE_CLEAR << flush;
    }
    else if (option == "R" || option == "r") {
        zeroVars();
        initApp();
    }
    else {
        option.clear();
        clearScreen(0);
        timerReset();
    }
}
