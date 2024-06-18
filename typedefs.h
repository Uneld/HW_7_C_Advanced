#ifndef __TIPEDEFS_H__
#define __TIPEDEFS_H__

#include <stdlib.h>

typedef struct
{
    int down;
    int up;
    int left;
    int right;
} control_buttons;

enum Direction
{
    UP = 0,
    RIGHT = 1,
    LEFT = 2,
    DOWN = 3
};

typedef struct
{
    int x;
    int y;
} tail_t;

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

typedef struct
{
    int x;
    int y;
} apple_t;

typedef struct
{
    apple_t apple;
    int isEaten;
    int isRipe;
    int isOccupied;
} pumpkin_t;

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