#ifndef __bullet_H__
#define __bullet_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"

typedef struct Bullet_S
{
	Entity *ent;

}Bullet;

/**
* @brief spawn a bullet entity
* @param destinationx location (x) for the entity to travel to
* @param destinationy location (y) for the entity to travel to
* @return NULL on error, or a pointer to a new bullet entity
*/
Entity *bullet_spawn(int destinationx, int destinationy);

/*
*	@brief checks what the bullet collided with and respond accordingly
*	@param other sthe entity the bullet collided with
*/
void bullet_collide(Entity *other);

/*
*	@brief returns the bullet's entity
*/
Entity *get_bullet_entity();

/*
*	@brief returns the bullet
*/
Bullet *get_bullet();

void bullet_travel(Entity *self);
#endif