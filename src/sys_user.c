/*
 * user and hostname information
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>

void get_hostname_info(char *buffer, size_t size) {
    DWORD buf_size = (DWORD)size;
    
    if (!GetComputerNameA(buffer, &buf_size)) {
        strcpy(buffer, "Unknown");
    }
}

void get_username_info(char *buffer, size_t size) {
    DWORD buf_size = (DWORD)size;
    
    if (!GetUserNameA(buffer, &buf_size)) {
        strcpy(buffer, "Unknown");
    }
}
