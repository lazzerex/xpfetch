/*
 * system uptime information
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>

void get_uptime_info(char *buffer, size_t size) {
    DWORD uptime_ms;
    DWORD uptime_sec;
    DWORD days, hours, minutes;
    
    uptime_ms = GetTickCount();
    uptime_sec = uptime_ms / 1000;
    
    /* calculate time components */
    days = uptime_sec / 86400;
    uptime_sec %= 86400;
    hours = uptime_sec / 3600;
    uptime_sec %= 3600;
    minutes = uptime_sec / 60;
    
    if (days > 0) {
        sprintf(buffer, "%lu days, %lu hours, %lu mins", days, hours, minutes);
    } else if (hours > 0) {
        sprintf(buffer, "%lu hours, %lu mins", hours, minutes);
    } else {
        sprintf(buffer, "%lu mins", minutes);
    }
}
