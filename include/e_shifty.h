#ifndef __E_SHIFTY_H__
#define __E_SHIFTY_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"
#include "player.h"

typedef struct Shifty_S
{
	Entity *ent;
	int maxHealth;

}Shifty;

/**
* @brief spawn a shifty entity
* @param position the screen position to spawn the shifty at
* @return NULL on error, or a pointer to a new shifty entity
*/
Entity *shifty_spawn(Vector2D position);

/*
*	@brief checks what the shifty collided with and respond accordingly
*	@param other sthe entity the shifty collided with
*/
void shifty_collide(Entity *other);

#endif