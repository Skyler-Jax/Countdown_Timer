#pragma once

namespace timer {
    int getHours();
    int getMins();
    void timerClock();
    void timerCore(int timerSecs);
}

namespace screen {
    void clearScreen();
    void headerDisp();
    void wait2Start();
    void timerElapsed();
}
