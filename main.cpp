/***************************
 * Console Countdown Timer *
 *     Version 1.1.0       *
 *  by Skyler Jax Hansen   *
 *     Aug. 19th, 2026     *
 ***************************/

#include "functions.h"

using namespace app;
using namespace timer;
using namespace display;

int main()
{
    initApp();
    while (programActive == true) {
        timerCore(totalSecs);
        timerExpired();
        timerReset();
    }
    return 0;
}
