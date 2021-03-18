#ifndef __rocket_H__
#define __rocket_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"

typedef struct Rocket_S
{
	Entity *ent;
	Entity *explosion;
	Bool	alive;

}Rocket;

void rocket_init();

/**
* @brief spawn a rocket entity
* @return NULL on error, or a pointer to a new rocket entity
*/
Entity *rocket_spawn();

/**
* @brief spawn a explosion entity
* @return NULL on error, or a pointer to a new rocket entity
*/
Entity *explosion_spawn(Vector2D *position);

void *rocket_explode(Entity *self);

void rocket_travel(Entity *self);

Rocket *get_rocket();

#endif