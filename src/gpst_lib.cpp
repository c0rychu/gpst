#include <iostream>
#include <time.h>
#include "gpst_leaps.h"
#include "gpst_lib.h"


time_t
unix2gps(time_t unixTime)
{
    return unixTime+leapShift(unixTime)-gps0;
}


time_t
gps2unix(time_t gpsTime)
{
    time_t unixTime = gpsTime+gps0-leapShift(gpsTime+gps0);
    if ( gpsTime == unix2gps(unixTime) || gpsTime != unix2gps(unixTime+1) ) {
        return unixTime;
    } else {
        return unixTime+1;
    }
}


time_t
leapShift(time_t unixTime)
{
    if (unixTime < gps0){     // gpstime < 0
        throw std::invalid_argument( "gpstime < 0" );
    } else {
        int i;
        for (i=0; i<N_LEAPS; ++i) {
            if (leaps[i] > unixTime) {
                return i;
            }
        } 
        return i;
    }
}

