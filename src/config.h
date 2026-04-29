/*
 * XPFetch configuration
 */

#ifndef XPFETCH_CONFIG_H
#define XPFETCH_CONFIG_H

typedef struct {
    int show_os;
    int show_host;
    int show_kernel;
    int show_uptime;
    int show_shell;
    int show_resolution;
    int show_cpu;
    int show_gpu;
    int show_memory;
    int show_disk;
    char logo[16];
} XPFetchConfig;

void config_init(XPFetchConfig *config);
int load_config(XPFetchConfig *config, const char *path);

#endif /* XPFETCH_CONFIG_H */