#include "console_colors.h"

void setConsoleColor(CONSOLECOLOR text, CONSOLECOLOR background)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (((background << 4) | text)));
}