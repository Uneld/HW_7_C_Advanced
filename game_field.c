#include <stdio.h>
#include "game_field.h"
#include "settings.h"
#include "console_colors.h"

void clearGameField(char matrix[][MAX_Y])
{
    for (int i = 0; i < MAX_X; ++i)
    {
        for (int j = 0; j < MAX_Y; ++j)
        {
            if (i == 0 && j > MAX_Y - HEIGHT_CONTAINER)
            {
                matrix[i][j] = '|';
            }
            else if (i < WIDTH_CONTAINER && j == MAX_Y - 1)
            {
                matrix[i][j] = '_';
            }
            else if (matrix[i][j] != ' ')
            {
                matrix[i][j] = ' ';
            }
        }
    }
}

void printGameField(char matrix[][MAX_Y])
{
    for (int j = 0; j < MAX_Y; ++j)
    {
        for (int i = 0; i < MAX_X; ++i)
        {
            switch (matrix[i][j])
            {
            case CHAR_HEAD_D1:
                setConsoleColor(CC_RED, CC_BLACK);
                break;
            case CHAR_TAIL_D1:
                setConsoleColor(CC_GREEN, CC_BLACK);
                break;
            case CHAR_HEAD_D2:
                setConsoleColor(CC_YELLOW, CC_BLACK);
                break;
            case CHAR_TAIL_D2:
                setConsoleColor(CC_CYAN, CC_BLACK);
                break;
            case CHAR_HEAD_D3:
                setConsoleColor(CC_RED, CC_BLACK);
                break;
            case CHAR_TAIL_D3:
                setConsoleColor(CC_GREEN, CC_BLACK);
                break;
            case CHAR_HEAD_D4:
                setConsoleColor(CC_RED, CC_BLACK);
                break;
            case CHAR_TAIL_D4:
                setConsoleColor(CC_GREEN, CC_BLACK);
                break;
            case CHAR_PUMKIN_DEAD:
                setConsoleColor(CC_BLUE, CC_BLACK);
                break;
            case CHAR_PUMKIN_RIPE:
                setConsoleColor(CC_GREEN_LIGHT, CC_BLACK);
                break;
            case CHAR_PUMKIN_NOT_RIPE:
                setConsoleColor(CC_BROWN, CC_BLACK);
                break;

            default:
                setConsoleColor(CC_WHITE, CC_BLACK);
                break;
            }
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}
