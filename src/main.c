#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "logo.h"
#include "console.h"
#include "sysinfo.h"

#define MAX_INFO_LINES 25
#define LOGO_WIDTH 20

static char* xp_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *dup = malloc(len);
    if (dup) {
        memcpy(dup, str, len);
    }
    return dup;
}

typedef struct {
    char os[128];
    char kernel[64];
    char hostname[64];
    char username[64];
    char uptime[64];
    char shell[64];
    char resolution[32];
    char cpu[128];
    char gpu[128];
    char memory[64];
    char disk[64];
} SystemInfo;

void fetch_system_info(SystemInfo *info) {
    get_os_info(info->os, sizeof(info->os));
    get_kernel_info(info->kernel, sizeof(info->kernel));
    get_hostname_info(info->hostname, sizeof(info->hostname));
    get_username_info(info->username, sizeof(info->username));
    get_uptime_info(info->uptime, sizeof(info->uptime));
    get_shell_info(info->shell, sizeof(info->shell));
    get_display_info(info->resolution, sizeof(info->resolution));
    get_cpu_info(info->cpu, sizeof(info->cpu));
    get_gpu_info(info->gpu, sizeof(info->gpu));
    get_memory_info(info->memory, sizeof(info->memory));
    get_disk_info(info->disk, sizeof(info->disk));
}

void print_layout(const char **logo_lines, int logo_count, SystemInfo *info) {
    const char *info_lines[MAX_INFO_LINES];
    int info_count = 0;
    char buffer[256];
    int i, max_lines;
    
    sprintf(buffer, "OS: %s", info->os);
    info_lines[info_count++] = xp_strdup(buffer);
    
    sprintf(buffer, "Host: %s", info->hostname);
    info_lines[info_count++] = xp_strdup(buffer);
    
    sprintf(buffer, "Kernel: %s", info->kernel);
    info_lines[info_count++] = xp_strdup(buffer);
    
    sprintf(buffer, "Uptime: %s", info->uptime);
    info_lines[info_count++] = xp_strdup(buffer);
    
    sprintf(buffer, "Shell: %s", info->shell);
    info_lines[info_count++] = xp_strdup(buffer);
    
    sprintf(buffer, "Resolution: %s", info->resolution);
    info_lines[info_count++] = xp_strdup(buffer);
    
    info_lines[info_count++] = xp_strdup("");
    
    sprintf(buffer, "CPU: %s", info->cpu);
    info_lines[info_count++] = xp_strdup(buffer);
    
    sprintf(buffer, "GPU: %s", info->gpu);
    info_lines[info_count++] = xp_strdup(buffer);
    
    sprintf(buffer, "Memory: %s", info->memory);
    info_lines[info_count++] = xp_strdup(buffer);
    
    info_lines[info_count++] = xp_strdup("");
    
    sprintf(buffer, "Disk (C:): %s", info->disk);
    info_lines[info_count++] = xp_strdup(buffer);
    
    max_lines = (logo_count > info_count) ? logo_count : info_count;
    
    printf("\n");
    
    for (i = 0; i < max_lines; i++) {
        if (i < logo_count) {
            set_console_color(LOGO_COLOR);
            printf("%-*s", LOGO_WIDTH, logo_lines[i]);
            reset_console_color();
        } else {
            printf("%-*s", LOGO_WIDTH, "");
        }
        
        printf("  ");
        
        if (i < info_count) {
            if (strlen(info_lines[i]) > 0) {
                char *colon = strchr(info_lines[i], ':');
                if (colon != NULL) {
                    size_t label_len = colon - info_lines[i];
                    set_console_color(LABEL_COLOR);
                    printf("%.*s:", (int)label_len, info_lines[i]);
                    reset_console_color();
                    printf("%s", colon + 1);
                } else {
                    printf("%s", info_lines[i]);
                }
            }
        }
        
        printf("\n");
    }
    
    printf("\n");
    
    for (i = 0; i < info_count; i++) {
        free((void*)info_lines[i]);
    }
}

int main(int argc, char *argv[]) {
    SystemInfo info;
    
    init_console();
    fetch_system_info(&info);
    print_layout(xp_logo, xp_logo_lines, &info);
    
    return 0;
}
