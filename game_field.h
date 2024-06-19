#ifndef __GAME_FIELD_H__
#define __GAME_FIELD_H__

#include "settings.h"

/**
 * Clears the game field by setting all cells to their initial values.
 *
 * @param matrix the game field matrix
 */
void clearGameField(char matrix[][MAX_Y]);

/**
 * Prints the game field to the console.
 *
 * @param matrix the game field matrix
 */
void printGameField(char matrix[][MAX_Y]);
#endif /* __GAME_FIELD_H__ */