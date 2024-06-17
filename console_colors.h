#ifndef __CONSOLECOLORS_H__
#define __CONSOLECOLORS_H__

#include "windows.h"

typedef enum
{
    CC_BLACK = 0,
    CC_BLUE = 1,
    CC_GREEN = 2,
    CC_CYAN = 3,
    CC_RED = 4,
    CC_MAGENTA = 5,
    CC_BROWN = 6,
    CC_GRAY_LIGHT = 7,
    CC_GRAY_DARK = 8,
    CC_BLUE_LIGHT = 9,
    CC_GREEN_LIGHT = 10,
    CC_CYAN_LIGHT = 11,
    CC_RED_LIGHT = 12,
    CC_MAGENTA_LIGHJT = 13,
    CC_YELLOW = 14,
    CC_WHITE = 15,
} CONSOLECOLOR;

void setConsoleColor(CONSOLECOLOR text, CONSOLECOLOR background);

#endif /* __CONSOLE_COLORS_H__ */