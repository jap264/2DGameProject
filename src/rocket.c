#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "rocket.h"

void rocket_update(Entity *self);
void rocket_think(Entity *self);
void explosion_update(Entity *self);
void rocket_collide(Entity *self);
static Rocket *rocket = { 0 };

void rocket_init()
{
	rocket = (Rocket *)gfc_allocate_array(sizeof(Rocket), 1);
	rocket->alive = false;
}

Entity *rocket_spawn()
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the rocket");
		return NULL;
	}
	rocket->ent = ent;
	rocket->ent->sprite = gf2d_sprite_load_image("images/rocket.png");
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x+50;
	spawn.y = get_player_entity()->position.y+50;
	vector2d_copy(ent->position, spawn);
	rocket->ent->rotation.x = 16;
	rocket->ent->rotation.y = 16;
	rocket->ent->update = rocket_update;
	rocket->ent->think = rocket_think;
	rocket->ent->collide = rocket_collide;
	rocket->ent->ttv = 500;
	rocket->ent->speed = 4;
	ent->ent_type = 1;
	ent->dmg = 0;
	rocket->alive = true;

	return rocket->ent;
}

Entity *explosion_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the rocket");
		return NULL;
	}

	rocket->explosion = ent;
	rocket->explosion->sprite = gf2d_sprite_load_image("images/explosion_large.png");
	rocket->explosion->position = position;
	rocket->explosion->ttv = 100;
	rocket->explosion->ent_type = 6;
	rocket->explosion->update = explosion_update;

	return rocket->explosion;
}

void rocket_collide(Entity *self, Entity *other)
{
	if (!self || !other) return;

	if (other->ent_type != 2) return;
	
	rocket_explode(self);
}

void rocket_update(Entity *self)
{
	if (!self)return;

	self->circle = shape_circle(self->position.x + 16, self->position.y + 16, 8);

	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void explosion_update(Entity *self)
{
	self->circle = shape_circle(self->position.x + 32, self->position.y + 32, 16);
}

void rocket_think(Entity *self)
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
	aimdir.x = mx - (self->position.x); //where its going to
	aimdir.y = my - (self->position.y);
	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;
	
	vector2d_normalize(&aimdir);

	vector2d_scale(thrust, aimdir, 1.99);
	vector2d_add(self->velocity, self->velocity, thrust);

	//need a fail safe to delete rockets
	if (self->ttv == 1) rocket_explode(self);
}

void *rocket_explode(Entity *self)
{
	Vector2D position = self->position;
	position.x -= 16;
	position.y -= 16;
	explosion_spawn(position);
	rocket->alive = false;
}

Rocket *get_rocket()
{
	return rocket;
}