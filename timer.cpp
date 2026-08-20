/***************************
 * Console Countdown Timer *
 *     Version 1.1.0       *
 *  by Skyler Jax Hansen   *
 *     Aug. 19th, 2026     *
 ***************************/

/*******************
 * Timer Functions *
 *******************/

#include "functions.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std;
using namespace app;
using namespace display;

// Get timer hours from console input
int timer::getHours()
{
    cout << "Enter timer hours:" << endl;
    cin >> hours;
    areSetHours = !areSetHours;
    clearScreen(1);
    return hours;
}

// Get timer minutes from console input
int timer::getMins()
{
    cout << "Enter timer minutes:" << endl;
    cin >> mins;
    if (mins > 59 || mins < 0) {
        timer::getMins();
    }
    areSetMins = !areSetMins;
    clearScreen(1);
    return mins;
}

// Get timer seconds from console input
int timer::getSecs()
{
    cout << "Enter timer seconds:" << endl;
    cin >> secs;
    if (secs > 59 || secs < 0) {
        timer::getSecs();
    }
    areSetSecs = !areSetSecs;
    clearScreen(0);
    return secs;
}

// Timer clock
void timer::timerClock()
{
    this_thread::sleep_for(chrono::seconds(1));
    if (hours > 0 || mins > 0 || secs > 0) {
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

// Timer component
void timer::timerCore(int timerSecs)
{
    float barRatio = calculateBarRatio();
    int barPercent = 0;
    clockHands = 1;
    while (timerSecs >= 0) {
        clearScreen(0);
        displayProgress(false, barPercent);
        displaySecs(timerSecs);
        displayNote();
        timer::timerClock();
        timerSecs--;
        if (clockHands == 12) clockHands = 1;
        else clockHands++;
        if (tickCount == (barRatio - 1)) {
            tickCount = 0;
            barPercent = barPercent + 5;
            if (barPercent > 100) barPercent = 100;
        }
        else tickCount++;
        continue;
    }
    clockHands = 13;
    clearScreen(0);
    displayProgress(true, 100);
}
