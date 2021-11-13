/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * timezon.c - Set proper timezone needed by newlib.
 *
 * Copyright (c) 2021 Francisco Javier Trujillo Mata <fjtrujy@gmail.com>
 *
 */

#include <psputility_sysparam.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef F___timezone_update
__attribute__((weak))
void __timezone_update()
{
    /* Initialize timezone from PSP configuration */
    int tzOffset = 0;
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_TIMEZONE, &tzOffset);
    int tzOffsetAbs = tzOffset < 0 ? -tzOffset : tzOffset;
    int hours = tzOffsetAbs / 60;
    int minutes = tzOffsetAbs - hours * 60;
    int pspDaylight = 0;
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_DAYLIGHTSAVINGS, &pspDaylight);
    static char tz[18];
    sprintf(tz, "GMT%s%02i:%02i%s", tzOffset < 0 ? "+" : "-", hours, minutes, pspDaylight ? "daylight" : "");
    setenv("TZ", tz, 1);
}
#endif