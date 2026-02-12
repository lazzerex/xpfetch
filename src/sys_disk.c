/*
 * disk space information for system drive
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

static void format_bytes(ULARGE_INTEGER bytes, char *buffer, size_t size) {
    double kb = bytes.QuadPart / 1024.0;
    double mb = kb / 1024.0;
    double gb = mb / 1024.0;
    
    if (gb >= 1.0) {
        sprintf(buffer, "%.2f GB", gb);
    } else if (mb >= 1.0) {
        sprintf(buffer, "%.0f MB", mb);
    } else {
        sprintf(buffer, "%.0f KB", kb);
    }
}

void get_disk_info(char *buffer, size_t size) {
    ULARGE_INTEGER free_bytes;
    ULARGE_INTEGER total_bytes;
    ULARGE_INTEGER used_bytes;
    char system_path[MAX_PATH];
    char system_drive[4];
    char free_str[32];
    char total_str[32];
    
    /* Get Windows directory path (e.g., "C:\Windows") */
    if (GetWindowsDirectoryA(system_path, sizeof(system_path)) > 0) {
        /* Extract drive letter (e.g., "C:\") */
        system_drive[0] = system_path[0];
        system_drive[1] = ':';
        system_drive[2] = '\\';
        system_drive[3] = '\0';
    } else {
        /* Fallback to C: drive */
        strcpy(system_drive, "C:\\");
    }
    
    if (GetDiskFreeSpaceExA(system_drive, &free_bytes, &total_bytes, NULL)) {
        used_bytes.QuadPart = total_bytes.QuadPart - free_bytes.QuadPart;
        
        format_bytes(used_bytes, free_str, sizeof(free_str));
        format_bytes(total_bytes, total_str, sizeof(total_str));
        
        sprintf(buffer, "%s / %s (%s)", free_str, total_str, system_drive);
    } else {
        strcpy(buffer, "Unknown");
    }
}
