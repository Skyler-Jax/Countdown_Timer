/***************************
 * Console Countdown Clock *
 *     Version 1.2.1       *
 *  by Skyler Jax Hansen   *
 *     Sep. 15th, 2026     *
 ***************************/

/*
 * This file contains the global program variables
 * and relevant preprocessor directives.
 */

#pragma once
#include <string>

using namespace std;
inline int hours;           // User-entered total hours
inline int mins;            // User-entered total minutes
inline int secs;            // User-entered total seconds
inline int tickCount;       // Used with calculated progress bar segment:second ratio to determine when to add a segment
inline int clockHands;      // Used to determine which clock symbol to display while timer is active
inline int hours2Secs;      // Holds calculated hours-to-seconds value
inline int mins2Secs;       // Holds calculated minutes-to-seconds value
inline int totalSecs;       // The sum of hours2Secs + mins2Secs + secs, the value of which dictates behavior of other functions
inline int ringCount;       // How many times to ring alarm bell
inline float barRatio;      // Ratio used determine bar segment:seconds
inline int barPercent;      // Progress bar percentage value
inline int startSecs;       // Captured total seconds at start of timer
inline bool programActive;  // Keeps the main loop running until user opts to quit
inline bool timerEnabled;   // Whether the timer is allowed to run or is paused
inline bool appInitialized; // Whether the program has been properly initialized
inline bool cleanStart;     // Tells timerCore() whether it was called into a clean start or called to resume from pause
inline bool timerRunning;   // Indicates that timer is set and running
inline bool timerHasExpired;// Indicates that timer naturally expired
inline bool timerWait;      // Whether the wait-to-start prompt is enabled or not
inline bool hoursAreSet;    // Hooks the main program loop to call getHours() if hours are not yet set
inline bool minsAreSet;     // Hooks the main program loop to call getMins() if minutes are not yet set
inline bool secsAreSet;     // Hooks the main program loop to call getSecs() if seconds are not yet set
inline bool bypassGetNote;  // Tells main() to bypass getting a note if time set through CLI arguments
inline bool showTimerNote;  // Tells displayNote() whether a note was entered for it to display
inline bool iconColor;      // Changes timer icon color when properly set
inline bool colorSwitch;    // Cycles timer icon color while timer running
inline char note[64];       // Character array for holding user's note
inline string input;        // String to hold user's numeric input
inline string option;       // String to hold user's option input
