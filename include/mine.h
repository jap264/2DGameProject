#ifndef __MINE_H__
#define __MINE_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"

/**
* @brief spawn a mine entity
* @return NULL on error, or a pointer to a new mine entity
*/
Entity *mine_spawn();

Entity *mine_explosion_spawn(Vector2D position);

void mine_travel(Entity *self);

#endif