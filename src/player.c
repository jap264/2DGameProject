#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "bullet.h"
#include "rocket.h"
#include "mine.h"

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
	player->ent->rotation.x = 64;
	player->ent->rotation.y = 64;
	player->ent->speed = 3;
	player->maxHealth = 3;
	player->health = player->maxHealth;
	player->currWeapon = 1;
	player->p_speed = false;
	player->p_firerate = false;
	player->p_invinc = false;
	return player->ent;
}


void player_update(Entity *self)
{
	Vector2D camera;
	Vector2D cameraSize;

	if (!self)return;
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
	camera = camera_get_position();
	mx += camera.x;
	my += camera.y;
	aimdir.x = mx - (self->position.x + 64);
	aimdir.y = my - (self->position.y + 64);
	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;

	if (player->p_speed == true) self->speed = 6;
	else self->speed = 3;

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
	return player->health;
}