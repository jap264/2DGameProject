#ifndef __E_ARMORED_H__
#define __E_ARMORED_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"
#include "player.h"

typedef struct Armored_S
{
	Entity *ent;
	int maxHealth;

}Armored;

/**
* @brief spawn a armored entity
* @param position the screen position to spawn the armored at
* @return NULL on error, or a pointer to a new armored entity
*/
Entity *armored_spawn(Vector2D position);

/*
*	@brief checks what the armored collided with and respond accordingly
*	@param other sthe entity the armored collided with
*/
void armored_collide(Entity *other);

#endif