#include "snake_bot.h"
#include "math.h"

enum Direction opposite_direction(enum Direction dir)
{
    switch (dir)
    {
    case UP:
        return DOWN;
    case DOWN:
        return UP;

    case LEFT:
        return RIGHT;

    default:
        return LEFT;
    }
}

int newDir;

void autoChangeDirection(snake_t *snake, apple_t *apple, pumpkin_t *pumpkins, int sizePumkins)
{
    int lockDir[4] = {0};
    for (int i = 0; i < 4; i++)
    {
        lockDir[i] = 0;
    }
    int dX = snake->x - apple->x;
    int dY = snake->y - apple->y;
    int absdX = abs(dX);
    int absdY = abs(dY);
    int oldSnakeDir = snake->dir;
    int oppoDir = opposite_direction(oldSnakeDir);
    // printf("sx = %d, sy = %d", snake->x, snake->y);
    // printf("dx = %d, dy = %d", dX, dY);

    if (absdY < absdX)
    {
        if (dX > 0)
        {
            setDir(snake, LEFT);
        }
        else
        {
            setDir(snake, RIGHT);
        }
    }
    else
    {
        if (dY > 0)
        {
            setDir(snake, UP);
        }
        else
        {
            setDir(snake, DOWN);
        }
    }

    lockDir[oppoDir] = 1;

    int checkX_L = (snake->x - 1) % MAX_X;
    int checkX_R = (snake->x + 1) % MAX_X;
    int checkY_U = (snake->y - 1) % MAX_Y;
    int checkY_D = (snake->y + 1) % MAX_Y;

    for (int i = 0; i < snake->tsize; i++)
    {
        if (checkX_L == snake->tail[i].x && snake->y == snake->tail[i].y)
        {
            lockDir[LEFT] = 1;
        }

        if (checkX_R == snake->tail[i].x && snake->y == snake->tail[i].y)
        {
            lockDir[RIGHT] = 1;
        }
        if (checkY_U == snake->tail[i].y && snake->x == snake->tail[i].x)
        {
            lockDir[UP] = 1;
        }
        if (checkY_D == snake->tail[i].y && snake->x == snake->tail[i].x)
        {
            lockDir[DOWN] = 1;
        }

        for (int i = 0; i < sizePumkins; i++)
        {
            if (pumpkins[i].isEaten == 0)
            {
                if (apple != &pumpkins[i].apple)
                {
                    if (checkX_L == pumpkins[i].apple.x && snake->y == pumpkins[i].apple.y)
                    {
                        lockDir[LEFT] = 1;
                    }

                    if (checkX_R == pumpkins[i].apple.x && snake->y == pumpkins[i].apple.y)
                    {
                        lockDir[RIGHT] = 1;
                    }
                    if (checkY_U == pumpkins[i].apple.y && snake->x == pumpkins[i].apple.x)
                    {
                        lockDir[UP] = 1;
                    }
                    if (checkY_D == pumpkins[i].apple.y && snake->x == pumpkins[i].apple.x)
                    {
                        lockDir[DOWN] = 1;
                    }
                }
            }
        }
    }

    // newDir = snake->dir;
    if (lockDir[snake->dir] == 1)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (lockDir[i] != 1)
            {
                snake->dir = i;
            }
        }
    }

    // printf("dir = %d, opp = %d, newDir = %d\n", oldSnakeDir, oppoDir, newDir);
    // printf("l0 %d, l1 %d, l2 %d, l3 %d", lockDir[0], lockDir[1], lockDir[2], lockDir[3]);
}
