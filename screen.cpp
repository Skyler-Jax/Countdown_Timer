#include "functions.h"
#include <iostream>

void screen::clearScreen()
{
    std::cout << "\033[2J\033[H" << std::flush;
}

void screen::headerDisp()
{
    std::cout << "---------------------------" << std::endl;
    std::cout << "| Console Countdown Timer |" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "   by Skyler Jax Hansen    " << std::endl << std::endl;
}

void screen::wait2Start()
{
    std::cout << "Press Enter to start timer..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void screen::timerElapsed()
{
    screen::clearScreen();
    screen::headerDisp();
    std::cout << "Timer has elapsed!" << std::endl;
}
