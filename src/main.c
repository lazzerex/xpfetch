#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "logo.h"
#include "console.h"
#include "config.h"
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

static void append_info_line(const char **info_lines, int *info_count, const char *label, const char *value) {
    char buffer[256];

    sprintf(buffer, "%s: %s", label, value);
    info_lines[*info_count] = xp_strdup(buffer);
    (*info_count)++;
}

static void append_blank_line(const char **info_lines, int *info_count) {
    info_lines[*info_count] = xp_strdup("");
    (*info_count)++;
}

static void select_logo(const XPFetchConfig *config, const char ***logo_lines, int *logo_count) {
    if (strcmp(config->logo, "w2k") == 0) {
        *logo_lines = w2k_logo;
        *logo_count = w2k_logo_lines;
    } else if (strcmp(config->logo, "win") == 0) {
        *logo_lines = win_logo;
        *logo_count = win_logo_lines;
    } else if (strcmp(config->logo, "ascii") == 0 || strcmp(config->logo, "fallback") == 0) {
        *logo_lines = win_ascii_logo;
        *logo_count = win_ascii_logo_lines;
    } else {
        *logo_lines = xp_logo;
        *logo_count = xp_logo_lines;
    }
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

void print_layout(const char **logo_lines, int logo_count, SystemInfo *info, const XPFetchConfig *config) {
    const char *info_lines[MAX_INFO_LINES];
    int info_count = 0;
    int i, max_lines;

    if (config->show_os) {
        append_info_line(info_lines, &info_count, "OS", info->os);
    }

    if (config->show_host) {
        append_info_line(info_lines, &info_count, "Host", info->hostname);
    }

    if (config->show_kernel) {
        append_info_line(info_lines, &info_count, "Kernel", info->kernel);
    }

    if (config->show_uptime) {
        append_info_line(info_lines, &info_count, "Uptime", info->uptime);
    }

    if (config->show_shell) {
        append_info_line(info_lines, &info_count, "Shell", info->shell);
    }

    if (config->show_resolution) {
        append_info_line(info_lines, &info_count, "Resolution", info->resolution);
    }

    if ((config->show_cpu || config->show_gpu || config->show_memory) && info_count > 0) {
        append_blank_line(info_lines, &info_count);
    }

    if (config->show_cpu) {
        append_info_line(info_lines, &info_count, "CPU", info->cpu);
    }

    if (config->show_gpu) {
        append_info_line(info_lines, &info_count, "GPU", info->gpu);
    }

    if (config->show_memory) {
        append_info_line(info_lines, &info_count, "Memory", info->memory);
    }

    if (config->show_disk) {
        if (info_count > 0) {
            append_blank_line(info_lines, &info_count);
        }

        append_info_line(info_lines, &info_count, "Disk (C:)", info->disk);
    }
    
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
    XPFetchConfig config;
    SystemInfo info;
    const char **logo_lines;
    int logo_count;
    
    init_console();
    config_init(&config);
    load_config(&config, "xpfetch.conf");
    fetch_system_info(&info);
    select_logo(&config, &logo_lines, &logo_count);
    print_layout(logo_lines, logo_count, &info, &config);
    
    return 0;
}
