/*
 * GPU information detection
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

void get_gpu_info(char *buffer, size_t size) {
    DISPLAY_DEVICEA dd;
    int adapter_count = 0;
    char gpu_list[256] = "";
    DWORD i;
    
    ZeroMemory(&dd, sizeof(dd));
    dd.cb = sizeof(dd);
    
    for (i = 0; EnumDisplayDevicesA(NULL, i, &dd, 0); i++) {
        if (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) {
            strncpy(gpu_list, dd.DeviceString, sizeof(gpu_list) - 1);
            adapter_count = 1;
            break;
        }
    }
    
    if (adapter_count == 0) {
        for (i = 0; EnumDisplayDevicesA(NULL, i, &dd, 0); i++) {
            if (dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
                strncpy(gpu_list, dd.DeviceString, sizeof(gpu_list) - 1);
                break;
            }
        }
    }
    
    if (strlen(gpu_list) > 0) {
        strncpy(buffer, gpu_list, size - 1);
        buffer[size - 1] = '\0';
    } else {
        strcpy(buffer, "Unknown");
    }
}
