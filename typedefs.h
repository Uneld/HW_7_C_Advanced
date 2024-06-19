#ifndef __TIPEDEFS_H__
#define __TIPEDEFS_H__

#include <stdlib.h>

/**
 * @typedef control_buttons
 * @brief Represents the control buttons for the game.
 *
 * This struct contains four integer members to represent the down, up, left, and right control buttons.
 *
 * @param down  integer value for the down button
 * @param up    integer value for the up button
 * @param left  integer value for the left button
 * @param right integer value for the right button
 */
typedef struct
{
    int down;
    int up;
    int left;
    int right;
} control_buttons;

/**
 * @enum Direction
 * @brief Enumerates the possible directions in the game.
 *
 * This enum defines four possible directions: UP, RIGHT, LEFT, and DOWN.
 *
 * @param UP    represents the up direction
 * @param RIGHT represents the right direction
 * @param LEFT  represents the left direction
 * @param DOWN  represents the down direction
 */
enum Direction
{
    UP = 0,
    RIGHT = 1,
    LEFT = 2,
    DOWN = 3
};

/**
 * @typedef tail_t
 * @brief Represents a single element in the snake's tail.
 *
 * This struct contains two integer members to represent the x and y coordinates of a tail element.
 *
 * @param x integer value for the x coordinate
 * @param y integer value for the y coordinate
 */
typedef struct
{
    int x;
    int y;
} tail_t;

/**
 * @typedef snake_t
 * @brief Represents the snake in the game.
 *
 * This struct contains several members to represent the snake's properties.
 *
 * @param x        integer value for the x coordinate
 * @param y        integer value for the y coordinate
 * @param dir      enum Direction value for the snake's current direction
 * @param tail     pointer to a tail_t struct for the snake's tail
 * @param tsize    size_t value for the size of the tail
 * @param butCtrl  pointer to a control_buttons struct for the snake's control buttons
 * @param headChar const char pointer for the character to represent the snake's head
 * @param tailChar const char pointer for the character to represent the snake's tail
 * @param lockControl  integer value to indicate whether the control is locked
 * @param isEnabled  integer value to indicate whether the snake is enabled
 */
typedef struct
{
    int x;
    int y;
    enum Direction dir;
    tail_t *tail;
    size_t tsize;
    control_buttons *butCtrl;
    const char *headChar;
    const char *tailChar;
    int lockControl;
    int isEnabled;
} snake_t;

/**
 * @typedef apple_t
 * @brief Represents an apple in the game.
 *
 * This struct contains two integer members to represent the x and y coordinates of an apple.
 *
 * @param x integer value for the x coordinate
 * @param y integer value for the y coordinate
 */
typedef struct
{
    int x;
    int y;
} apple_t;

/**
 * @typedef pumpkin_t
 * @brief Represents a pumpkin in the game.
 *
 * This struct contains several members to represent a pumpkin's properties.
 *
 * @param apple     apple_t struct for the pumpkin's position
 * @param isEaten   integer value to indicate whether the pumpkin is eaten
 * @param isRipe    integer value to indicate whether the pumpkin is ripe
 * @param isOccupied integer value to indicate whether the pumpkin is occupied
 */
typedef struct
{
    apple_t apple;
    int isEaten;
    int isRipe;
    int isOccupied;
} pumpkin_t;

/**
 * @typedef drone_t
 * @brief Represents a drone in the game.
 *
 * This struct contains several members to represent a drone's properties.
 *
 * @param snake      snake_t struct for the drone's snake
 * @param isAlive    integer value to indicate whether the drone is alive
 * @param isManual   integer value to indicate whether the drone is in manual mode
 * @param isByzy     integer value to indicate whether the drone is busy
 * @param inUnload   integer value to indicate whether the drone is unloading
 * @param target     pumpkin_t pointer for the drone's target
 */
typedef struct
{
    snake_t snake;
    int isAlive;
    int isManual;
    int isByzy;
    int inUnload;
    pumpkin_t *target;
} drone_t;

#endif /* __TIPEDEFS_H__ */