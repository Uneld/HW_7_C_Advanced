#ifndef __SNAKEBOT_H__
#define __SNAKEBOT_H__

#include "snake.h"

/**
 * Changes the direction of the snake based on its surroundings.
 *
 * @param snake the snake object
 * @param apple the apple object
 * @param pumpkins the array of pumpkin objects
 * @param sizePumkins the size of the pumpkin array
 */
void autoChangeDirection(snake_t *snake, apple_t *apple, pumpkin_t *pumpkins, int sizePumkins);

#endif /* __SNAKEBOT_H__ */