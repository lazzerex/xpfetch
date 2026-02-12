/*
 * console color and helper functions implementation
 */

#include "console.h"
#include <windows.h>

HANDLE hConsole = NULL;
WORD original_attributes = 0;

void init_console(void) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    if (hConsole != INVALID_HANDLE_VALUE) {
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            original_attributes = csbi.wAttributes;
        }
    }
}

void set_console_color(WORD color) {
    if (hConsole != INVALID_HANDLE_VALUE && hConsole != NULL) {
        SetConsoleTextAttribute(hConsole, color);
    }
}

void reset_console_color(void) {
    if (hConsole != INVALID_HANDLE_VALUE && hConsole != NULL) {
        SetConsoleTextAttribute(hConsole, original_attributes);
    }
}
