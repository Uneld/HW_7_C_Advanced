#include "controls.h"
#include "game_field.h"
#include "console_colors.h"
#include "drones.h"

LARGE_INTEGER counter, oldCounterUpdateConsole, oldCounterUpdatePumkins, freq;

pumpkin_t pumpkins[PUMPKINS_SIZE];
drone_t drones[DRONES_NUM];
drone_t *manualControlDrone = NULL;

long deltaUpdateConsole;
long deltaUpdatePumkins;

int countGrubPumkins = 0;
int countDestroyPumkins = 0;
int checkEatenPumpkins = 0;

int main()
{
	char matrix[MAX_X][MAX_Y];

	// инициализация счетчиков
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&oldCounterUpdateConsole);
	QueryPerformanceCounter(&oldCounterUpdatePumkins);

	initPumpkins(pumpkins, PUMPKINS_INIT_X, PUMPKINS_INIT_Y, PUMPKINS_WIDTH, PUMPKINS_HEIGHT, PUMPKINS_STEP);
	initDrones(drones, DRONE_HEADS_CHAR, DRONE_TAILS_CHAR, DRONES_NUM, DRONES_INIT_X, DRONES_INIT_Y, button_controls);

	while (1)
	{
		// счетчик
		QueryPerformanceCounter(&counter);

		// выполнение взращивания тыкв и определения целей для дронов подсчет собраных тыкв
		deltaUpdatePumkins = (counter.QuadPart - oldCounterUpdatePumkins.QuadPart) * 1000000 / freq.QuadPart;
		if (deltaUpdatePumkins >= DELAY_WORK_DRONES_PUMPKINS)
		{
			oldCounterUpdatePumkins = counter;
			ripePumkingHandler(pumpkins, PUMPKINS_SIZE);
			countGrubPumkins += cointeinerHandler(drones, DRONES_NUM);
			scaningRipePumkins(drones, DRONES_NUM, pumpkins, PUMPKINS_SIZE, checkEatenPumpkins);
		}

		deltaUpdateConsole = (counter.QuadPart - oldCounterUpdateConsole.QuadPart) * 1000000 / freq.QuadPart;
		if (deltaUpdateConsole >= DELAY_UPDATE_SCREEN)
		{
			oldCounterUpdateConsole = counter;

			// получаем нажатие кнопки
			int key = getControlKey();
			// при смене дрона выключаем ручной режим
			if (key > KEY_1_VAL && key < KEY_5_VAL)
			{
				if (manualControlDrone != NULL)
				{
					manualControlDrone->isManual = 0;
					manualControlDrone->isByzy = 0;
					manualControlDrone->inUnload = 0;
					manualControlDrone->snake.isEnabled = 0;
				}
			}
			// выбор каким дроном управлять в ручную
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
				// выключение ручного режима
				if (manualControlDrone != NULL)
				{
					manualControlDrone->snake.isEnabled = 0;
					manualControlDrone->isManual = 0;
					manualControlDrone->isByzy = 0;
					manualControlDrone->inUnload = 0;
				}
				manualControlDrone = NULL;
				break;
			}

			// управление дроном в ручном режиме если он был выбран
			if (manualControlDrone != NULL)
			{
				if (manualControlDrone->target != NULL)
				{
					manualControlDrone->target->isOccupied = 0;
				}
				snakeControlHandler(&manualControlDrone->snake, key);
			}

			checkEatenPumpkins = checkEatenPumpkin(pumpkins, PUMPKINS_SIZE);
			moveDrones(drones, DRONES_NUM);
			droneCollision(drones, DRONES_NUM);
			// считаем уничтоженные тыквы
			countDestroyPumkins += collectionHandler(drones, DRONES_NUM, pumpkins, PUMPKINS_SIZE);
			unloadingHandler(drones, DRONES_NUM, checkEatenPumpkins);

			system("cls");
			clearGameField(matrix);
			// вызываем авто управление если не в ручном и есть цель
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
			printf("Alive: d1=%d, d2=%d, d3=%d, d4=%d\n", drones[0].isAlive, drones[1].isAlive, drones[2].isAlive, drones[3].isAlive);
			printf("Destroy pumkins: %d, Grub pumkins: %d, Total pumpkins: %d\n", countDestroyPumkins, countGrubPumkins, PUMPKINS_SIZE);
			setConsoleColor(CC_GREEN, CC_BLACK);
			printf("To control manually, select the drone key 1,2,3,4 key 5 turns off manual mode.\n controls: arrow or w,a,s,d");

			setConsoleColor(CC_WHITE, CC_BLACK);
		}
		usleep(1);
	}

	return 0;
}
