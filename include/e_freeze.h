#ifndef __E_FREEZE_H__
#define __E_FREEZE_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"
#include "player.h"

typedef struct Freeze_S
{
	Entity *ent;
	int maxHealth;

}Freeze;

/**
* @brief spawn a freeze entity
* @param position the screen position to spawn the freeze at
* @return NULL on error, or a pointer to a new freeze entity
*/
Entity *freeze_spawn(Vector2D position);

/*
*	@brief checks what the freeze collided with and respond accordingly
*	@param other sthe entity the freeze collided with
*/
void freeze_collide(Entity *other);

#endif