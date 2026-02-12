/*
 * shell information
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

void get_shell_info(char *buffer, size_t size) {
    char *comspec = getenv("COMSPEC");
    
    if (comspec != NULL) {
        char *last_slash = strrchr(comspec, '\\');
        if (last_slash != NULL) {
            snprintf(buffer, size, "%s", last_slash + 1);
        } else {
            snprintf(buffer, size, "%s", comspec);
        }
    } else {
        strcpy(buffer, "cmd.exe");
    }
}
