#ifndef __BOSS_MELEE_H__
#define __BOSS_MELEE_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"
#include "player.h"

typedef struct Boss_Melee_S
{
	Entity *ent;
	int		maxHealth;
	Bool	frozen;
	Bool	sheathed;

}Boss_Melee;

/**
* @brief spawn a melee boss entity
* @param position the screen position to spawn the melee boss at
* @return NULL on error, or a pointer to a new melee boss entity
*/
Entity *boss_melee_spawn(Vector2D position);

/*
*	@brief checks what the melee boss collided with and respond accordingly
*	@param other sthe entity the melee boss collided with
*/
void boss_melee_collide(Entity *other);

#endif