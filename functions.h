/***************************
 * Console Countdown Timer *
 *     Version 1.1.5       *
 *  by Skyler Jax Hansen   *
 *     Aug. 25th, 2026     *
 ***************************/

#pragma once

#include <string>

using namespace std;

/************************
 * Namespace & Function *
 *     Declarations     *
 ************************/
namespace app                               //Program initialization and setup functions
{
    void zeroVars();                        //Step 1: Clear/initialize all variables to prepare for timer setup
    void initApp();                         //Step 2a: Get time values from user and initialize timerCore()
    bool checkInput(const string& input);   //Step 2b: Checks whether user entered valid positive integer to set time with
    void getNote();                         //Step 3: Promp user for optional timer note/reminder
    void wait2Start();                      //Step 4: Pause after gathering information, wait for user to start timer
    int calculateBarRatio();                //Step 5: Calculates appropriate bar segnemt:seconds ratio for progress bar
    void timerReset();                      //Step 6: Handle timer reset or program exit
}

namespace timer                     //Time setting and tracking functions
{
    int getHours();                 //Get timer hours from user
    int getMins();                  //Get timer minutes from user
    int getSecs();                  //Get timer seconds from user
    void timerClock();              //1 Hz program master clock
    void timerCore(int timerSecs);  //Core program logic; increments timers and sets/syncs visual elements
}

namespace display                                                   //Screen handling/display functions
{
    void clearScreen(bool timerSetMode);                            //Clears console, initiates redrawing program header and timer display
    void displayHeader();                                           //Called by clearScreen(), redraws header
    void displayClock(int hr, int min, int sec, int iconSelect,     //Called by clearScreen(), redraws current timer
                      bool flashClock, bool hoursSet,               //
                      bool minsSet, bool secsSet, bool iconColor);  //
    void displayProgress(bool timerDone, int barPercent);           //Shows progress bar
    void displaySecs(int startSecs, int remainSecs);                //Shows total starting and remaining seconds while timer active
    void displayNote();                                             //Displays optional note/reminder while timer is running
    void timerExpired();                                            //Displays timer expired message and handles ringing terminal bell
    string statusIcon(int input);                                   //Returns status icon from look-up array
    string segmentDisplay(int input);                               //Returns sylized digit symbol from ASCII numeral translation
}
