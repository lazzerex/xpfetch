/*
 * disk space information for all fixed and removable drives
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

int get_disk_info(DiskEntry *entries, int max_entries) {
    ULARGE_INTEGER free_bytes;
    ULARGE_INTEGER total_bytes;
    ULARGE_INTEGER used_bytes;
    DWORD drives = GetLogicalDrives();
    UINT old_mode = SetErrorMode(SEM_FAILCRITICALERRORS);
    char root[4] = "A:\\";
    char used_str[32];
    char total_str[32];
    UINT type;
    int count = 0;
    int i;

    for (i = 0; i < 26 && count < max_entries; i++) {
        if (!(drives & (1UL << i))) {
            continue;
        }

        root[0] = (char)('A' + i);
        type = GetDriveTypeA(root);
        if (type != DRIVE_FIXED && type != DRIVE_REMOVABLE) {
            continue;
        }

        if (!GetDiskFreeSpaceExA(root, &free_bytes, &total_bytes, NULL) ||
            total_bytes.QuadPart == 0) {
            continue;
        }

        used_bytes.QuadPart = total_bytes.QuadPart - free_bytes.QuadPart;
        format_bytes(used_bytes, used_str, sizeof(used_str));
        format_bytes(total_bytes, total_str, sizeof(total_str));

        sprintf(entries[count].drive, "%c:", root[0]);
        sprintf(entries[count].usage, "%s / %s", used_str, total_str);
        count++;
    }

    SetErrorMode(old_mode);
    return count;
}
