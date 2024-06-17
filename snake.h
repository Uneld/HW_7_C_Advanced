#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include "typedefs.h"
#include "settings.h"
#include "apple.h"

snake_t initSnake(int x, int y, size_t tsize, control_buttons *butCtrl, const char *headChar, const char *tailChar, int lockControl);
void moveSnake(snake_t *snake);
void printSnake(snake_t *snake, char matrix[][MAX_Y]);
void setDir(snake_t *snake, enum Direction dir);
int eatHandler(snake_t *snake, apple_t *apple, int unlockEat);
int snakeCollision(snake_t *snake);

#endif /* __SNAKE_H__ */