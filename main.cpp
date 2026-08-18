#include "functions.h"
#include <iostream>

int retHours;
int retMins;
int totalSecs;
int hours2Secs;
int mins2Secs;

int main()
{
    screen::clearScreen();
    screen::headerDisp();
    retHours = timer::getHours();
    hours2Secs = retHours * 60 * 60;
    retMins = timer::getMins();
    mins2Secs = retMins * 60;
    totalSecs = hours2Secs + mins2Secs;
    screen::wait2Start();
    timer::timerCore(totalSecs);
    screen::timerElapsed();
    return 0;
}
