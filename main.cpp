/***************************
 * Console Countdown Timer *
 *     Version 1.1.4       *
 *  by Skyler Jax Hansen   *
 *     Aug. 21st, 2026     *
 ***************************/

#include "variables.h"
#include "functions.h"

using namespace app;
using namespace timer;
using namespace display;

int main()
{
    zeroVars();
    while (programActive == true) {
        initApp();
        getNote();
        wait2Start();
        timerCore(totalSecs);
        timerExpired();
        timerReset();
    }
    return 0;
}
