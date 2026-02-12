/*
 * console color and helper functions
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>

#define LOGO_COLOR (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define LABEL_COLOR (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define TEXT_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

extern HANDLE hConsole;
extern WORD original_attributes;

void init_console(void);
void set_console_color(WORD color);
void reset_console_color(void);

#endif /* CONSOLE_H */
