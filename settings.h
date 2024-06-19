#ifndef __SETTINGS_H__
#define __SETTINGS_H__

/**
 * Delay time for updating the screen in microseconds.
 */
#define DELAY_UPDATE_SCREEN 200000

/**
 * Delay time for working drones and pumpkins in microseconds.
 */
#define DELAY_WORK_DRONES_PUMPKINS 1000000

/**
 * Maximum x-coordinate of the game field.
 */
#define MAX_X 20

/**
 * Maximum y-coordinate of the game field.
 */
#define MAX_Y 20

/**
 * Minimum delta for new random apple x-coordinate.
 */
#define MIN_DELTA_NEW_RAND_APPLE_X 3

/**
 * Minimum delta for new random apple y-coordinate.
 */
#define MIN_DELTA_NEW_RAND_APPLE_Y 3

/**
 * Maximum apple weight.
 */
#define MAX_APPLE_WEIGHT 3

/**
 * Number of drones.
 */
#define DRONES_NUM 4

/**
 * Initial x-coordinate of drones.
 */
#define DRONES_INIT_X 4

/**
 * Initial y-coordinate of drones.
 */
#define DRONES_INIT_Y 15

/**
 * Minimum drone size.
 */
#define DRONES_MIN_SIZE 2

/**
 * Maximum drone size.
 */
#define DRONES_MAX_SIZE (DRONES_MIN_SIZE + 5)

/**
 * Characters representing drone heads.
 */
#define CHAR_HEAD_D1 '@'
#define CHAR_HEAD_D2 '%'
#define CHAR_HEAD_D3 '$'
#define CHAR_HEAD_D4 '#'

/**
 * Characters representing drone tails.
 */
#define CHAR_TAIL_D1 '*'
#define CHAR_TAIL_D2 '+'
#define CHAR_TAIL_D3 '\"'
#define CHAR_TAIL_D4 ':'

/**
 * Array of drone head characters.
 */
const static char DRONE_HEADS_CHAR[DRONES_NUM] = {CHAR_HEAD_D1, CHAR_HEAD_D2, CHAR_HEAD_D3, CHAR_HEAD_D4};

/**
 * Array of drone tail characters.
 */
const static char DRONE_TAILS_CHAR[DRONES_NUM] = {CHAR_TAIL_D1, CHAR_TAIL_D2, CHAR_TAIL_D3, CHAR_TAIL_D4};

/**
 * Characters representing pumpkins.
 */
#define CHAR_PUMKIN_NOT_RIPE 'o'
#define CHAR_PUMKIN_RIPE 'O'
#define CHAR_PUMKIN_DEAD 'X'

/**
 * Initial x-coordinate of pumpkins.
 */
#define PUMPKINS_INIT_X 5

/**
 * Initial y-coordinate of pumpkins.
 */
#define PUMPKINS_INIT_Y 1

/**
 * Step size for pumpkins.
 */
#define PUMPKINS_STEP 3

/**
 * Width of pumpkins.
 */
#define PUMPKINS_WIDTH 5

/**
 * Height of pumpkins.
 */
#define PUMPKINS_HEIGHT 5

/**
 * Size of pumpkins.
 */
#define PUMPKINS_SIZE (PUMPKINS_WIDTH * PUMPKINS_HEIGHT)

/**
 * Width of container.
 */
#define WIDTH_CONTAINER 8

/**
 * Height of container.
 */
#define HEIGHT_CONTAINER 7

/**
 * Size of route backward.
 */
#define SIZE_ROUTE_BACKWORD 3
#endif /* __SETTINGS_H__ */
