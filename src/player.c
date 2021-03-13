#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "bullet.h"

void player_update(Entity *self);
void player_think(Entity *self);

static Player *player = { 0 };

Entity *player_spawn(Vector2D position)
{
	player = (Player *)gfc_allocate_array(sizeof(Player), 1);
	Entity *ent = ent = entity_new();
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

	// turn aimdir into a unit vector
	vector2d_normalize(&aimdir);
	// check for motion
	if (keys[SDL_SCANCODE_W])
	{
		self->position.y -= 3;
		/*vector2d_scale(thrust, aimdir, 2);
		vector2d_add(self->velocity, self->velocity, thrust);*/
	}
	
	else if (keys[SDL_SCANCODE_S])
	{
		self->position.y += 3;
		/*vector2d_scale(thrust, aimdir, -2);
		vector2d_add(self->velocity, self->velocity, thrust);*/
	}
	
	if (keys[SDL_SCANCODE_A])
	{
		self->position.x -= 3;
		/*vector2d_scale(thrust, vector2d(aimdir.x+1,aimdir.y+1), 2);
		vector2d_add(self->velocity, self->velocity, thrust);*/
	}
	
	else if (keys[SDL_SCANCODE_D])
	{
		self->position.x += 3;
		/*vector2d_scale(thrust, vector2d(aimdir.x+1,aimdir.y+1), 2);
		vector2d_add(self->velocity, self->velocity, thrust);*/
	}

	if (SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT)) bullet_spawn(mx, my);

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