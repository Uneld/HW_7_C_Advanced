#include "drones.h"
#include "time.h"

pumpkin_t routeBackwordDrone[DRONES_NUM][SIZE_ROUTE_BACKWORD] = {
    {{{15, 7}, 0, 0, 0}, {{8, 15}, 0, 0, 0}, {{3, 15}, 0, 0, 0}},
    {{{15, 8}, 0, 0, 0}, {{8, 16}, 0, 0, 0}, {{3, 16}, 0, 0, 0}},
    {{{15, 9}, 0, 0, 0}, {{8, 17}, 0, 0, 0}, {{3, 17}, 0, 0, 0}},
    {{{15, 10}, 0, 0, 0}, {{8, 18}, 0, 0, 0}, {{3, 18}, 0, 0, 0}}};

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
        if (drones[i].isAlive == 0)
        {
            drones[i].snake.isEnabled = 0;
        }
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
            // проверка на возможность съесть
            unlockEat = drones[i].snake.tsize < DRONES_MAX_SIZE && pumpkins[j].isRipe == 1 && pumpkins[j].isEaten == 0;
            // функция из змейка дополненная блокировкой еды и возвращаемым флагом было ли совпадение головы змеи и яблока
            isEaten = eatHandler(&drones[i].snake, &pumpkins[j].apple, unlockEat);
            if (isEaten)
            {
                if (unlockEat)
                {
                    drones[i].isByzy = 0;

                    // приостановка дрона в автоматическом режиме в ождании новой цели
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
                // необходимо если для сброса флага занятости при ошибочной цели после ручного режима
                else if (pumpkins[j].isEaten == 1 && &pumpkins[j] == drones[i].target)
                {
                    drones[i].isByzy = 0;
                }
            }
        }
    }

    return 0;
}

void ripePumkingHandler(pumpkin_t *pumpkins, int sizePumpkins)
{
    static int countPumkin = 0;
    // проверка на то что все тыквы взошли
    if (countPumkin >= sizePumpkins)
    {
        return;
    }

    int numPumkin;
    srand(time(NULL));
    // рандомно взводим тыквы
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
        // если дрон на разгрузке то разгружаем тележки
        if (drones[i].inUnload == 1 && drones[i].snake.x < WIDTH_CONTAINER &&
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

int checkEatenPumpkin(pumpkin_t *pumpkins, int sizePumpkins)
{
    for (int i = 0; i < sizePumpkins; i++)
    {
        if (pumpkins[i].isEaten != 1)
        {
            return 0;
        }
    }

    return 1;
}

void scaningRipePumkins(drone_t *drones, int sizeDrones, pumpkin_t *pumpkins, int sizePumpkins, int checkEatenPumpkins)
{
    for (int j = 0; j < sizeDrones; j++)
    {
        // если дрон не на разгрузке и не в ручном режиме
        if (drones[j].inUnload == 0 && drones[j].isManual == 0)
        {
            // проверяем на то что не собраны все тыквы змейка жива и не занята
            if (drones[j].isByzy == 0 && drones[j].isAlive == 1 && drones[j].snake.tsize < DRONES_MAX_SIZE && checkEatenPumpkins == 0)
            {
                for (int i = 0; i < sizePumpkins; i++)
                {
                    // ищем свободную не съеденную тыву и запускаем дрон назначает цель и взводим флаг занятости
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
            // если дрон полный или все съедено инициируем возврат на базу
            else if (drones[j].snake.tsize >= DRONES_MAX_SIZE || checkEatenPumpkins)
            {
                drones[j].isByzy = 1;
                drones[j].snake.isEnabled = 1;
                drones[j].inUnload = 1;
                drones[j].target = &routeBackwordDrone[j][0];
            }
        }
    }
}

void unloadingHandler(drone_t *drones, int sizeDrones, int checkEatenPumpkins)
{
    // реализуем проход по нескольким точкам для выравнивания возврата
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
                // если все съедено остаемся на базе если нет после разгрузки продолжаем работу
                if (checkEatenPumpkins == 0 && drones[j].snake.tsize <= DRONES_MIN_SIZE)
                {
                    drones[j].inUnload = 0;
                    drones[j].isByzy = 0;
                }
            }
        }
    }
}

void droneCollision(drone_t *drones, int sizeDrones)
{
    for (int i = 0; i < sizeDrones; i++)
    {
        drones[i].isAlive = !snakeCollision(&drones[i].snake);
    }
}