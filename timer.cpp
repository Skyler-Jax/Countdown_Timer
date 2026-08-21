/***************************
 * Console Countdown Timer *
 *     Version 1.1.3       *
 *  by Skyler Jax Hansen   *
 *     Aug. 21st, 2026     *
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

// Get timer hours from console input
int timer::getHours()
{
    cout << " Enter timer hours: (0-24)" << endl << ANSI_YELLW << "   " << ANSI_RESET << ANSI_CSHOW;
    cin >> input;
    if (checkInput(input) == true) {
        if (stoi(input) > 24) {
            input.clear();
            clearScreen(1);
            initApp();
        }
        else if (stoi(input) == 24) {
            hours = stoi(input);
            hoursAreSet = !hoursAreSet;
            minsAreSet = !minsAreSet;
            secsAreSet = !secsAreSet;
            input.clear();
            clearScreen(0);
        }
        else {
            hours = stoi(input);
            hoursAreSet = !hoursAreSet;
            input.clear();
            clearScreen(1);
        }
    }
    else {
        input.clear();
        clearScreen(1);
        initApp();
    }
    return hours;
}

// Get timer minutes from console input
int timer::getMins()
{
    cout << " Enter timer minutes: (0-59)" << endl << ANSI_YELLW << "   " << ANSI_RESET << ANSI_CSHOW;
    cin >> input;
    if (checkInput(input) == true) {
        if (stoi(input) > 59) {
            input.clear();
            clearScreen(1);
            initApp();
        }
        else {
            mins = stoi(input);
            minsAreSet = !minsAreSet;
            input.clear();
            clearScreen(1);
        }
    }
    else {
        input.clear();
        clearScreen(1);
        initApp();
    }
    return mins;
}

// Get timer seconds from console input
int timer::getSecs()
{
    cout << " Enter timer seconds: (0-59)" << endl << ANSI_YELLW << "   " << ANSI_RESET << ANSI_CSHOW;
    cin >> input;
    if (checkInput(input) == true) {
        if (stoi(input) > 59) {
            input.clear();
            clearScreen(1);
            initApp();
        }
        else {
            secs = stoi(input);
            secsAreSet = !secsAreSet;
            input.clear();
            clearScreen(0);
        }
    }
    else {
        input.clear();
        clearScreen(1);
        initApp();
    }
    return secs;
}

// Timer clock tick
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
    int startSecs = timerSecs;
    clockHands = 1;
    iconColor = !iconColor;
    while (timerSecs >= 0) {
        clearScreen(0);
        if (startSecs > 59) displayProgress(false, barPercent);
        displaySecs(startSecs, timerSecs);
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
    iconColor = !iconColor;
    clockHands = 13;
    clearScreen(0);
    if (startSecs > 59) displayProgress(true, 100);
}
