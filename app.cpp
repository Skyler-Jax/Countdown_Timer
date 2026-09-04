/***************************
 * Console Countdown Timer *
 *     Version 1.2.0       *
 *  by Skyler Jax Hansen   *
 *     Sep. 4th, 2026      *
 ***************************/

#include "variables.h"
#include "functions.h"
#include <iostream>
#include <chrono>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

using namespace std;
using namespace app;
using namespace display;
using namespace timer;

/*****************************
 * General Program Functions *
 *****************************/

// Step 1: Clear/initialize all variables to prepare for timer setup
//            (See variables.h for variable details)
////////////////////////////////////////////////////////////////////
void app::zeroVars() {
    hours           = 0;
    mins            = 0;
    secs            = 0;
    tickCount       = 0;
    clockHands      = 0;
    hours2Secs      = 0;
    mins2Secs       = 0;
    totalSecs       = 0;
    ringCount       = 2;
    timerEnabled    = true;
    appInitialized  = false;
    cleanStart      = true;
    timerHasExpired = false;
    timerWait       = true;
    hoursAreSet     = false;
    minsAreSet      = false;
    secsAreSet      = false;
    bypassGetNote   = false;
    showTimerNote   = false;
    iconColor       = false;
    colorSwitch     = false;
    input.clear();
    option.clear();
}

// Step 2a: Get time values from user and initialize timerCore()
////////////////////////////////////////////////////////////////
void app::initApp() {
    clearScreen(true);

    // Get hour value from user and calculate hour duration in seconds if bool flag is not set
    if (hoursAreSet == false) {
        hours = getHours();
    }
    if (!appInitialized) hours2Secs = hours * 60 * 60;

    // Get minute value from user and calculate minute duration in seconds if bool flag is not set
    if (minsAreSet == false) {
        mins = getMins();
    }
    if (!appInitialized) mins2Secs = mins * 60;

    // Get seconds value from user and calculate total entered timer duration in seconds if bool flag is not set
    if (secsAreSet == false) {
        secs = getSecs();
    }
    if (!appInitialized) totalSecs = hours2Secs + mins2Secs + secs;

    // Change icon timer color from white to green, indicates successful timer set routine
    iconColor = true;

    // Set flag indicating timer has been initialized
    appInitialized = true;

    clearScreen(false);
}

// Step 2b: Checks whether user entered valid positive integer to set time with
///////////////////////////////////////////////////////////////////////////////
bool app::checkInput(const string& input) {
    return !input.empty() && all_of(input.begin(), input.end(), [](unsigned char c) {
        return isdigit(c);
    });
}

// Step 3: Promp user for optional timer note/reminder
//////////////////////////////////////////////////////
void app::getNote() {

    // Bool flag used to activate second half of function
    bool noteIsSet = false;

    cout << " Attach note to timer? (Y/N)" << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> option;

    /*
     * Either sets flags to activate next step of function and to activate displayNote() while
     * timer is running, or continues through program loop if no note desired. Otherwise return
     * to start of this function if user input is invalid.
     */
    if (option == "Y" || option == "y") {
        noteIsSet = !noteIsSet;
        showTimerNote = !showTimerNote;
        option.clear();
        clearScreen(false);
    } else if (option == "N" || option == "n") {
        option.clear();
        clearScreen(false);
    } else {
        option.clear();
        clearScreen(false);
        getNote();
    }

    // If the flag was set by the previous step, get note body text from user
    if (noteIsSet == true) {
        cout << " Enter reminder/note for this timer:" << endl << TEXT_FG_BLUE << "   " << TEXT_RESET;
        cin.ignore();
        cin.get(note, 63);
        clearScreen(false);
    }
}

// Step 4: Pause after gathering information, wait for user to start timer
//////////////////////////////////////////////////////////////////////////
void app::wait2Start() {
    cout << " Timer set, press Enter to start..." << TEXT_FG_GREEN << TEXT_BLINK << "  " << TEXT_RESET;
    cin.ignore();
    cin.get();
}

// Step 5: Calculates appropriate bar segnemt:seconds ratio for progress bar
////////////////////////////////////////////////////////////////////////////
int app::calculateBarRatio() {
    int sum = 0;
    int ratio = 0;

    // Round up seconds used in bar ratio so the quotient is cleanly divisible
    {
    if (secs > 0 && secs < 10) sum = hours2Secs + mins2Secs + 10;
    if (secs > 10 && secs < 20) sum = hours2Secs + mins2Secs + 20;
    if (secs > 20 && secs < 30) sum = hours2Secs + mins2Secs + 30;
    if (secs > 30 && secs < 40) sum = hours2Secs + mins2Secs + 40;
    if (secs > 40 && secs < 50) sum = hours2Secs + mins2Secs + 50;
    if (secs > 50 && secs < 60) sum = hours2Secs + mins2Secs + 60;
    else sum = hours2Secs + mins2Secs + secs;
    }

    ratio = sum / 20;
    return ratio;
}

// Step 6a: Execute main timer functions from main() while loop
///////////////////////////////////////////////////////////////
void app::runTimer() {
    //Set up timer, sub-functions handle getting user input and calculating total timer seconds
    initApp();

    //Prompts user whether to add/enable optional note/reminder message
    if (!bypassGetNote) getNote();

    //Prompts user to start timer when setup completes successfully
    if (timerWait) wait2Start();

    //Runs the timer core logic; sub-functions increment/decrement counters and sync visual elements
    timerCore();
}

// Step 6b: Listen for keypress to pause active timer
////////////////////////////////////////////
bool app::pauseTimer() {

    // Windows implementation
    #ifdef _WIN32
    if (_kbhit()) {
        _getch();
        return true;
    }
    return false;

    // *nix implementation
    #else
    struct termios oldt, newt;
    int ch;
    int oldf;

    // 1. Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // 2. Disable canonical mode (buffering) and local echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    // 3. Set standard input to non-blocking mode
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    // 4. Restore terminal settings immediately
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    // If a character was successfully pulled from the stream, a key was hit
    if(ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }

    return false;
    #endif
}

// Step 7a: Handle timer reset or program exit after expiration
///////////////////////////////////////////////////////////////
void app::resetTimer() {
    cout << " R to   or Q to  " << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> option;

    // Process user input to reset or quit program
    if (option == "Q" || option == "q") {
        programActive = !programActive;
        cout << CONSOLE_CLEAR << flush;
        return;
    } else if (option == "R" || option == "r") {
        zeroVars();
        runTimer();
    } else {
        option.clear();
        clearScreen(false);
        ringCount = 0;
        timerExpired();
    }
}

// Step 7b: Handle timer restart or program exit after pausing
//////////////////////////////////////////////////////////////
void app::restartTimer() {
    cout << " R to   or Q to  " << endl << TEXT_FG_AMBER << "   " << TEXT_RESET << CURSOR_SHOW;
    cin >> option;

    // Clear the leftover newline character from the input buffer
    cin.ignore(256, '\n');

    // Process user input to restart or quit program
    if (option == "Q" || option == "q") {
        programActive = !programActive;
        cout << CONSOLE_CLEAR << flush;
    } else if (option == "R" || option == "r") {
        timerEnabled = true;
        timerCore();
    } else {
        option.clear();
        clearScreen(false);
        timerPaused();
    }
}
