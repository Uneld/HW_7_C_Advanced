#include "apple.h"

apple_t initApple(int x, int y)
{
    apple_t apple;

    apple.x = x;
    apple.y = y;

    return apple;
}

void printApple(apple_t *apple, char matrix[][MAX_Y], char ch_apple)
{
    matrix[apple->x][apple->y] = ch_apple;
}
