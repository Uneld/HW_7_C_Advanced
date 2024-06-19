#include "snake_bot.h"
#include "math.h"
#include "time.h"

/**
 * Returns the opposite direction of the given direction.
 *
 * @param dir the direction to find the opposite of
 * @return the opposite direction
 */
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
    // массив блокированных направлений
    int lockDir[4] = {0};
    for (int i = 0; i < 4; i++)
    {
        lockDir[i] = 0;
    }
    // считаем дельты до цели
    int dX = snake->x - apple->x;
    int dY = snake->y - apple->y;
    int absdX = abs(dX);
    int absdY = abs(dY);
    // сохраняем текущее направление змейки
    int oldSnakeDir = snake->dir;
    // сохраняем противоположное направление змейки
    int oppoDir = opposite_direction(oldSnakeDir);

    // блокируем противоположное направление
    lockDir[oppoDir] = 1;

    // выбираем новое направление для достижения цели
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

    // выбираем точки следующего шага
    int checkX_L = (snake->x - 1) % MAX_X;
    int checkX_R = (snake->x + 1) % MAX_X;
    int checkY_U = (snake->y - 1) % MAX_Y;
    int checkY_D = (snake->y + 1) % MAX_Y;

    // проверка на то что змейка не будет себя пересекать
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
    }

    // проверка на то что змейка не будет наезжать на тыквы которые не являются ее целью или уже не съедены или разрушены
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

    // если текущее выбранное направление блокировано выбираем новое которое свободно
    if (lockDir[snake->dir] == 1)
    {

        srand(time(NULL));

        do
        {
            snake->dir = rand() % 4;
        } while (lockDir[snake->dir] == 1);
    }
}
