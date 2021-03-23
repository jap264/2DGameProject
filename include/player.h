#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"
#include "shape.h"

typedef struct Player_S
{
	Entity *ent;
	int maxHealth;
	Bool alive;
	int points;
	int enemiesKilled;
	int currWeapon;
	Bool p_speed;
	Bool p_firerate;
	Bool p_invinc;
	Bool p_instakill;
	Bool frozen;

}Player;

/**
* @brief spawn a player entity
* @param position the screen position to spawn the player at
* @return NULL on error, or a pointer to a new player entity
*/
Entity *player_spawn(Vector2D position);

/**
* @brief spawn a player entity
* @param position the screen position to respawn the player at
* @return NULL on error, or a pointer to a new player entity
*/
Entity *player_respawn(Vector2D position);

/*
*	@brief checks what the player collided with and respond accordingly
*	@param other the entity the player collided with
*/
void player_collide(Entity *other);

/*
*	@brief player has lost all health
*/
void player_die();

/*
*	@brief returns the player's entity
*/
Entity *get_player_entity();

/*
*	@brief returns the player
*/
Player *get_player();

/*
*	@brief returns the player's health
*/
int *get_player_health();

#endif