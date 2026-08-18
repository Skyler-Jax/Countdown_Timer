#include "functions.h"
#include <iostream>
#include <chrono>
#include <thread>

int hours = 0;
int mins = 60;
int secs = 0;
int clockTick = 0;

int timer::getHours()
{
    std::cout << "Enter duration hours:" << std::endl;
    std::cin >> hours;
    return hours;
}

int timer::getMins()
{
    std::cout << "Enter duration minutes:" << std::endl;
    std::cin >> mins;
    if (mins > 59 || mins < 0) {
        std::cout << "Invalid input, enter 0-59 minutes.\n" << std::endl;
        getMins();
    }
    return mins;
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
        screen::headerDisp();
        std::cout << timerSecs << " Total seconds remaining." << std::endl << std::endl;
        std::cout << "Countdown clock:" << std::endl;
        if (hours < 10) std::cout << "0";
        std::cout << hours << ":";
        if (mins < 10) std::cout << "0";
        std::cout << mins << ":";
        if (secs < 10) std::cout << "0";
        std::cout << secs << std::endl << std::endl;
        timer::timerClock();
        timerSecs--;
        continue;
    }
}
