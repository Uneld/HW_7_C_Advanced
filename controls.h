#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include "snake.h"

#define BUF_ARR_KEY 0
#define SIZE_BUF_KEY 5

#define KEY_1_VAL 1
#define KEY_2_VAL 2
#define KEY_3_VAL 3
#define KEY_4_VAL 4
#define KEY_5_VAL 5

extern control_buttons button_controls[SIZE_BUF_KEY];

void snakeControlHandler(snake_t *snake, int key);
int getControlKey();

#endif /* __CONTROLS_H__ */