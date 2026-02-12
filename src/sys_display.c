/*
 * display resolution information
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>

void get_display_info(char *buffer, size_t size) {
    DEVMODEA dm;
    int refresh_rate;
    
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);
    
    if (EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
        refresh_rate = dm.dmDisplayFrequency;
        
        if (refresh_rate > 0) {
            sprintf(buffer, "%lux%lu @ %luHz", 
                   dm.dmPelsWidth, dm.dmPelsHeight, refresh_rate);
        } else {
            sprintf(buffer, "%lux%lu", 
                   dm.dmPelsWidth, dm.dmPelsHeight);
        }
    } else {
        int width = GetSystemMetrics(SM_CXSCREEN);
        int height = GetSystemMetrics(SM_CYSCREEN);
        
        sprintf(buffer, "%dx%d", width, height);
    }
}
