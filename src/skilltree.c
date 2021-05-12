#include "simple_logger.h"

#include "skilltree.h"
#include "player.h"

static SkillTree *skilltree = { 0 };

void skilltree_init()
{
	skilltree = (SkillTree *)gfc_allocate_array(sizeof(SkillTree), 1);

	skilltree->speed_perk = 1; //0 = locked, 1 = unlocked, 2 = hovered, 3 = unlocked
	skilltree->random_powerup_perk = 0;
	skilltree->dash_perk = 0;
	skilltree->all_powerups_perk = 0;
	skilltree->shield_perk = 0;

	skilltree->bullet_speed_perk = 1;
	skilltree->slow_bullets_perk = 0;
	skilltree->strong_bullets_perk = 0;
	skilltree->explode_perk = 0;
	skilltree->hammer_perk = 0;

	Sprite *speed, *random_powerup, *dash, *all_powerups, *shield, 
		*bullet_speed, *slow_bullets, *strong_bullets, *explode, *hammer;

	speed = gf2d_sprite_load_image("images/speed_perk/unlocked.png");
	bullet_speed = gf2d_sprite_load_image("images/bullet_speed_perk/unlocked.png");
	random_powerup = gf2d_sprite_load_image("images/random_powerup_perk/locked.png");
	dash = gf2d_sprite_load_image("images/dash_perk/locked.png");
	slow_bullets = gf2d_sprite_load_image("images/slow_bullets_perk/locked.png");
	strong_bullets = gf2d_sprite_load_image("images/strong_bullets_perk/locked.png");
	all_powerups = gf2d_sprite_load_image("images/all_powerups_perk/locked.png");
	shield = gf2d_sprite_load_image("images/shield_perk/locked.png");
	explode = gf2d_sprite_load_image("images/explode_perk/locked.png");
	hammer = gf2d_sprite_load_image("images/hammer_perk/locked.png");

	skilltree->speed = speed;
	skilltree->random_powerup = random_powerup;
	skilltree->dash = dash;
	skilltree->all_powerups = all_powerups;
	skilltree->shield = shield;
	skilltree->bullet_speed = bullet_speed;
	skilltree->slow_bullets = slow_bullets;
	skilltree->strong_bullets = strong_bullets;
	skilltree->explode = explode;
	skilltree->hammer = hammer;

	return;
}

void skilltree_reset()
{
	skilltree->speed_perk = 1; //0 = locked, 1 = unlocked, 2 = hovered, 3 = unlocked
	skilltree->random_powerup_perk = 0;
	skilltree->dash_perk = 0;
	skilltree->all_powerups_perk = 0;
	skilltree->shield_perk = 0;

	skilltree->bullet_speed_perk = 1;
	skilltree->slow_bullets_perk = 0;
	skilltree->strong_bullets_perk = 0;
	skilltree->explode_perk = 0;
	skilltree->hammer_perk = 0;
}

void skilltree_update()
{
	//Tier 1 Skills
	if (skilltree->speed_perk == 1) skilltree->speed = gf2d_sprite_load_image("images/speed_perk/unlocked.png");
	else if (skilltree->speed_perk == 2) skilltree->speed = gf2d_sprite_load_image("images/speed_perk/hovered.png");
	else if (skilltree->speed_perk == 3) skilltree->speed = gf2d_sprite_load_image("images/speed_perk/redeemed.png");

	if (skilltree->bullet_speed_perk == 1) skilltree->bullet_speed = gf2d_sprite_load_image("images/bullet_speed_perk/unlocked.png");
	else if (skilltree->bullet_speed_perk == 2) skilltree->bullet_speed = gf2d_sprite_load_image("images/bullet_speed_perk/hovered.png");
	else if (skilltree->bullet_speed_perk == 3) skilltree->bullet_speed = gf2d_sprite_load_image("images/bullet_speed_perk/redeemed.png");

	//Tier 2 Skills
	if (skilltree->random_powerup_perk == 0) skilltree->random_powerup = gf2d_sprite_load_image("images/random_powerup_perk/locked.png");
	else if (skilltree->random_powerup_perk == 1) skilltree->random_powerup = gf2d_sprite_load_image("images/random_powerup_perk/unlocked.png");
	else if (skilltree->random_powerup_perk == 2) skilltree->random_powerup = gf2d_sprite_load_image("images/random_powerup_perk/hovered.png");
	else if (skilltree->random_powerup_perk == 3) skilltree->random_powerup = gf2d_sprite_load_image("images/random_powerup_perk/redeemed.png");

	if (skilltree->dash_perk == 0) skilltree->dash = gf2d_sprite_load_image("images/dash_perk/locked.png");
	else if (skilltree->dash_perk == 1) skilltree->dash = gf2d_sprite_load_image("images/dash_perk/unlocked.png");
	else if (skilltree->dash_perk == 2) skilltree->dash = gf2d_sprite_load_image("images/dash_perk/hovered.png");
	else if (skilltree->dash_perk == 3) skilltree->dash = gf2d_sprite_load_image("images/dash_perk/redeemed.png");

	if (skilltree->slow_bullets_perk == 0) skilltree->slow_bullets = gf2d_sprite_load_image("images/slow_bullets_perk/locked.png");
	else if (skilltree->slow_bullets_perk == 1) skilltree->slow_bullets = gf2d_sprite_load_image("images/slow_bullets_perk/unlocked.png");
	else if (skilltree->slow_bullets_perk == 2) skilltree->slow_bullets = gf2d_sprite_load_image("images/slow_bullets_perk/hovered.png");
	else if (skilltree->slow_bullets_perk == 3) skilltree->slow_bullets = gf2d_sprite_load_image("images/slow_bullets_perk/redeemed.png");

	if (skilltree->strong_bullets_perk == 0) skilltree->strong_bullets = gf2d_sprite_load_image("images/strong_bullets_perk/locked.png");
	else if (skilltree->strong_bullets_perk == 1) skilltree->strong_bullets = gf2d_sprite_load_image("images/strong_bullets_perk/unlocked.png");
	else if (skilltree->strong_bullets_perk == 2) skilltree->strong_bullets = gf2d_sprite_load_image("images/strong_bullets_perk/hovered.png");
	else if (skilltree->strong_bullets_perk == 3) skilltree->strong_bullets = gf2d_sprite_load_image("images/strong_bullets_perk/redeemed.png");

	//Tier 3 Skills
	if (skilltree->all_powerups_perk == 0) skilltree->all_powerups = gf2d_sprite_load_image("images/all_powerups_perk/locked.png");
	else if (skilltree->all_powerups_perk == 1) skilltree->all_powerups = gf2d_sprite_load_image("images/all_powerups_perk/unlocked.png");
	else if (skilltree->all_powerups_perk == 2) skilltree->all_powerups = gf2d_sprite_load_image("images/all_powerups_perk/hovered.png");
	else if (skilltree->all_powerups_perk == 3) skilltree->all_powerups = gf2d_sprite_load_image("images/all_powerups_perk/redeemed.png");

	if (skilltree->shield_perk == 0) skilltree->shield = gf2d_sprite_load_image("images/shield_perk/locked.png");
	else if (skilltree->shield_perk == 1) skilltree->shield = gf2d_sprite_load_image("images/shield_perk/unlocked.png");
	else if (skilltree->shield_perk == 2) skilltree->shield = gf2d_sprite_load_image("images/shield_perk/hovered.png");
	else if (skilltree->shield_perk == 3) skilltree->shield = gf2d_sprite_load_image("images/shield_perk/redeemed.png");

	if (skilltree->explode_perk == 0) skilltree->explode = gf2d_sprite_load_image("images/explode_perk/locked.png");
	else if (skilltree->explode_perk == 1) skilltree->explode = gf2d_sprite_load_image("images/explode_perk/unlocked.png");
	else if (skilltree->explode_perk == 2) skilltree->explode = gf2d_sprite_load_image("images/explode_perk/hovered.png");
	else if (skilltree->explode_perk == 3) skilltree->explode = gf2d_sprite_load_image("images/explode_perk/redeemed.png");

	if (skilltree->hammer_perk == 0) skilltree->hammer = gf2d_sprite_load_image("images/hammer_perk/locked.png");
	else if (skilltree->hammer_perk == 1) skilltree->hammer = gf2d_sprite_load_image("images/hammer_perk/unlocked.png");
	else if (skilltree->hammer_perk == 2) skilltree->hammer = gf2d_sprite_load_image("images/hammer_perk/hovered.png");
	else if (skilltree->hammer_perk == 3) skilltree->hammer = gf2d_sprite_load_image("images/hammer_perk/redeemed.png");

	gf2d_sprite_draw_image(skilltree->speed, vector2d(234, 528));
	gf2d_sprite_draw_image(skilltree->random_powerup, vector2d(366, 332));
	gf2d_sprite_draw_image(skilltree->dash, vector2d(103, 332));
	gf2d_sprite_draw_image(skilltree->all_powerups, vector2d(367, 136));
	gf2d_sprite_draw_image(skilltree->shield, vector2d(104, 136));
	gf2d_sprite_draw_image(skilltree->bullet_speed, vector2d(854, 528));
	gf2d_sprite_draw_image(skilltree->slow_bullets, vector2d(723, 332));
	gf2d_sprite_draw_image(skilltree->strong_bullets, vector2d(986, 332));
	gf2d_sprite_draw_image(skilltree->explode, vector2d(987, 136));
	gf2d_sprite_draw_image(skilltree->hammer, vector2d(724, 136));

}

SkillTree *get_skilltree()
{
	return skilltree;
}

/*eol@eof*/
