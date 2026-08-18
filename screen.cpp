#include "functions.h"
#include <iostream>

void screen::clearScreen()
{
    std::cout << "\033[2J\033[H" << std::flush;
}

void screen::displayHeader()
{
    std::cout << "---------------------------" << std::endl;
    std::cout << "| Console Countdown Timer |" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "   by Skyler Jax Hansen    " << std::endl << std::endl;
}

void screen::displayClock(int hr, int min, int sec)
{
    std::cout << "Countdown clock:" << std::endl;
    if (hr < 10) std::cout << "0";
    std::cout << hr << ":";
    if (min < 10) std::cout << "0";
    std::cout << min << ":";
    if (sec < 10) std::cout << "0";
    std::cout << sec << std::endl << std::endl;
}

void screen::displaySecs(int totalSecs)
{
    std::cout << totalSecs << " total seconds remaining." << std::endl;
}


void screen::wait2Start()
{
    std::cout << "Press Enter to start timer..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void screen::timerElapsed()
{
    std::cout << "Timer has expired!" << std::endl;
}
