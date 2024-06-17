#include "controls.h"
#include "game_field.h"
#include "console_colors.h"
#include "snake_bot.h"

void printDebugSnake(snake_t *snake) { ; }

int
    currentLevel = 0,
    collision = 0,
    collision1 = 0,
    collision2 = 0;

int
    pauseFlag = 0,
    eatWeight = 0,
    eatWeight1 = 0,
    eatWeight2 = 0;

long int delayUpdateScreen = DELAY_UPDATE_SCREEN;
float speed = 0;
LARGE_INTEGER counter, oldCounter, freq;
int gameMode = 0;
int flagWorkGame = 0;

int lockControlSnake1;
int lockControlSnake2;

int main()
{

    int buttonGameControl;
    char matrix[MAX_X][MAX_Y];
    snake_t snake;
    snake_t snake2;
    apple_t apple;

    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&oldCounter);

    while (1)
    {
        int choice;
        system("cls");
        printMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Starting game for 1 player...\n");
            gameMode = 1;
            flagWorkGame = 1;
            lockControlSnake1 = 0;
            break;
        case 2:
            printf("Starting game for 2 players...\n");
            lockControlSnake1 = 0;
            lockControlSnake2 = 0;
            gameMode = 2;
            flagWorkGame = 1;
            break;
        case 3:
            printf("Starting game for 1 players with Bot\n");
            gameMode = 2;
            lockControlSnake1 = 0;
            lockControlSnake2 = 1;
            flagWorkGame = 1;
            break;
        case 4:
            // Exit game
            printf("Exiting game...\n");
            return 0;
        default:
            printf("Invalid choice. Exiting game...\n");
            return 0;
        }

        snake = initSnake(10, 5, 2, button_controls_S1, &SNAKE_HEAD_1, &SNAKE_TAIL_1, lockControlSnake1);
        snake2 = initSnake(15, 10, 2, button_controls_S2, &SNAKE_HEAD_2, &SNAKE_TAIL_2, lockControlSnake2);
        apple = initApple(10, 10, 1);
        delayUpdateScreen = DELAY_UPDATE_SCREEN;
        speed = 1.0 / ((float)delayUpdateScreen / 1000000);
        currentLevel = 0;

        while (flagWorkGame)
        {
            QueryPerformanceCounter(&counter);

            long delta = (counter.QuadPart - oldCounter.QuadPart) * 1000000 / freq.QuadPart;
            if (delta >= delayUpdateScreen)
            {
                oldCounter = counter;

                buttonGameControl = snakeControlHandler(&snake, &snake2);

                switch (buttonGameControl)
                {
                case STOP_KEY_VAL:
                    setConsoleColor(CC_GREEN, CC_BLACK);
                    system("cls");
                    printf("Exit to menu");
                    sleep(1);
                    gameMode = 0;
                    flagWorkGame = 0;
                    setConsoleColor(CC_BLACK, CC_BLACK);
                    break;

                case PAUSE_KEY_VAL:
                    pauseFlag = !pauseFlag;
                    break;
                }

                if (pauseFlag == 1)
                {
                    setConsoleColor(CC_YELLOW, CC_BLACK);
                    system("cls");
                    printf("Game paused");
                    usleep(DELAY_UPDATE_SCREEN);
                    setConsoleColor(CC_BLACK, CC_BLACK);
                    continue;
                }

                collision1 = snakeCollision(&snake);
                if (gameMode == 2)
                {
                    collision2 = snakeCollision(&snake2);
                }
                collision = collision1 + collision2;
                if (collision)
                {
                    system("cls");

                    setConsoleColor(CC_RED, CC_BLACK);
                    printf("!!GAME OVER!!\n");
                    if (collision1 > collision2)
                    {
                        printf("Player 1 fail");
                    }
                    else if (collision2 > collision1)
                    {
                        printf("Player 2 fail");
                    }
                    else
                    {
                        printf("Both players fail");
                    }
                    setConsoleColor(CC_BLACK, CC_BLACK);
                    sleep(2);

                    gameMode = 0;
                    flagWorkGame = 0;
                }

                moveSnake(&snake);
                if (gameMode == 2)
                {
                    moveSnake(&snake2);
                }

                eatWeight1 = eatHandler(&snake, &apple);
                if (gameMode == 2)
                {
                    eatWeight2 = eatHandler(&snake2, &apple);
                }
                eatWeight = eatWeight1 + eatWeight2;

                if (eatWeight)
                {
                    currentLevel += eatWeight;
                    if (delayUpdateScreen > MIN_DELAY_UPDATE_SCREEN)
                    {
                        delayUpdateScreen -= eatWeight * INCTEMENT_LEVEL_TIME;
                    }
                    speed = 1.0 / ((float)delayUpdateScreen / 1000000);
                }

                if (snake.tsize >= WON_SIZE)
                {
                    setConsoleColor(CC_BROWN, CC_BLACK);
                    system("cls");
                    printf("Congratulations, Player 1 won!!");
                    setConsoleColor(CC_BLACK, CC_BLACK);
                    sleep(2);

                    gameMode = 0;
                    flagWorkGame = 0;
                }
                if (snake2.tsize >= WON_SIZE && gameMode == 2)
                {
                    setConsoleColor(CC_BROWN, CC_BLACK);
                    system("cls");
                    printf("Congratulations, Player 2 won!!");
                    setConsoleColor(CC_BLACK, CC_BLACK);
                    sleep(2);

                    gameMode = 0;
                    flagWorkGame = 0;
                }

                system("cls");
                clearGameField(matrix);
                autoChangeDirection(&snake2, &apple);
                printSnake(&snake, matrix);
                if (gameMode == 2)
                {
                    printSnake(&snake2, matrix);
                }
                printApple(&apple, matrix);
                printGameField(matrix);

                setConsoleColor(CC_BLUE_LIGHT, CC_BLACK);
                setConsoleColor(CC_BLUE_LIGHT, CC_BLACK);
                printf("Player 1 snake length is %lld\n", snake.tsize);
                if (gameMode == 2)
                {
                    printf("Player 2 snake length is %lld\n", snake2.tsize);
                }
                setConsoleColor(CC_GREEN, CC_BLACK);
                printf("Current level: %d. Required size to win %d\n", currentLevel, WON_SIZE);
                printf("Apple weight: %d. Speed: %.2f px/s \n", apple.weigt, speed);
                printf("Press F10 for exit to menu. Press P for pause. Control P1: w,s,a,d or arrows\n");
                setConsoleColor(CC_BROWN, CC_BLACK);
                if (lockControlSnake1 == 0)
                {
                    printf("Control P1: w,s,a,d or arrows\n");
                }
                if (lockControlSnake2 == 0)
                {
                    printf("Control P2: i,k,j,l or arrows\n");
                }
                setConsoleColor(CC_WHITE, CC_BLACK);
            }
            usleep(1);
        }
    }

    return 0;
}
