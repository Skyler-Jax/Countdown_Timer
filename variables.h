/***************************
 * Console Countdown Timer *
 *     Version 1.1.3       *
 *  by Skyler Jax Hansen   *
 *     Aug. 21st, 2026     *
 ***************************/

#pragma once

#include <string>

using namespace std;

/****************************
 * Global Program Variables *
 ****************************/
inline int hours = 0;
inline int mins = 0;
inline int secs = 0;
inline int tickCount = 0;
inline int clockHands = 0;
inline int hours2Secs = 0;
inline int mins2Secs = 0;
inline int totalSecs = 0;
inline bool hoursAreSet = false;
inline bool minsAreSet = false;
inline bool secsAreSet = false;
inline bool noteIsSet = false;
inline bool programActive = true;
inline bool showTimerNote = false;
inline bool resetTimer = false;
inline bool iconColor = false;
inline bool colorSwitch = false;
inline const string ANSI_MGNTA = "\033[35m";
inline const string ANSI_BLUE = "\033[34m";
inline const string ANSI_GREEN = "\033[32m";
inline const string ANSI_YELLW = "\033[33m";
inline const string ANSI_BLINK = "\033[5m";
inline const string ANSI_RESET = "\033[0m";
inline const string ANSI_ERASE = "\033[2J\033[H";
inline const string ANSI_CHIDE = "\033[?25l";
inline const string ANSI_CSHOW = "\033[?25h";
inline char note[64];
inline string input;
inline string option;
