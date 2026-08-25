/***************************
 * Console Countdown Timer *
 *     Version 1.1.4       *
 *  by Skyler Jax Hansen   *
 *     Aug. 21st, 2026     *
 ***************************/

#include "variables.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace app;
using namespace display;
using namespace timer;

/*****************************
 * General Program Functions *
 *****************************/
// Initialize/zero all app variables for clean timer restart
void app::zeroVars()
{
    hours = 0;
    mins = 0;
    secs = 0;
    tickCount = 0;
    clockHands = 0;
    hours2Secs = 0;
    mins2Secs = 0;
    totalSecs = 0;
    hoursAreSet = false;
    minsAreSet = false;
    secsAreSet = false;
    noteIsSet = false;
    showTimerNote = false;
    resetTimer = false;
    iconColor = false;
    colorSwitch = false;
    option.clear();
}

// Function that starts the program
void app::initApp()
{
    clearScreen(1);
    if (hoursAreSet == false) hours = getHours();
    hours2Secs = hours * 60 * 60;
    if (minsAreSet == false) mins = getMins();
    mins2Secs = mins * 60;
    if (secsAreSet == false) secs = getSecs();
    totalSecs = hours2Secs + mins2Secs + secs;
}

// Draw start message on screen and wait for Enter
void app::wait2Start()
{
    cout << " Timer set, press Enter to start..." << endl << ANSI_GREEN << "  " << ANSI_RESET;
    cin.ignore();
    cin.get();
}

// Get timer reminder note from console input
void app::getNote()
{
    cout << " Attach note to timer? (Y/N)" << endl << ANSI_YELLW << "   " << ANSI_RESET << ANSI_CSHOW;
    cin >> option;
    if (option == "Y" || option == "y") {
        noteIsSet = !noteIsSet;
        showTimerNote = !showTimerNote;
        option.clear();
        clearScreen(0);
    }
    else {
        option.clear();
        clearScreen(0);
    }
    if (noteIsSet == true) {
        cout << " Enter reminder/note for this timer:" << endl << ANSI_BLUE << "   " << ANSI_RESET;
        cin.ignore();
        cin.get(note, 63);
        clearScreen(0);
    }
}

// Draw timer reminder/note
void app::displayNote()
{
    if (showTimerNote == true) cout << endl << " Timer note:" << endl << ANSI_YELLW << "  " << ANSI_RESET << note << endl << endl;
}

// Draw timer complete notification on screen
void app::timerExpired()
{
    iconColor = false;
    cout << "   Timer has expired!  " << endl << endl;
    for (int ringCount = 0; ringCount < 2; ringCount++) {
        for (int bellCount = 0; bellCount < 4; bellCount++) {
            cout << "\a" << flush;
            this_thread::sleep_for(chrono::milliseconds(125));;
        }
        this_thread::sleep_for(chrono::milliseconds(750));
    }
}

// Reset timer or quit
void app::timerReset()
{
    cout << " R to   or Q to  " << endl << ANSI_YELLW << "   " << ANSI_RESET << ANSI_CSHOW;
    cin >> option;
    if (option == "Q" || option == "q") {
        programActive = !programActive;
        cout << ANSI_ERASE << flush;
    }
    else if (option == "R" || option == "r") {
        zeroVars();
        initApp();
    }
    else {
        option.clear();
        clearScreen(0);
        timerReset();
    }
}

// Check for valid numeric bool app::checkInput(const string& input)
bool app::checkInput(const string& input)
{
    return !input.empty() && all_of(input.begin(), input.end(), [](unsigned char c) {
        return isdigit(c);
    });
}

// Calculate progress bar step ratio from set duration
int app::calculateBarRatio()
{
    int sum = 0;
    int ratio = 0;
    if (secs > 0 && secs < 10) sum = hours2Secs + mins2Secs + 10;
    if (secs > 10 && secs < 20) sum = hours2Secs + mins2Secs + 20;
    if (secs > 20 && secs < 30) sum = hours2Secs + mins2Secs + 30;
    if (secs > 30 && secs < 40) sum = hours2Secs + mins2Secs + 40;
    if (secs > 40 && secs < 50) sum = hours2Secs + mins2Secs + 50;
    if (secs > 50 && secs < 60) sum = hours2Secs + mins2Secs + 60;
    else sum = hours2Secs + mins2Secs + secs;
    ratio = sum / 20;
    return ratio;
}

// Translate ASCII digits to segmented digits
string app::segmentDisplay(int input)
{
    const string symbols[] = {
        "🯰", "🯱", "🯲", "🯳", "🯴",
        "🯵", "🯶", "🯷", "🯸", "🯹"
    };
    string numStr = to_string(abs(input));
    string result;
    result.reserve(numStr.length() * 4);
    for (char digit : numStr) {
        result += symbols[digit - '0'];
    }
    return result;
}

