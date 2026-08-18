#include "functions.h"
#include <iostream>

int retHours;
int retMins;
int retSecs;
int totalSecs;
int hours2Secs;
int mins2Secs;

int main()
{
    screen::clearScreen();
    screen::displayHeader();
    screen::displayClock(0, 0, 0);
    retHours = timer::getHours();
    hours2Secs = retHours * 60 * 60;
    retMins = timer::getMins();
    mins2Secs = retMins * 60;
    retSecs = timer::getSecs();
    totalSecs = hours2Secs + mins2Secs + retSecs;
    screen::wait2Start();
    timer::timerCore(totalSecs);
    screen::timerElapsed();
    return 0;
}
