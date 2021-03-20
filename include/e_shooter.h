#ifndef __E_SHOOTER_H__
#define __E_SHOOTER_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"
#include "player.h"

typedef struct Shooter_S
{
	Entity *ent;
	int maxHealth;

}Shooter;

/**
* @brief spawn a shooter entity
* @param position the screen position to spawn the shooter at
* @return NULL on error, or a pointer to a new shooter entity
*/
Entity *shooter_spawn(Vector2D position);

/**
* @brief spawn a pellet entity
* @param position the screen position to spawn the shooter at
* @return NULL on error, or a pointer to a new pellet entity
*/
Entity *pellet_spawn(Vector2D position);

/*
*	@brief checks what the shooter collided with and respond accordingly
*	@param other sthe entity the shooter collided with
*/
void shooter_collide(Entity *other);

#endif