/*
 * CPU information detection using CPUID
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

#if defined(_MSC_VER)
    #include <intrin.h>
    #define cpuid(info, x) __cpuid(info, x)
    #define cpuidex(info, x, y) __cpuidex(info, x, y)
#else
    static void cpuid(int info[4], int function_id) {
        __asm__ volatile (
            "cpuid"
            : "=a" (info[0]), "=b" (info[1]), "=c" (info[2]), "=d" (info[3])
            : "a" (function_id), "c" (0)
        );
    }
#endif

static void get_cpu_brand_string(char *brand, size_t size) {
    int cpu_info[4] = {0};
    char temp_brand[49] = {0};
    int i;
    
    cpuid(cpu_info, 0x80000000);
    
    if ((unsigned int)cpu_info[0] < 0x80000004) {
        strcpy(brand, "Unknown CPU");
        return;
    }
    
    cpuid((int*)(temp_brand + 0), 0x80000002);
    cpuid((int*)(temp_brand + 16), 0x80000003);
    cpuid((int*)(temp_brand + 32), 0x80000004);
    
    temp_brand[48] = '\0';
    
    i = 0;
    while (temp_brand[i] == ' ' && temp_brand[i] != '\0') {
        i++;
    }
    
    strncpy(brand, temp_brand + i, size - 1);
    brand[size - 1] = '\0';
}

static void get_cpu_vendor(char *vendor, size_t size) {
    int cpu_info[4] = {0};
    char temp_vendor[13] = {0};
    
    cpuid(cpu_info, 0);
    
    memcpy(temp_vendor + 0, &cpu_info[1], 4);
    memcpy(temp_vendor + 4, &cpu_info[3], 4);
    memcpy(temp_vendor + 8, &cpu_info[2], 4);
    temp_vendor[12] = '\0';
    
    strncpy(vendor, temp_vendor, size - 1);
    vendor[size - 1] = '\0';
}

void get_cpu_info(char *buffer, size_t size) {
    char brand[64];
    char vendor[16];
    char *cpu_pos, *at_pos;
    SYSTEM_INFO sysInfo;
    
    get_cpu_brand_string(brand, sizeof(brand));
    
    if (strlen(brand) == 0 || strcmp(brand, "Unknown CPU") == 0) {
        get_cpu_vendor(vendor, sizeof(vendor));
        GetSystemInfo(&sysInfo);
        sprintf(buffer, "%s (%u cores)", vendor, sysInfo.dwNumberOfProcessors);
    } else {
        GetSystemInfo(&sysInfo);
        
        /* Remove " CPU" from brand string */
        cpu_pos = strstr(brand, " CPU");
        if (cpu_pos != NULL) {
            *cpu_pos = '\0';
        }
        
        /* Remove "@" and everything after it */
        at_pos = strstr(brand, " @");
        if (at_pos != NULL) {
            *at_pos = '\0';
        }
        
        sprintf(buffer, "%s (%u core%s)", brand, 
                sysInfo.dwNumberOfProcessors,
                sysInfo.dwNumberOfProcessors > 1 ? "s" : "");
    }
}
