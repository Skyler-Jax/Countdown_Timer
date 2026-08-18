#pragma once

namespace timer {
    int getHours();
    int getMins();
    int getSecs();
    void timerClock();
    void timerCore(int timerSecs);
}

namespace screen {
    void clearScreen();
    void displayHeader();
    void displayClock(int hr, int min, int sec);
    void displaySecs(int totalSecs);
    void wait2Start();
    void timerElapsed();
}
