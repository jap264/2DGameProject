#ifndef __grenade_H__
#define __grenade_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"

/**
* @brief spawn a grenade entity
* @param destinationx location (x) for the entity to travel to
* @param destinationy location (y) for the entity to travel to
* @return NULL on error, or a pointer to a new grenade entity
*/
Entity *grenade_spawn(int destinationx, int destinationy);

void grenade_travel(Entity *self);

#endif