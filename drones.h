#ifndef __DRONES_H__
#define __DRONES_H__

#include "typedefs.h"
#include "settings.h"
#include "snake_bot.h"

/**
 * Initializes an array of pumpkins with their positions and properties.
 *
 * @param pumpkins the array of pumpkins to be initialized
 * @param initX the initial x-coordinate of the pumpkins
 * @param initY the initial y-coordinate of the pumpkins
 * @param width the width of the pumpkin array
 * @param height the height of the pumpkin array
 * @param step the step size between pumpkins
 */
void initPumpkins(pumpkin_t *pumpkins, int initX, int initY, int width, int heigt, int step);

/**
 * Prints the pumpkins in the game environment.
 *
 * @param pumpkins the array of pumpkins to be printed
 * @param size the size of the pumpkin array
 * @param matrix the game environment matrix
 */
void printPumpkins(pumpkin_t *pumpkins, int size, char matrix[][MAX_Y]);

/**
 * Initializes an array of drones with their properties and control buttons.
 *
 * @param drones the array of drones to be initialized
 * @param headChars the characters representing the drone heads
 * @param tailChars the characters representing the drone tails
 * @param size the size of the drone array
 * @param initX the initial x-coordinate of the drones
 * @param initY the initial y-coordinate of the drones
 * @param butCtrl the control buttons for the drones
 */
void initDrones(drone_t *drones, const char *headChars, const char *tailChars, int size, int initX, int initY, control_buttons *butCtrl);

/**
 * Prints the drones in the game environment.
 *
 * @param drones the array of drones to be printed
 * @param size the size of the drone array
 * @param matrix the game environment matrix
 */
void printDrones(drone_t *drones, int size, char matrix[][MAX_Y]);

/**
 * Moves the drones in the game environment.
 *
 * @param drones the array of drones to be moved
 * @param size the size of the drone array
 */
void moveDrones(drone_t *drones, int size);

/**
 * Handles the collection of pumpkins by drones.
 *
 * @param drones the array of drones
 * @param sizeDrones the size of the drone array
 * @param pumpkins the array of pumpkins
 * @param sizePumpkins the size of the pumpkin array
 * @return 1 if a pumpkin is eaten, 0 otherwise
 */
int collectionHandler(drone_t *drones, int sizeDrones, pumpkin_t *pumpkins, int sizePumpkins);

/**
 * Handles the ripening of pumpkins.
 *
 * @param pumpkins the array of pumpkins
 * @param sizePumpkins the size of the pumpkin array
 */
void ripePumkingHandler(pumpkin_t *pumpkins, int sizePumpkins);

/**
 * Handles the unloading of pumpkins from drones.
 *
 * @param drones the array of drones
 * @param sizeDrones the size of the drone array
 * @return the number of pumpkins unloaded
 */
int cointeinerHandler(drone_t *drones, int sizeDrones);

/**
 * Checks if all pumpkins are eaten.
 *
 * @param pumpkins the array of pumpkins
 * @param sizePumpkins the size of the pumpkin array
 * @return 1 if all pumpkins are eaten, 0 otherwise
 */
int checkEatenPumpkin(pumpkin_t *pumpkins, int sizePumpkins);

/**
 * Scans for ripe pumpkins and assigns them to drones.
 *
 * @param drones the array of drones
 * @param sizeDrones the size of the drone array
 * @param pumpkins the array of pumpkins
 * @param sizePumpkins the size of the pumpkin array
 * @param checkEatenPumpkins the result of checkEatenPumpkin()
 */
void scaningRipePumkins(drone_t *drones, int sizeDrones, pumpkin_t *pumpkins, int sizePumpkins, int checkEatenPumpkins);

/**
 * Handles the unloading of pumpkins from drones.
 *
 * @param drones the array of drones
 * @param sizeDrones the size of the drone array
 * @param checkEatenPumpkins the result of checkEatenPumpkin()
 */
void unloadingHandler(drone_t *drones, int sizeDrones, int checkEatenPumpkins);

/**
 * Checks for drone collisions.
 *
 * @param drones the array of drones
 * @param sizeDrones the size of the drone array
 */
void droneCollision(drone_t *drones, int sizeDrones);

#endif /* __DRONES_H__ */