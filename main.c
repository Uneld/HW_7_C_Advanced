#include "controls.h"
#include "game_field.h"
#include "console_colors.h"
#include "snake_bot.h"
#include "time.h"

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

float speed = 0;
LARGE_INTEGER counter, oldCounterUpdateConsole, oldCounterUpdatePumkins, freq;
int gameMode = 0;
int flagWorkGame = 0;

int lockControlSnake1;
int lockControlSnake2;

pumpkin_t pumpkins[PUMPKINS_SIZE];
drone_t drones[DRONES_NUM];
drone_t *manualControlDrone = NULL;

void initPumpkins(pumpkin_t *pumpkins, int initX, int initY, int width, int heigt, int step)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < heigt; j++)
		{
			pumpkins[i * heigt + j].apple.x = i * step + initX;
			pumpkins[i * heigt + j].apple.y = j * step + initY;
			pumpkins[i * heigt + j].isRipe = 0;
			pumpkins[i * heigt + j].isEaten = 0;
			pumpkins[i * heigt + j].isOccupied = 0;
		}
	}
}

void printPumpkins(pumpkin_t *pumpkins, int size, char matrix[][MAX_Y])
{
	char ch_pumpkin;
	for (int i = 0; i < size; i++)
	{
		ch_pumpkin = CHAR_PUMKIN_NOT_RIPE;
		if (pumpkins[i].isEaten)
		{
			ch_pumpkin = CHAR_PUMKIN_DEAD;
		}
		else if (pumpkins[i].isRipe)
		{
			ch_pumpkin = CHAR_PUMKIN_RIPE;
		}

		printApple(&pumpkins[i].apple, matrix, ch_pumpkin);
	}
}

void initDrones(drone_t *drones, const char *headChars, const char *tailChars, int size, int initX, int initY, control_buttons *butCtrl)
{
	for (int i = 0; i < size; i++)
	{
		drones[i].snake = initSnake(initX, initY + i, DRONES_MIN_SIZE, butCtrl, &headChars[i], &tailChars[i], 0);
		drones[i].isAlive = 1;
		drones[i].isManual = 0;
		drones[i].isByzy = 0;
	}
}

void printDrones(drone_t *drones, int size, char matrix[][MAX_Y])
{
	for (int i = 0; i < size; i++)
	{
		printSnake(&drones[i].snake, matrix);
	}
}

void moveDrones(drone_t *drones, int size)
{
	for (int i = 0; i < size; i++)
	{
		moveSnake(&drones[i].snake);
	}
}

int collectionHandler(drone_t *drones, int sizeDrones, pumpkin_t *pumpkins, int sizePumpkins)
{
	int isEaten = 0;
	int unlockEat;
	for (int i = 0; i < sizeDrones; i++)
	{
		for (int j = 0; j < sizePumpkins; j++)
		{
			unlockEat = drones[i].snake.tsize < DRONES_MAX_SIZE && pumpkins[j].isRipe == 1 && pumpkins[j].isEaten == 0;
			isEaten = eatHandler(&drones[i].snake, &pumpkins[j].apple, unlockEat);
			if (isEaten)
			{
				if (unlockEat)
				{
					drones[i].isByzy = 0;

					if (drones[i].isManual == 0)
					{
						drones[i].snake.isEnabled = 0;
					}
					pumpkins[j].isEaten = 1;
				}
				else if (pumpkins[j].isEaten == 0)
				{
					pumpkins[j].isEaten = 1;
					return 1;
				}
			}
		}
	}

	return 0;
}

void ripePumkingHandler(pumpkin_t *pumpkins, int sizePumpkins)
{
	static int countPumkin = 0;
	if (countPumkin >= sizePumpkins)
	{
		return;
	}

	int numPumkin;
	srand(time(NULL));

	do
	{
		numPumkin = rand() % sizePumpkins;

	} while (pumpkins[numPumkin].isRipe);

	countPumkin++;
	pumpkins[numPumkin].isRipe = 1;
}

int cointeinerHandler(drone_t *drones, int sizeDrones)
{
	int countGrub = 0;
	for (int i = 0; i < sizeDrones; i++)
	{
		if (drones[i].inUnload == 1 && drones[i].snake.x < WITDH_CONTAINER &&
			drones[i].snake.y > MAX_Y - HEIGHT_CONTAINER)
		{
			if (drones[i].snake.tsize > DRONES_MIN_SIZE)
			{
				drones[i].snake.tsize--;
				countGrub++;
			}
		}
	}

	return countGrub;
}

// надо добавить точки маршрута для возврата на базу и установку флага занят до полной разгрузки
#define SIZE_ROUTE_BACKWORD 3
pumpkin_t routeBackwordDrone[DRONES_NUM][SIZE_ROUTE_BACKWORD] = {
	{{{15, 10}, 0, 0, 0}, {{10, 15}, 0, 0, 0}, {{5, 15}, 0, 0, 0}},
	{{{15, 10}, 0, 0, 0}, {{10, 16}, 0, 0, 0}, {{5, 16}, 0, 0, 0}},
	{{{15, 10}, 0, 0, 0}, {{10, 17}, 0, 0, 0}, {{5, 17}, 0, 0, 0}},
	{{{15, 10}, 0, 0, 0}, {{10, 18}, 0, 0, 0}, {{5, 18}, 0, 0, 0}}};

void scaningRipePumkins(drone_t *drones, int sizeDrones, pumpkin_t *pumpkins, int sizePumpkins)
{
	for (int j = 0; j < sizeDrones; j++)
	{
		if (drones[j].inUnload == 0)
		{
			if (drones[j].isByzy == 0 && drones[0].isAlive == 1 && drones[j].snake.tsize < DRONES_MAX_SIZE)
			{
				for (int i = 0; i < sizePumpkins; i++)
				{
					if (pumpkins[i].isRipe && pumpkins[i].isOccupied == 0 && pumpkins[i].isEaten == 0)
					{
						drones[j].isByzy = 1;
						drones[j].snake.isEnabled = 1;
						drones[j].target = &pumpkins[i];
						pumpkins[i].isOccupied = 1;

						break;
					}
				}
			}
			else if (drones[j].snake.tsize >= DRONES_MAX_SIZE)
			{
				drones[j].isByzy = 1;
				drones[j].snake.isEnabled = 1;
				drones[j].inUnload = 1;
				drones[j].target = &routeBackwordDrone[j][0];
			}
		}
	}
}

void unloadingHandler(drone_t *drones, int sizeDrones)
{
	for (int j = 0; j < sizeDrones; j++)
	{
		if (drones[j].inUnload == 1)
		{
			if (drones[j].snake.x == routeBackwordDrone[j][0].apple.x &&
				drones[j].snake.y == routeBackwordDrone[j][0].apple.y)
			{
				drones[j].snake.isEnabled = 1;
				drones[j].target = &routeBackwordDrone[j][1];
			}
			else if (drones[j].snake.x == routeBackwordDrone[j][1].apple.x &&
					 drones[j].snake.y == routeBackwordDrone[j][1].apple.y)
			{
				drones[j].snake.isEnabled = 1;
				drones[j].target = &routeBackwordDrone[j][2];
			}
			else if (drones[j].snake.x == routeBackwordDrone[j][2].apple.x &&
					 drones[j].snake.y == routeBackwordDrone[j][2].apple.y)
			{
				drones[j].snake.isEnabled = 0;
				if (drones[j].snake.tsize <= DRONES_MIN_SIZE)
				{
					drones[j].inUnload = 0;
					drones[j].isByzy = 0;
				}
			}
		}
	}
}

long deltaUpdateConsole;
long deltaUpdatePumkins;

int tstCOunt;
int countGrubPumkins = 0;
int countDestroyPumkins = 0;
int main()
{

	int buttonGameControl;
	char matrix[MAX_X][MAX_Y];

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&oldCounterUpdateConsole);
	QueryPerformanceCounter(&oldCounterUpdatePumkins);

	gameMode = 2;
	lockControlSnake1 = 0;
	lockControlSnake2 = 1;
	flagWorkGame = 1;

	initPumpkins(pumpkins, PUMPKINS_INIT_X, PUMPKINS_INIT_Y, PUMPKINS_WIDTH, PUMPKINS_HEIGHT, PUMPKINS_STEP);
	initDrones(drones, DRONE_HEADS_CHAR, DRONE_TAILS_CHAR, DRONES_NUM, DRONES_INIT_X, DRONES_INIT_Y, button_controls);

	speed = 1.0 / ((float)DELAY_UPDATE_SCREEN / 1000000);
	currentLevel = 0;

	while (flagWorkGame)
	{
		QueryPerformanceCounter(&counter);

		deltaUpdatePumkins = (counter.QuadPart - oldCounterUpdatePumkins.QuadPart) * 1000000 / freq.QuadPart;
		if (deltaUpdatePumkins >= DELAY_WORK_RISE_PUMPKIN)
		{
			oldCounterUpdatePumkins = counter;
			ripePumkingHandler(pumpkins, PUMPKINS_SIZE);
			countGrubPumkins += cointeinerHandler(drones, DRONES_NUM);
			scaningRipePumkins(drones, DRONES_NUM, pumpkins, PUMPKINS_SIZE);
			tstCOunt++;
		}

		deltaUpdateConsole = (counter.QuadPart - oldCounterUpdateConsole.QuadPart) * 1000000 / freq.QuadPart;
		if (deltaUpdateConsole >= DELAY_UPDATE_SCREEN)
		{
			oldCounterUpdateConsole = counter;

			int key = getControlKey();
			if (key > 0)
			{
				if (manualControlDrone != NULL)
				{
					manualControlDrone->isManual = 0;
				}
			}
			switch (key)
			{
			case KEY_1_VAL:
				drones[0].isManual = 1;
				drones[0].snake.isEnabled = 1;
				manualControlDrone = &drones[0];
				break;
			case KEY_2_VAL:
				drones[1].isManual = 1;
				drones[1].snake.isEnabled = 1;
				manualControlDrone = &drones[1];
				break;
			case KEY_3_VAL:
				drones[2].isManual = 1;
				drones[2].snake.isEnabled = 1;
				manualControlDrone = &drones[2];
				break;
			case KEY_4_VAL:
				drones[3].isManual = 1;
				drones[3].snake.isEnabled = 1;
				manualControlDrone = &drones[3];
				break;
			case KEY_5_VAL:
				if (manualControlDrone != NULL)
				{
					manualControlDrone->snake.isEnabled = 0;
					manualControlDrone->isManual = 0;
				}
				manualControlDrone = NULL;
				break;
			}

			if (manualControlDrone != NULL)
			{
				snakeControlHandler(&manualControlDrone->snake);
			}
			moveDrones(drones, DRONES_NUM);
			countDestroyPumkins += collectionHandler(drones, DRONES_NUM, pumpkins, PUMPKINS_SIZE);
			unloadingHandler(drones, DRONES_NUM);

			system("cls");
			clearGameField(matrix);
			if (drones[0].isManual == 0 && drones[0].target != NULL)
			{
				autoChangeDirection(&drones[0].snake, &drones[0].target->apple, pumpkins, PUMPKINS_SIZE);
			}
			if (drones[1].isManual == 0 && drones[1].target != NULL)
			{
				autoChangeDirection(&drones[1].snake, &drones[1].target->apple, pumpkins, PUMPKINS_SIZE);
			}
			if (drones[2].isManual == 0 && drones[2].target != NULL)
			{
				autoChangeDirection(&drones[2].snake, &drones[2].target->apple, pumpkins, PUMPKINS_SIZE);
			}
			if (drones[3].isManual == 0 && drones[3].target != NULL)
			{
				autoChangeDirection(&drones[3].snake, &drones[3].target->apple, pumpkins, PUMPKINS_SIZE);
			}

			printPumpkins(pumpkins, PUMPKINS_SIZE, matrix);
			printDrones(drones, DRONES_NUM, matrix);
			printGameField(matrix);

			setConsoleColor(CC_BLUE_LIGHT, CC_BLACK);
			setConsoleColor(CC_BLUE_LIGHT, CC_BLACK);
			setConsoleColor(CC_GREEN, CC_BLACK);
			// printf("Current level: %d\n", currentLevel);
			// printf("Speed: %.2f px/s \n", speed);
			// printf("Press F10 for exit to menu. Press P for pause. Control P1: w,s,a,d or arrows\n");
			// setConsoleColor(CC_BROWN, CC_BLACK);
			// if (lockControlSnake1 == 0)
			// {
			// 	printf("Control P1: w,s,a,d or arrows\n");
			// }
			// if (lockControlSnake2 == 0)
			// {
			// 	printf("Control P2: i,k,j,l or arrows\n");
			// }
			// printf("\n %d \n", getControlKey());
			printf("Count: %d\n", tstCOunt);
			// printf("countGrubPumkins: %d\n", countGrubPumkins);
			printf("countDestroyPumkins: %d countGrubPumkins: %d\n", countDestroyPumkins, countGrubPumkins);

			if (drones[0].target != NULL)
			{
				printf("pumpkin: x:%d, y:%d\n", drones[0].isByzy, drones[0].target->apple.y);
			}
			if (drones[1].target != NULL)
			{
				printf("pumpkin: x:%d, y:%d\n", drones[1].isByzy, drones[1].target->apple.y);
			}
			if (drones[2].target != NULL)
			{
				printf("pumpkin: x:%d, y:%d\n", drones[2].isByzy, drones[2].target->apple.y);
			}
			if (drones[3].target != NULL)
			{
				printf("pumpkin: x:%d, y:%d\n", drones[3].isByzy, drones[3].target->apple.y);
			}

			setConsoleColor(CC_WHITE, CC_BLACK);
		}
		usleep(1);
	}

	return 0;
}
