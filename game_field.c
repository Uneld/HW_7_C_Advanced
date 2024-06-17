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
            if (matrix[i][j] != ' ')
            {
                matrix[i][j] = ' ';
            }
        }
    }
}

void printGameField(char matrix[][MAX_Y])
{
    // не придумал как это решить (TODO)
    // const char SNAKE_HEAD_1 = '@';
    // const char SNAKE_TAIL_1 = '*';
    // const char SNAKE_HEAD_2 = '%';
    // const char SNAKE_TAIL_2 = '+';

    // рисуем все поле
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

void printMenu()
{
    setConsoleColor(CC_BLUE_LIGHT, CC_BLACK);
    printf("!!! Welcome to Snake Game !!!\n");
    printf("----------------------------\n");
    setConsoleColor(CC_GREEN, CC_BLACK);
    printf("1. Start game for 1 player\n");
    printf("2. Start game for 2 players\n");
    printf("3. Starting game for 1 players with Bot\n");
    printf("4. Exit game\n");
    setConsoleColor(CC_BLUE_LIGHT, CC_BLACK);
    printf("----------------------------\n");
    printf("Enter your choice: ");
    setConsoleColor(CC_MAGENTA, CC_BLACK);
}