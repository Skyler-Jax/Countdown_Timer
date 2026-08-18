#include "functions.h"
#include <iostream>
#include <chrono>
#include <thread>

int hours = 0;
int mins = 0;
int secs = 0;
int clockTick = 0;

int timer::getHours()
{
    std::cout << "Enter timer hours:" << std::endl;
    std::cin >> hours;
    screen::clearScreen();
    screen::displayHeader();
    screen::displayClock(hours, mins, secs);
    return hours;
}

int timer::getMins()
{
    std::cout << "Enter timer minutes:" << std::endl;
    std::cin >> mins;
    if (mins > 59 || mins < 0) {
        timer::getMins();
    }
    screen::clearScreen();
    screen::displayHeader();
    screen::displayClock(hours, mins, secs);
    return mins;
}

int timer::getSecs()
{
    std::cout << "Enter timer seconds:" << std::endl;
    std::cin >> secs;
    if (secs > 59 || secs < 0) {
        timer::getSecs();
    }
    screen::clearScreen();
    screen::displayHeader();
    screen::displayClock(hours, mins, secs);
    return secs;
}

void timer::timerClock()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
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

void timer::timerCore(int timerSecs)
{
    while (timerSecs >= 0) {
        screen::clearScreen();
        screen::displayHeader();
        screen::displayClock(hours, mins, secs);
        screen::displaySecs(timerSecs);
        timer::timerClock();
        timerSecs--;
        continue;
    }
    screen::clearScreen();
    screen::displayHeader();
    screen::displayClock(0, 0, 0);
}
