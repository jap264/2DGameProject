#ifndef __E_WALKER_H__
#define __E_WALKER_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"
#include "player.h"

typedef struct Walker_S
{
	Entity *ent;
	int maxHealth;

}Walker;

/**
* @brief spawn a walker entity
* @param position the screen position to spawn the walker at
* @return NULL on error, or a pointer to a new walker entity
*/
Entity *walker_spawn(Vector2D position);

/*
*	@brief checks what the walker collided with and respond accordingly
*	@param other sthe entity the walker collided with
*/
void walker_collide(Entity *other);

#endif