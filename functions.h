/***************************
 * Console Countdown Timer *
 *     Version 1.1.4       *
 *  by Skyler Jax Hansen   *
 *     Aug. 21st, 2026     *
 ***************************/

#pragma once

#include <string>

using namespace std;

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
    bool checkInput(const string& input);
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
    void displayClock(int hr, int min, int sec, int iconSelect, bool flashClock, bool hoursSet, bool minsSet, bool secsSet, bool iconColor);
    void displaySecs(int startSecs, int remainSecs);
    void displayProgress(bool timerDone, int barPercent);
    void displayTimerIcon(int handPosition);
}
