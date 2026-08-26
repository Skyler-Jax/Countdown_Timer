/***************************
 * Console Countdown Timer *
 *     Version 1.1.5       *
 *  by Skyler Jax Hansen   *
 *     Aug. 25th, 2026     *
 ***************************/

/********************
 * Screen Functions *
 ********************/
#include "variables.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace app;

//Clears console, initiates redrawing program header and timer display
//////////////////////////////////////////////////////////////////////
void display::clearScreen(bool timerSetMode)
{
    cout << CONSOLE_CLEAR << CURSOR_HIDE << flush;
    displayHeader();
    displayClock(hours, mins, secs, clockHands, timerSetMode, hoursAreSet, minsAreSet, secsAreSet, iconColor);
}

//Called by clearScreen(), redraws header
///////////////////////////////////////
void display::displayHeader()
{
    cout << TEXT_BG_SLATE;
    cout << TEXT_FG_AMBER;
    cout << " ╭─────────────────────────╮ " << endl;
    cout << " │ ";
    cout << TEXT_FG_MGNTA << "Console Countdown Clock";
    cout << TEXT_FG_AMBER << " │ " << endl;
    cout << " │  ";
    cout << TEXT_FG_GREEN << "ⓑⓨ🅢ⓚⓨⓛⓔⓡ🅙ⓐⓧ🅗ⓐⓝⓢⓔⓝ🄌🄯⓴㉖";
    cout << TEXT_FG_AMBER << " │ " << endl;
    cout << " ╰─────────────────────────╯ " << endl;
    cout << TEXT_RESET;
}

//Called by clearScreen(), redraws current timer
////////////////////////////////////////////////
void display::displayClock(int hr, int min, int sec, int iconSelect, bool flashClock, bool hoursSet, bool minsSet, bool secsSet, bool iconColor)
{
    cout << " Countdown clock: ";
    cout << statusIcon(iconSelect) << endl;
    if (iconColor == true) {
        if (colorSwitch == true) cout << TEXT_FG_YELLW << "  ";
        else cout << TEXT_FG_GREEN << "  ";
    }
    else cout <<  "  ";
    cout << TEXT_BG_SLATE;
    if (flashClock == true) cout << TEXT_BLINK;
    cout << TEXT_FG_GREEN;
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
    cout << TEXT_RESET;
}

//Shows progress bar
////////////////////
void display::displayProgress(bool timerDone, int barPercent)
{
    cout << "   Elapsed duration: ";
    if (barPercent < 10) cout << " ";
    if (barPercent < 100) cout << " ";
    cout << barPercent << "%" << endl;
    cout <<  "   ⦗";
    for (int i = 0; i < 20; i++) {
        if (timerDone == false) {
            if (i < barPercent / 5) cout << TEXT_FG_GREEN << "🞅";
            else cout << TEXT_FG_AMBER << "🞄";
        }
        if (timerDone == true) cout << TEXT_FG_GREEN << "⨁";
    }
    cout << TEXT_RESET << "⦘" << endl;
}

//Shows total starting and remaining seconds while timer active
///////////////////////////////////////////////////////////////
void display::displaySecs(int startSecs, int remainSecs)
{
    cout << TEXT_FG_BLUE << "  " << TEXT_FG_GREEN << TEXT_BG_SLATE;
    if (startSecs < 10) cout << "🯰";
    if (startSecs < 100) cout << "🯰";
    if (startSecs < 1000) cout << "🯰";
    if (startSecs < 10000) cout << "🯰";
    cout << segmentDisplay(startSecs) << TEXT_RESET << " seconds at start" << endl;
    cout << TEXT_FG_BLUE << "  ";
    if (startSecs < 3600) {
        if (remainSecs < (startSecs * 0.25)) cout << TEXT_FG_RED << TEXT_BG_SLATE;
        else if (remainSecs < (startSecs * 0.5)) cout << TEXT_FG_YELLW << TEXT_BG_SLATE;
        else cout << TEXT_FG_GREEN << TEXT_BG_SLATE;
    }
    else {
        if (remainSecs < 60) cout << TEXT_FG_RED << TEXT_BG_SLATE;
        else if (remainSecs < 300) cout << TEXT_FG_YELLW << TEXT_BG_SLATE;
        else cout << TEXT_FG_GREEN << TEXT_BG_SLATE;
    }
    if (remainSecs < 10) cout << "🯰";
    if (remainSecs < 100) cout << "🯰";
    if (remainSecs < 1000) cout << "🯰";
    if (remainSecs < 10000) cout << "🯰";
    cout << segmentDisplay(remainSecs) << TEXT_RESET << " seconds remaining" << endl;
}

//Displays optional note/reminder while timer is running
////////////////////////////////////////////////////////
void display::displayNote()
{
    if (showTimerNote == true) cout << endl << " Timer note:" << endl << TEXT_BG_SLATE << TEXT_FG_YELLW << "  " << note << " " << TEXT_RESET << endl << endl;
}

//Displays timer expired message and handles ringing terminal bell
//////////////////////////////////////////////////////////////////
void display::timerExpired()
{
    cout << "   Timer has expired!  " << endl << endl;
    for (int ringCount = 0; ringCount < 2; ringCount++) {
        for (int bellCount = 0; bellCount < 4; bellCount++) {
            cout << "\a" << flush;
            this_thread::sleep_for(chrono::milliseconds(125));;
        }
        this_thread::sleep_for(chrono::milliseconds(750));
    }
}

//Returns status icon from look-up array
////////////////////////////////////////
string display::statusIcon(int input)
{
    const string icons[] = {
        "🖮", "🕐", "🕑", "🕒", "🕓",
        "🕔", "🕕", "🕖", "🕗", "🕘",
        "🕙", "🕚", "🕛", "✅"
    };
    string iconReturn = icons[input];
    return iconReturn;
}

//Returns sylized digit symbol from ASCII numeral translation
/////////////////////////////////////////////////////////////
string display::segmentDisplay(int input)
{
    const string digits[] = {
        "🯰", "🯱", "🯲", "🯳", "🯴",
        "🯵", "🯶", "🯷", "🯸", "🯹"
    };
    string numStr = to_string(abs(input));
    string translation;
    translation.reserve(numStr.length() * 4);
    for (char digit : numStr) {
        translation += digits[digit - '0'];
    }
    return translation;
}
