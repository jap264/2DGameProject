#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "bullet.h"
#include "rocket.h"
#include "mine.h"
#include "shape.h"

void player_update(Entity *self);
void player_think(Entity *self);

static Player *player = { 0 };
static int pistolDelay = 0;
static int smgDelay = 0;
static int shotgunDelay = 0;
static int lmgDelay = 0;
static int sniperDelay = 0;
static int thunderDelay = 0;
static int grenadeDelay = 0;
static int mineDelay = 0;
static int hammerDelay = 0;
static int frozenDelay = 0;
static int p_speedDelay = 0;
static int p_firerateDelay = 0;
static int p_invincDelay = 0;
static int p_instakillDelay = 0;

Entity *player_spawn(Vector2D position)
{
	player = (Player *)gfc_allocate_array(sizeof(Player), 1);
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the player");
		return NULL;
	}
	player->ent = ent;
	player->ent->sprite = gf2d_sprite_load_all("images/ed210_top.png", 128, 128, 16);
	vector2d_copy(player->ent->position, position);
	player->ent->frameRate = 0.1;
	player->ent->frameCount = 16;
	player->ent->update = player_update;
	player->ent->think = player_think;
	player->ent->collide = player_collide;
	player->ent->rotation.x = 64;
	player->ent->rotation.y = 64;
	player->ent->speed = 3;
	player->maxHealth = 3;
	player->ent->health = player->maxHealth;
	player->currWeapon = 1;
	player->ent->ent_type = 0;
	player->p_speed = false;
	player->p_firerate = false;
	player->p_invinc = false;
	player->frozen = false;
	player->alive = true;
	return player->ent;
}

Entity *player_respawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the player");
		return NULL;
	}
	player->ent = ent;
	player->ent->sprite = gf2d_sprite_load_all("images/ed210_top.png", 128, 128, 16);
	vector2d_copy(player->ent->position, position);
	player->ent->frameRate = 0.1;
	player->ent->frameCount = 16;
	player->ent->update = player_update;
	player->ent->think = player_think;
	player->ent->collide = player_collide;
	player->ent->rotation.x = 64;
	player->ent->rotation.y = 64;
	player->ent->speed = 3;
	player->maxHealth = 3;
	player->ent->health = player->maxHealth;
	player->currWeapon = 1;
	player->ent->ent_type = 0;
	player->p_speed = false;
	player->p_firerate = false;
	player->p_invinc = false;
	player->frozen = false;
	player->alive = true;
	return player->ent;
}

void player_die()
{
	player->ent->health = 0;
	entity_free(player->ent);
	player->alive = false;
}

void player_collide(Entity *self, Entity *other)
{
	if (!self || !other) return;

	//ignore player projectiles
	if (other->ent_type == 1 
		|| other->ent_type == 0 
		|| other->ent_type == 6) return;

	slog("p_collision, ent type: %i", other->ent_type);
	
	//check if powerup
	if (other->ent_type == 4)
	{
		//check type of powerup
		if (other->powerup == 0) //health
		{
			player->ent->health = player->maxHealth;
		}

		else if (other->powerup == 1) //speed
		{
			player->p_speed = true;
			p_speedDelay = 1000;
		}

		else if (other->powerup == 2) //firerate
		{
			player->p_firerate = true;
			p_firerateDelay = 1000;
		}

		else if (other->powerup == 3) //invinc
		{
			player->p_invinc = true;
			p_invincDelay = 1000;
		}

		else if (other->powerup == 4) //instakill
		{
			player->p_instakill = true;
			p_instakillDelay = 1000;
		}

		entity_free(other);
	}

	//check if e_freeze
	else if (other->ent_type == 5)
	{

		player->frozen = true;
		frozenDelay += 300;
		slog("freeze");

		entity_free(other);
	}

	//check if enemy, enemy projectile, or minion
	else if (other->ent_type == 2 || other->ent_type == 3 || other->ent_type == 9)
	{
		// check if player is invincible
		if (player->p_invinc == false) player->ent->health--;
		else slog("player is invincible and cannot take damage.");

		//free the entity of the projectile
		entity_free(other);
	}

	else if (other->ent_type == 7 || other->ent_type == 8)
	{
		player_die();
	}
}

void player_update(Entity *self)
{
	Vector2D camera;
	Vector2D cameraSize;

	if (!self)return;
	
	self->circle = shape_circle(self->position.x + 64, self->position.y + 64, 32);
	
	if (frozenDelay > 0) frozenDelay--;
	if (frozenDelay <= 0) player->frozen = false;

	if (p_speedDelay > 0) p_speedDelay--;
	if (p_speedDelay <= 0) player->p_speed = false;

	if (p_firerateDelay > 0) p_firerateDelay--;
	if (p_firerateDelay <= 0) player->p_firerate = false;

	if (p_invincDelay > 0) p_invincDelay--;
	if (p_invincDelay <= 0) player->p_invinc = false;

	if (p_instakillDelay > 0) p_instakillDelay--;
	if (p_instakillDelay <= 0) player->p_instakill = false;

	if (player->p_speed == true) self->speed = 6;
	else if (player->frozen == true) self->speed = 1;
	else self->speed = 3;

	cameraSize = camera_get_dimensions();
	camera.x = (self->position.x + 64) - (cameraSize.x * 0.5);
	camera.y = (self->position.y + 64) - (cameraSize.y * 0.5);
	camera_set_position(camera);
	// apply dampening on velocity
	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void player_think(Entity *self)
{
	const Uint8 *keys;
	Vector2D aimdir, camera, thrust;
	float angle;
	int mx, my;
	if (!self)return;
	keys = SDL_GetKeyboardState(NULL);
	SDL_GetMouseState(&mx, &my);
	/*camera = camera_get_position();
	mx += camera.x;
	my += camera.y;*/
	aimdir.x = mx - (self->position.x + 64);
	aimdir.y = my - (self->position.y + 64);
	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;

	// turn aimdir into a unit vector
	vector2d_normalize(&aimdir);
	// check for motion
	if (player->currWeapon != 4)
	{
		if (keys[SDL_SCANCODE_W])
		{
			self->position.y -= self->speed;
			/*vector2d_scale(thrust, aimdir, 2);
			vector2d_add(self->velocity, self->velocity, thrust);*/
		}
	
		else if (keys[SDL_SCANCODE_S])
		{
			self->position.y += self->speed;
			/*vector2d_scale(thrust, aimdir, -2);
			vector2d_add(self->velocity, self->velocity, thrust);*/
		}
	
		if (keys[SDL_SCANCODE_A])
		{
			self->position.x -= self->speed;
			/*vector2d_scale(thrust, vector2d(aimdir.x+1,aimdir.y+1), 2);
			vector2d_add(self->velocity, self->velocity, thrust);*/
		}
	
		else if (keys[SDL_SCANCODE_D])
		{
			self->position.x += self->speed;
			/*vector2d_scale(thrust, vector2d(aimdir.x+1,aimdir.y+1), 2);
			vector2d_add(self->velocity, self->velocity, thrust);*/
		}
	}

	if (pistolDelay > 0) pistolDelay--;
	if (smgDelay > 0) smgDelay--;
	if (shotgunDelay > 0) shotgunDelay--;
	if (lmgDelay > 0) lmgDelay--;
	if (sniperDelay > 0) sniperDelay--;
	if (thunderDelay > 0) thunderDelay--;
	if (grenadeDelay > 0) grenadeDelay--;
	if (mineDelay > 0) mineDelay--;
	if (hammerDelay > 0) hammerDelay--;

	if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		switch (player->currWeapon)
		{
			case 1:
				if (pistolDelay == 0)
				{
					pistol_round_spawn(mx, my);
					if (player->p_firerate == false) pistolDelay = 50;
					else pistolDelay = 25;
				}
				break;

			case 2:
				if (smgDelay == 0)
				{
					light_round_spawn(mx, my);
					if (player->p_firerate == false) smgDelay = 20;
					else smgDelay = 10;
				}
				break;

			case 3:
				if (shotgunDelay == 0)
				{
					shotgun_shells_spawn(mx, my);
					if (player->p_firerate == false) shotgunDelay = 40;
					else shotgunDelay = 20;
				}
				break;

			case 4:
				if(lmgDelay == 0)
				{
					heavy_round_spawn(mx, my);
					if (player->p_firerate == false) lmgDelay = 10;
					else lmgDelay = 5;
				}
				break;

			case 5:
				if (sniperDelay == 0)
				{
					sniper_round_spawn(mx, my);
					if (player->p_firerate == false) sniperDelay = 100;
					else sniperDelay = 50;
				}
				break;

			case 6:
				if (!get_rocket()->alive)
				{
					rocket_spawn();
				}
				break;

			case 7:
				if (thunderDelay == 0)
				{
					thunderwave_spawn(mx,my);
					if (player->p_firerate == false) thunderDelay = 120;
					else thunderDelay = 60;
				}
				break;

			case 8:
				if (grenadeDelay == 0)
				{
					grenade_spawn(mx, my);
					if (player->p_firerate == false) grenadeDelay = 40;
					else grenadeDelay = 20;
				}
				break;

			case 9:
				if (mineDelay == 0)
				{
					mine_spawn();
					if (player->p_firerate == false) mineDelay = 15;
					else mineDelay = 8;
				}
				break;

			case 10:
				if (hammerDelay == 0)
				{
					ground_pound_spawn();
					if (player->p_firerate == false) hammerDelay = 100;
					else hammerDelay = 50;
				}
				break;
		}
	}

	if (player->ent->health <= 0) player_die();
}

Entity *get_player_entity()
{
	return player->ent;
}

Player *get_player()
{
	return player;
}

int *get_player_health()
{
	return player->ent->health;
}