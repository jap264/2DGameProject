#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"

/**
* @brief spawn a health powerup entity
* @param position (x,y) location to spawn health powerup
* @return NULL on error, or a pointer to a new health powerup entity
* @note restores player's health to full
*/
Entity *p_health_spawn(Vector2D position);

/**
* @brief spawn a speed powerup entity
* @param position (x,y) location to spawn speed powerup
* @return NULL on error, or a pointer to a new speed powerup entity
* @note doubles player's speed for a duration
*/
Entity *p_speed_spawn(Vector2D position);

/**
* @brief spawn a firerate powerup entity
* @param position (x,y) location to spawn firerate powerup
* @return NULL on error, or a pointer to a new firerate powerup entity
* @note doubles player's firerate for a duration
*/
Entity *p_firerate_spawn(Vector2D position);

/**
* @brief spawn a invinc powerup entity
* @param position (x,y) location to spawn invinc powerup
* @return NULL on error, or a pointer to a new invinc powerup entity
* @note doubles player's invinc for a duration
*/
Entity *p_invinc_spawn(Vector2D position);


/**
* @brief spawn a instakill powerup entity
* @param position (x,y) location to spawn instakill powerup
* @return NULL on error, or a pointer to a new instakill powerup entity
* @note doubles player's instakill for a duration
*/
Entity *p_instakill_spawn(Vector2D position);

void random_powerup_spawn();
#endif