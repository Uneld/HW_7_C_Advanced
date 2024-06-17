#include "snake.h"
#include "settings.h"
#include "console_colors.h"

snake_t initSnake(int x, int y, size_t tsize, control_buttons *butCtrl, const char *headChar, const char *tailChar, int lockControl)
{
    snake_t snake;

    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    snake.dir = LEFT;
    snake.butCtrl = butCtrl;
    snake.headChar = headChar;
    snake.tailChar = tailChar;
    snake.lockControl = lockControl;
    snake.isEnabled = 0;

    for (int i = 0; i < tsize; ++i)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }

    return snake;
}

// @**
void printSnake(snake_t *snake, char matrix[][MAX_Y])
{
    // заполняем змейку
    matrix[snake->x][snake->y] = *snake->headChar;
    for (int i = 0; i < snake->tsize; ++i)
    {
        matrix[snake->tail[i].x][snake->tail[i].y] = *snake->tailChar;
    }
}

void update_tail(snake_t *snake)
{
    memmove(&snake->tail[1], &snake->tail[0], (snake->tsize - 1) * sizeof(tail_t));
    snake->tail[0].x = snake->x;
    snake->tail[0].y = snake->y;
}

void moveSnakeHandler(snake_t *snake, int dx, int dy)
{
    update_tail(snake);

    snake->x += dx;
    if (snake->x >= MAX_X)
    {
        snake->x = 0;
    }
    else if (snake->x < 0)
    {
        snake->x = MAX_X - 1;
    }

    snake->y += dy;
    if (snake->y >= MAX_Y)
    {
        snake->y = 0;
    }
    else if (snake->y < 0)
    {
        snake->y = MAX_Y - 1;
    }
}

void moveSnake(snake_t *snake)
{
    if (snake->isEnabled == 0)
    {
        return;
    }

    switch (snake->dir)
    {
    case LEFT:
        moveSnakeHandler(snake, -1, 0);
        break;
    case RIGHT:
        moveSnakeHandler(snake, 1, 0);
        break;
    case UP:
        moveSnakeHandler(snake, 0, -1);
        break;
    case DOWN:
        moveSnakeHandler(snake, 0, 1);
        break;
    }
}

void setDir(snake_t *snake, enum Direction dir)
{
    if ((snake->dir + dir) % 3)
    {
        snake->dir = dir;
    }
}

int eatHandler(snake_t *snake, apple_t *apple, int unlockEat)
{
    if (snake->x == apple->x && snake->y == apple->y)
    {
        if (unlockEat)
        {
            int posLastTail = snake->tsize - 1;
            int posSecLastTail = posLastTail - 1;

            int deltaX = snake->tail[posSecLastTail].x - snake->tail[posLastTail].x;
            int deltaY = snake->tail[posSecLastTail].y - snake->tail[posLastTail].y;
            snake->tsize = snake->tsize + 1;

            for (int i = posLastTail + 1; i < snake->tsize; i++)
            {
                snake->tail[i].x = snake->tail[i - 1].x - deltaX;
                snake->tail[i].y = snake->tail[i - 1].y - deltaY;
            }
        }
        return 1;
    }

    return 0;
}

int snakeCollision(snake_t *snake)
{
    for (int i = 0; i < snake->tsize; i++)
    {
        if (snake->x == snake->tail[i].x && snake->y == snake->tail[i].y)
        {
            return 1;
        }
    }
    return 0;
}