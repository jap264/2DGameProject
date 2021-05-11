#ifndef __SKILL_TREE_H__
#define __SKILL_TREE_H__

#include "gfc_types.h"
#include "gf2d_sprite.h"

typedef struct
{
	int		all_powerups_perk; //0 = locked, 1 = unlocked, 2 = hovered, 3 = redeemed
	int		bullet_speed_perk;
	int		dash_perk;
	int		explode_perk;
	int		hammer_perk;
	int		random_powerup_perk;
	int		shield_perk;
	int		slow_bullets_perk;
	int		speed_perk;
	int		strong_bullets_perk;
	Sprite	*speed;
	Sprite	*random_powerup;
	Sprite	*dash;
	Sprite	*all_powerups;
	Sprite	*shield;
	Sprite	*bullet_speed;
	Sprite	*slow_bullets;
	Sprite	*strong_bullets;
	Sprite	*explode;
	Sprite  *hammer;

}SkillTree;

/*
* @brief initializes the skill tree
*/
void skilltree_init();

/*
* @brief resets the skill tree to default
*/
void skilltree_reset();

/*
* @brief updates the skill tree
*/
void skilltree_update();

/*
* @brief returns the skill tree
*/
SkillTree *get_skilltree();
#endif