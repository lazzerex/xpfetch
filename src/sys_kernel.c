/*
 * kernel version information
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

void get_kernel_info(char *buffer, size_t size) {
    unsigned long major, minor, build;
    
    if (get_nt_version(&major, &minor, &build)) {
        sprintf(buffer, "NT %lu.%lu (Build %lu)", major, minor, build);
    } else {
        strcpy(buffer, "Unknown");
    }
}
