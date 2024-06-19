#ifndef __APPLE_H__
#define __APPLE_H__

#include "typedefs.h"
#include "settings.h"

/**
 * Initializes a new apple object.
 *
 * @param x the initial x-coordinate of the apple
 * @param y the initial y-coordinate of the apple
 * @return a new apple object
 */
apple_t initApple(int x, int y);
/**
 * Prints the apple in the game environment.
 *
 * @param apple the apple object to be printed
 * @param matrix the game environment matrix
 * @param ch_apple the character representing the apple
 */
void printApple(apple_t *apple, char matrix[][MAX_Y], char ch_apple);

#endif /* __APPLE_H__ */