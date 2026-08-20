/***************************
 * Console Countdown Timer *
 *     Version 1.1.0       *
 *  by Skyler Jax Hansen   *
 *     Aug. 19th, 2026     *
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
inline bool areSetHours = false;
inline bool areSetMins = false;
inline bool areSetSecs = false;
inline bool noteIsSet = false;
inline bool programActive = true;
inline bool showTimerNote = false;
inline bool resetTimer = false;
inline const string ANSI_MGNTA = "\033[35m";
inline const string ANSI_GREEN = "\033[32m";
inline const string ANSI_BLINK = "\033[5m";
inline const string ANSI_RESET = "\033[0m";
inline string note;
inline string option;

/************************
 * Namespace & Function *
 *     Declarations     *
 ************************/
namespace app
{
    void zeroVars();
    void initApp();
    void wait2Start();
    void getNote();
    void displayNote();
    void timerExpired();
    void timerReset();
    int calculateBarRatio();
    string segmentDisplay(int input);
}

namespace timer
{
    int getHours();
    int getMins();
    int getSecs();
    void timerClock();
    void timerCore(int timerSecs);
}

namespace display
{
    void clearScreen(bool timerSetMode);
    void displayHeader();
    void displayClock(int hr, int min, int sec, int iconSelect, bool flashClock, bool hoursSet, bool minsSet, bool secsSet);
    void displaySecs(int totalSecs);
    void displayProgress(bool timerDone, int barPercent);
    void displayTimerIcon(int handPosition);
}
