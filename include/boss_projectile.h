#ifndef __BOSS_PROJECTILE_H__
#define __BOSS_PROJECTILE_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"
#include "player.h"

typedef struct Boss_Projectile_S
{
	Entity *ent;
	int		maxHealth;
	Bool	frozen;
	Bool	alive;
	int		lives;


}Boss_Projectile;

/**
* @brief spawn a projectile boss entity
* @param position the screen position to spawn the projectile boss at
* @return NULL on error, or a pointer to a new projectile boss entity
*/
Entity *boss_projectile_spawn(Vector2D position);

/**
* @brief spawn a minion entity
* @param position the screen position to spawn the minion at
* @return NULL on error, or a pointer to a new minion entity
*/
Entity *minion_spawn(Vector2D position);

/*
*	@brief checks what the projectile boss collided with and respond accordingly
*	@param other sthe entity the projectile boss collided with
*/
void boss_projectile_collide(Entity *other);

#endif