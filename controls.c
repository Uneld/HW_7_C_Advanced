#include "controls.h"

#define COMMON_ARR 224
#define KEY_ARR_DOWN 80
#define KEY_ARR_UP 72
#define KEY_ARR_LEFT 75
#define KEY_ARR_RIGHT 77

#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53

#define KEY_s 115
#define KEY_w 119
#define KEY_a 97
#define KEY_d 100
#define KEY_S 83
#define KEY_W 87
#define KEY_A 65
#define KEY_D 68
#define KEY_RUS_s 235
#define KEY_RUS_w 230
#define KEY_RUS_a 228
#define KEY_RUS_d 162
#define KEY_RUS_S 155
#define KEY_RUS_W 150
#define KEY_RUS_A 148
#define KEY_RUS_D 130

control_buttons button_controls[SIZE_BUF_KEY] =
    {
        {KEY_ARR_DOWN, KEY_ARR_UP, KEY_ARR_LEFT, KEY_ARR_RIGHT},
        {KEY_s, KEY_w, KEY_a, KEY_d},
        {KEY_S, KEY_W, KEY_A, KEY_D},
        {KEY_RUS_s, KEY_RUS_w, KEY_RUS_a, KEY_RUS_d},
        {KEY_RUS_S, KEY_RUS_W, KEY_RUS_A, KEY_RUS_D}};

/**
 * Handles the snake control based on the keyboard input.
 *
 * @param snake the snake object
 * @param key the keyboard input
 */
void snakeControlHandler(snake_t *snake, int key)
{
    switch (key)
    {
    case COMMON_ARR:
        key = getch();
        if (snake->lockControl == 0)
        {
            if (key == snake->butCtrl[BUF_ARR_KEY].down)
                setDir(snake, DOWN);
            else if (key == snake->butCtrl[BUF_ARR_KEY].up)
                setDir(snake, UP);
            else if (key == snake->butCtrl[BUF_ARR_KEY].left)
                setDir(snake, LEFT);
            else if (key == snake->butCtrl[BUF_ARR_KEY].right)
                setDir(snake, RIGHT);
        }
        break;
    default:
        for (size_t i = 0; i < SIZE_BUF_KEY; i++)
        {
            if (snake->lockControl == 0)
            {
                if (key == snake->butCtrl[i].down)
                    setDir(snake, DOWN);
                else if (key == snake->butCtrl[i].up)
                    setDir(snake, UP);
                else if (key == snake->butCtrl[i].left)
                    setDir(snake, LEFT);
                else if (key == snake->butCtrl[i].right)
                    setDir(snake, RIGHT);
            }
        }
        break;
    }
}

/**
 * Gets the control key from the keyboard input.
 *
 * @return the control key code
 */
int getControlKey()
{
    if (kbhit())
    {
        int key = getch();
        switch (key)
        {
        case KEY_1:
            return KEY_1_VAL;
        case KEY_2:
            return KEY_2_VAL;
        case KEY_3:
            return KEY_3_VAL;
        case KEY_4:
            return KEY_4_VAL;
        case KEY_5:
            return KEY_5_VAL;

        default:
            return key;
        }
    }

    return 0;
}