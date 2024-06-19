#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include "typedefs.h"
#include "settings.h"
#include "apple.h"

/**
 * Initializes a new snake object.
 *
 * @param x the initial x-coordinate of the snake
 * @param y the initial y-coordinate of the snake
 * @param tsize the initial tail size of the snake
 * @param butCtrl the control buttons for the snake
 * @param headChar the character representing the snake's head
 * @param tailChar the character representing the snake's tail
 * @param lockControl whether to lock the control buttons
 * @return a new snake object
 */
snake_t initSnake(int x, int y, size_t tsize, control_buttons *butCtrl, const char *headChar, const char *tailChar, int lockControl);

/**
 * Moves the snake in the game environment.
 *
 * @param snake the snake object to be moved
 */
void moveSnake(snake_t *snake);

/**
 * Prints the snake in the game environment.
 *
 * @param snake the snake object to be printed
 * @param matrix the game environment matrix
 */
void printSnake(snake_t *snake, char matrix[][MAX_Y]);

/**
 * Sets the direction of the snake.
 *
 * @param snake the snake object
 * @param dir the new direction of the snake
 */
void setDir(snake_t *snake, enum Direction dir);

/**
 * Handles the eating of an apple by the snake.
 *
 * @param snake the snake object
 * @param apple the apple object
 * @param unlockEat whether to unlock the eating mechanism
 * @return 1 if the snake eats the apple, 0 otherwise
 */
int eatHandler(snake_t *snake, apple_t *apple, int unlockEat);

/**
 * Checks for collisions between the snake and the game environment.
 *
 * @param snake the snake object
 * @return 1 if a collision is detected, 0 otherwise
 */
int snakeCollision(snake_t *snake);

#endif /* __SNAKE_H__ */