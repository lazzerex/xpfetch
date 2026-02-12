/*
 * system information function declarations
 */

#ifndef SYSINFO_H
#define SYSINFO_H

#include <stddef.h>

void get_os_info(char *buffer, size_t size);
void get_kernel_info(char *buffer, size_t size);
void get_cpu_info(char *buffer, size_t size);
void get_gpu_info(char *buffer, size_t size);
void get_memory_info(char *buffer, size_t size);
void get_uptime_info(char *buffer, size_t size);
void get_shell_info(char *buffer, size_t size);
void get_disk_info(char *buffer, size_t size);
void get_display_info(char *buffer, size_t size);
void get_hostname_info(char *buffer, size_t size);
void get_username_info(char *buffer, size_t size);

#endif /* SYSINFO_H */
