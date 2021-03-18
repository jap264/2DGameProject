#ifndef __BULLET_H__
#define __BULLET_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"

typedef struct Bullet_S
{
	Entity *ent;

}Bullet;

/**
* @brief spawn a pistol round entity
* @param destinationx location (x) for the entity to travel to
* @param destinationy location (y) for the entity to travel to
* @return NULL on error, or a pointer to a new bullet entity
*/
Entity *pistol_round_spawn(int destinationx, int destinationy);

/**
* @brief spawn a light round entity
* @param destinationx location (x) for the entity to travel to
* @param destinationy location (y) for the entity to travel to
* @return NULL on error, or a pointer to a new bullet entity
*/
Entity *light_round_spawn(int destinationx, int destinationy);

/**
* @brief spawn three shotgun shell entities
* @param destinationx location (x) for the entity to travel to
* @param destinationy location (y) for the entity to travel to
* @return NULL on error, or a pointer to a new bullet entity
*/
void *shotgun_shells_spawn(int destinationx, int destinationy);

/**
* @brief spawn a heavy round entity
* @param destinationx location (x) for the entity to travel to
* @param destinationy location (y) for the entity to travel to
* @return NULL on error, or a pointer to a new bullet entity
*/
Entity *heavy_round_spawn(int destinationx, int destinationy);

/**
* @brief spawn a heavy round entity
* @param destinationx location (x) for the entity to travel to
* @param destinationy location (y) for the entity to travel to
* @return NULL on error, or a pointer to a new bullet entity
*/
Entity *sniper_round_spawn(int destinationx, int destinationy);

/**
* @brief spawn a thunderwave entity
* @param destinationx location (x) for the entity to travel to
* @param destinationy location (y) for the entity to travel to
* @return NULL on error, or a pointer to a new bullet entity
*/
Entity *thunderwave_spawn(int destinationx, int destinationy);

void bullet_travel(Entity *self);

void shotgun_spread(Entity *bullet1, Entity *bullet2, Entity *bullet3);

#endif