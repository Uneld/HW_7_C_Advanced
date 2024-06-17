#ifndef __APPLE_H__
#define __APPLE_H__

#include "typedefs.h"
#include "settings.h"

apple_t initApple(int x, int y);
void printApple(apple_t *apple, char matrix[][MAX_Y], char ch_apple);

#endif /* __APPLE_H__ */