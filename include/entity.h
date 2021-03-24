#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gf2d_sprite.h"
#include "shape.h"

typedef struct Entity_s
{
	Bool       _inuse;
	Vector2D    position;
	Vector2D    velocity;
	Vector3D    rotation; //(x,y) = rotation center, z = degrees of rotation
	Sprite     *sprite;
	ShapeCircle	circle;
	float       frame;
	float       frameRate;
	int         frameCount;
	void		(*update)(struct Entity_s *self);
	void		(*think)(struct Entity_s *self);
	void		(*draw)(struct Entity_s *self);
	void		(*free)(struct Entity_s *self);
	void		(*collide)(struct Entity_s *other);
	void       *data;
	int			ent_type;	//0 = player, 1 = player projectiles, 2 = enemies, 3 = enemy projectiles, 4 = powerups, 5 = e_freeze, 6 = p_projectiles that don't die, 7 = melee boss, 8 = projectile boss, 9 = minions, 10 = reverse cannonball
	int			powerup;	//0 = health, 1 = speed, 2 = firerate, 3 = invinc, 4 = instakill
	int			weapon;		//0 = bullet, 1 = explosion, 2 = thundergun, 3 = hammer, 4 = rocket
	int			destinationx;
	int			destinationy;
	int			ttv;	//time to live
	int			speed;	//used for projectiles
	int			dmg;	//used for projectiles
	int			health;
	int			glitch; //used for delay of tp mob

}Entity;

/**
* @brief initialize internal entity management system
* @param max_entities how many concurrent entities to support
*/
void entity_manager_init(Uint32 max_entities);

/**
* @brief calls update function on all entities
*/
void entity_manager_update_entities();

/**
* @brief call think function for all entities
*/
void entity_manager_think_entities();

/**
* @brief call draw on all entities
*/
void entity_manager_draw_entities();


/**
* @brief free all entities in the system and destroy entity manager
*/
void entity_manager_free();

/**
* @brief allocate an entity, initialize it to zero and return a pointer to it
* @return NULL on error (see logs) or a pointer to an initialized entity.
*/
Entity *entity_new();

/**
* @brief frees provided entity
* @param ent the entity to free
*/
void entity_free(Entity *ent);

/**
* @brief draws an entity to the current render frame
* @param ent the entity to draw
*/
void entity_draw(Entity *ent);

/*
*	@brief makes an entity follow another entity
*	@param self entity that is following
*	@param other entity that is being followed
*	@param speed distance to move every frame
*/
void follow(Entity *self, Entity *other, float speed);

/*
*	@brief checks collisions between all entities
*/
void check_all_collisions();

#endif