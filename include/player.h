#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "SDL.h"
#include "gfc_vector.h"

#include "entity.h"
#include "gfc_types.h"

typedef struct Player_S
{
	Entity *ent;
	int health;
	int maxHealth;
	int status; //alive or dead
	int points;
	int enemiesKilled;
	int currWeapon;
	Bool p_speed;
	Bool p_firerate;
	Bool p_invinc;

}Player;

/**
* @brief spawn a player entity
* @param position the screen position to spawn the player at
* @return NULL on error, or a pointer to a new player entity
*/
Entity *player_spawn(Vector2D position);

/*
*	@brief checks what the player collided with and respond accordingly
*	@param other sthe entity the player collided with
*/
void player_collide(Entity *other);

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