/*
 * ASCII logo definitions for XPFetch
 */

#ifndef LOGO_H
#define LOGO_H

#include <windows.h>

static const char *xp_logo[] = {
    "    :::    :::    ",
    "    :+:    :+:    ",
    "    +:+  +:+      ",
    "     +#++:        ",
    "    +#+  +#+      ",
    "   #+#    #+#     ",
    "  ###    ###      ",
    "                  ",
    " Windows XP       "
};

static const int xp_logo_lines = 9;

static const char *w2k_logo[] = {
    "   ___   ___      ",
    "  |__ \\ / _ \\     ",
    "     ) | | | |    ",
    "    / /| | | |    ",
    "   / /_| |_| |    ",
    "  |____|\\___/     ",
    "                  ",
    " Windows 2000     "
};

static const int w2k_logo_lines = 8;

static const char *win_logo[] = {
    "  ┌─┬─┐           ",
    "  │ │ │           ",
    "  ├─┼─┤           ",
    "  │ │ │           ",
    "  └─┴─┘           ",
    "                  ",
    " Windows          "
};

static const int win_logo_lines = 7;

static const char *win_ascii_logo[] = {
    "  .----.           ",
    "  | [] |           ",
    "  |    |           ",
    "  '----'           ",
    "                   ",
    " Windows           "
};

static const int win_ascii_logo_lines = 6;

#endif /* LOGO_H */
