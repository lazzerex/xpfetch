/*
 * kernel version information
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

void get_kernel_info(char *buffer, size_t size) {
    OSVERSIONINFOEXA osvi;
    
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXA));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);
    
    #pragma warning(push)
    #pragma warning(disable: 4996)
    if (GetVersionExA((OSVERSIONINFOA*)&osvi)) {
        sprintf(buffer, "NT %lu.%lu (Build %lu)", 
               osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
    } else {
        strcpy(buffer, "Unknown");
    }
    #pragma warning(pop)
}
