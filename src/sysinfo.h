/*
 * system information function declarations
 */

#ifndef SYSINFO_H
#define SYSINFO_H

#include <stddef.h>

#define MAX_DISKS 26

typedef struct {
    char drive[4];
    char usage[72];
} DiskEntry;

int get_nt_version(unsigned long *major, unsigned long *minor, unsigned long *build);
void get_os_info(char *buffer, size_t size);
void get_kernel_info(char *buffer, size_t size);
void get_cpu_info(char *buffer, size_t size);
void get_gpu_info(char *buffer, size_t size);
void get_memory_info(char *buffer, size_t size);
void get_uptime_info(char *buffer, size_t size);
void get_shell_info(char *buffer, size_t size);
int get_disk_info(DiskEntry *entries, int max_entries);
void get_display_info(char *buffer, size_t size);
void get_hostname_info(char *buffer, size_t size);
void get_username_info(char *buffer, size_t size);

#endif /* SYSINFO_H */
