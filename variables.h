/***************************
 * Console Countdown Timer *
 *     Version 1.1.6       *
 *  by Skyler Jax Hansen   *
 *     Aug. 27th, 2026     *
 ***************************/

#pragma once

#include <string>

using namespace std;

/****************************
 * Global Program Variables *
 ****************************/
inline int hours;           //User-entered total hours
inline int mins;            //User-entered total minutes
inline int secs;            //User-entered total seconds
inline int tickCount;       //Used with calculated progress bar segment:second ratio to determine when to add a segment
inline int clockHands;      //Used to determine which clock symbol to display while timer is active
inline int hours2Secs;      //Holds calculated hours-to-seconds value
inline int mins2Secs;       //Holds calculated minutes-to-seconds value
inline int totalSecs;       //The sum of hours2Secs + mins2Secs + secs, the value of which dictates behavior of other functions
inline int ringCount;       //How many times to ring alarm bell
inline bool timerWait;      //Whether the wait-to-start prompt is enabled or not
inline bool hoursAreSet;    //Hooks the main program loop to call getHours() if hours are not yet set
inline bool minsAreSet;     //Hooks the main program loop to call getMins() if minutes are not yet set
inline bool secsAreSet;     //Hooks the main program loop to call getSecs() if seconds are not yet set
inline bool bypassGetNote;  //Tells main() to bypass getting a note if time set through CLI arguments
inline bool showTimerNote;  //Tells displayNote() whether a note was entered for it to display
inline bool iconColor;      //Changes timer icon color when properly set
inline bool colorSwitch;    //Cycles timer icon color while timer running
inline bool programActive;  //Keeps the main loop running until user opts to quit
inline char note[64];       //Character array for holding user's note
inline string input;        //String to hold user's numeric input
inline string option;       //String to hold user's option input

/****************************
 * Global Program Constants *
 ****************************/
inline const string TEXT_FG_MGNTA = "\033[38;5;207m";   //Console output escape code for magenta colored characters
inline const string TEXT_FG_BLUE = "\033[38;5;69m";     //Console output escape code for blue colored characters
inline const string TEXT_FG_GREEN = "\033[38;5;46m";    //Console output escape code for green colored characters
inline const string TEXT_FG_YELLW = "\033[38;5;226m";   //Console output escape code for yellow colored characters
inline const string TEXT_FG_AMBER = "\033[38;5;208m";   //Console output escape code for amber colored characters
inline const string TEXT_FG_RED = "\033[38;5;196m";     //Console output escape code for red colored characters
inline const string TEXT_BG_SLATE = "\033[48;5;236m";   //Console output escape code for gray colored background
inline const string TEXT_BLINK = "\033[5m";             //Console output escape code for blinking test
inline const string TEXT_RESET = "\033[0m";             //Console output escape code for resetting formatting
inline const string CONSOLE_CLEAR = "\033[2J\033[H";    //Console output escape code for clearing the screen
inline const string CURSOR_HIDE = "\033[?25l";          //Console output escape code for hiding the cursor
inline const string CURSOR_SHOW = "\033[?25h";          //Console output escape code for showing the cursor
