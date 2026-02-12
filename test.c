/*
 * test.c - Test suite for XPFetch components
 * 
 * This file can be used to test individual system info functions
 * without running the full program.
 * 
 * Build: gcc -o test.exe test.c src/*.c -D_WIN32_WINNT=0x0501
 */

#include <stdio.h>
#include <windows.h>
#include "src/sysinfo.h"
#include "src/console.h"

void test_os_info(void) {
    char buffer[256];
    printf("Testing OS Info...\n");
    get_os_info(buffer, sizeof(buffer));
    printf("  Result: %s\n\n", buffer);
}

void test_cpu_info(void) {
    char buffer[256];
    printf("Testing CPU Info...\n");
    get_cpu_info(buffer, sizeof(buffer));
    printf("  Result: %s\n\n", buffer);
}

void test_memory_info(void) {
    char buffer[256];
    printf("Testing Memory Info...\n");
    get_memory_info(buffer, sizeof(buffer));
    printf("  Result: %s\n\n", buffer);
}

void test_uptime_info(void) {
    char buffer[256];
    printf("Testing Uptime Info...\n");
    get_uptime_info(buffer, sizeof(buffer));
    printf("  Result: %s\n\n", buffer);
}

void test_disk_info(void) {
    char buffer[256];
    printf("Testing Disk Info...\n");
    get_disk_info(buffer, sizeof(buffer));
    printf("  Result: %s\n\n", buffer);
}

void test_display_info(void) {
    char buffer[256];
    printf("Testing Display Info...\n");
    get_display_info(buffer, sizeof(buffer));
    printf("  Result: %s\n\n", buffer);
}

void test_hostname_info(void) {
    char buffer[256];
    printf("Testing Hostname Info...\n");
    get_hostname_info(buffer, sizeof(buffer));
    printf("  Result: %s\n\n", buffer);
}

void test_username_info(void) {
    char buffer[256];
    printf("Testing Username Info...\n");
    get_username_info(buffer, sizeof(buffer));
    printf("  Result: %s\n\n", buffer);
}

void test_console_colors(void) {
    printf("Testing Console Colors...\n");
    init_console();
    
    printf("  Normal text\n");
    
    set_console_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("  Red text\n");
    
    set_console_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("  Green text\n");
    
    set_console_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("  Blue text\n");
    
    set_console_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("  Yellow text\n");
    
    set_console_color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("  Cyan text\n");
    
    set_console_color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("  Magenta text\n");
    
    reset_console_color();
    printf("  Back to normal\n\n");
}

int main(void) {
    printf("========================================\n");
    printf("XPFetch Component Test Suite\n");
    printf("========================================\n\n");
    
    test_console_colors();
    test_os_info();
    test_cpu_info();
    test_memory_info();
    test_uptime_info();
    test_disk_info();
    test_display_info();
    test_hostname_info();
    test_username_info();
    
    printf("========================================\n");
    printf("All tests completed!\n");
    printf("========================================\n");
    
    return 0;
}
