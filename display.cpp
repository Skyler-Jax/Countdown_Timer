/***************************
 * Console Countdown Timer *
 *     Version 1.1.4       *
 *  by Skyler Jax Hansen   *
 *     Aug. 21st, 2026     *
 ***************************/

/********************
 * Screen Functions *
 ********************/
#include "variables.h"
#include "functions.h"
#include <iostream>
#include <string>

using namespace std;
using namespace app;

// Clear the screen
void display::clearScreen(bool timerSetMode)
{
    cout << ANSI_ERASE << ANSI_CHIDE << flush;
    displayHeader();
    displayClock(hours, mins, secs, clockHands, timerSetMode, hoursAreSet, minsAreSet, secsAreSet, iconColor);
}

// Draw program header on screen
void display::displayHeader()
{
    cout << ANSI_MGNTA;
    cout << " ╭─────────────────────────╮" << endl;
    cout << " │ Console Countdown Clock │" << endl;
    cout << " │";
    cout << ANSI_GREEN << "  ⓑⓨ🅢ⓚⓨⓛⓔⓡ🅙ⓐⓧ🅗ⓐⓝⓢⓔⓝ🄌🄯⓴㉖ ";
    cout << ANSI_MGNTA << "│" << endl;
    cout << " ╰─────────────────────────╯" << endl;
    cout << ANSI_RESET;
}

// Draw clock on screen
void display::displayClock(int hr, int min, int sec, int iconSelect, bool flashClock, bool hoursSet, bool minsSet, bool secsSet, bool iconColor)
{
    cout << " Countdown clock: ";
    displayTimerIcon(iconSelect);
    if (iconColor == true) {
        if (colorSwitch == true) {
            cout << ANSI_YELLW << "  ";
        }
        else cout << ANSI_GREEN << "  ";
        colorSwitch = !colorSwitch;
    }
    else cout <<  "  ";
    if (flashClock == true) cout << ANSI_BLINK;
    cout << ANSI_GREEN;
    if (hoursSet == false) cout << "__:";
    else if (hoursSet == true) {
        if (hr < 10) cout << "🯰";
        cout << segmentDisplay(hr) << ":";
    }
    if (minsSet == false) cout << "__:";
    else if (minsSet == true) {
        if (min < 10) cout << "🯰";
        cout << segmentDisplay(min) << ":";
    }
    if (secsSet == false) cout << "__" << endl << endl;
    else if (secsSet == true) {
        if (sec < 10) cout << "🯰";
        cout << segmentDisplay(sec) << endl << endl;
    }
    cout << ANSI_RESET;
}

// Draw timer icon
void display::displayTimerIcon(int handPosition)
{
    if (handPosition == 0) cout << "🖮" << endl;
    if (handPosition == 1) cout << "🕐" << endl;
    if (handPosition == 2) cout << "🕑" << endl;
    if (handPosition == 3) cout << "🕒" << endl;
    if (handPosition == 4) cout << "🕓" << endl;
    if (handPosition == 5) cout << "🕔" << endl;
    if (handPosition == 6) cout << "🕕" << endl;
    if (handPosition == 7) cout << "🕖" << endl;
    if (handPosition == 8) cout << "🕗" << endl;
    if (handPosition == 9) cout << "🕘" << endl;
    if (handPosition == 10) cout << "🕙" << endl;
    if (handPosition == 11) cout << "🕚" << endl;
    if (handPosition == 12) cout << "🕛" << endl;
    if (handPosition == 13) cout << "✅" << endl;
}

// Draw progress bar on screen
void display::displayProgress(bool timerDone, int barPercent)
{
    cout << "   Elapsed duration: ";
    if (barPercent < 10) cout << " ";
    if (barPercent < 100) cout << " ";
    cout << barPercent << "%" << endl;
    cout << "   ⦗";
    for (int i = 0; i < 20; i++) {
        if (timerDone == false) {
            if (i < barPercent / 5) cout << ANSI_GREEN << "⨁";
            else cout << ANSI_YELLW << "🞄";
        }
        if (timerDone == true) cout << ANSI_GREEN << "🞅";
    }
    cout << ANSI_RESET << "⦘" << endl;
}

// Draw total timer seconds on screen
void display::displaySecs(int startSecs, int remainSecs)
{
    cout << "  "<< ANSI_GREEN;
    if (startSecs < 10) cout << "🯰";
    if (startSecs < 100) cout << "🯰";
    if (startSecs < 1000) cout << "🯰";
    if (startSecs < 10000) cout << "🯰";
    cout << segmentDisplay(startSecs) << ANSI_RESET << " seconds at start" << endl;
    cout << "  " << ANSI_GREEN;
    if (remainSecs < 10) cout << "🯰";
    if (remainSecs < 100) cout << "🯰";
    if (remainSecs < 1000) cout << "🯰";
    if (remainSecs < 10000) cout << "🯰";
    cout << segmentDisplay(remainSecs) << ANSI_RESET << " seconds remaining" << endl;
}

