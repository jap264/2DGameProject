#ifndef __HAMMER_H__
#define __HAMMER_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"

/**
* @brief spawn a mine entity
* @return NULL on error, or a pointer to a new mine entity
*/
Entity *ground_pound_spawn();

#endif