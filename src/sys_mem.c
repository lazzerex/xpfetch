/*
 * memory information detection
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>

typedef BOOL (WINAPI *PGLOBALMEMORYSTATUSEX)(LPMEMORYSTATUSEX);

static void format_bytes(DWORDLONG bytes, char *buffer, size_t size) {
    double kb = bytes / 1024.0;
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

void get_memory_info(char *buffer, size_t size) {
    HMODULE hKernel32;
    PGLOBALMEMORYSTATUSEX pGlobalMemoryStatusEx;
    MEMORYSTATUSEX memInfo;
    MEMORYSTATUS oldMemInfo;
    char total_str[32];
    char used_str[32];
    DWORDLONG used_memory;
    BOOL success = FALSE;
    
    /* Try to load GlobalMemoryStatusEx dynamically for XP compatibility */
    hKernel32 = GetModuleHandleA("kernel32.dll");
    if (hKernel32) {
        pGlobalMemoryStatusEx = (PGLOBALMEMORYSTATUSEX)GetProcAddress(hKernel32, "GlobalMemoryStatusEx");
        if (pGlobalMemoryStatusEx) {
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            if (pGlobalMemoryStatusEx(&memInfo)) {
                used_memory = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
                format_bytes(used_memory, used_str, sizeof(used_str));
                format_bytes(memInfo.ullTotalPhys, total_str, sizeof(total_str));
                sprintf(buffer, "%s / %s", used_str, total_str);
                success = TRUE;
            }
        }
    }
    
    /* Fallback to GlobalMemoryStatus for older XP versions */
    if (!success) {
        oldMemInfo.dwLength = sizeof(MEMORYSTATUS);
        GlobalMemoryStatus(&oldMemInfo);
        
        used_memory = oldMemInfo.dwTotalPhys - oldMemInfo.dwAvailPhys;
        
        format_bytes(used_memory, used_str, sizeof(used_str));
        format_bytes(oldMemInfo.dwTotalPhys, total_str, sizeof(total_str));
        
        sprintf(buffer, "%s / %s", used_str, total_str);
    }
}
