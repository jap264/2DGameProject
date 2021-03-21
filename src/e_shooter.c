#include "simple_logger.h"

#include "e_shooter.h"
#include "camera.h"
#include "entity.h"

void shooter_update(Entity *self);
void shooter_think(Entity *self);

static Shooter *shooter = { 0 };

Entity *shooter_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the shooter");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/e_shooter.png");
	vector2d_copy(ent->position, position);
	ent->update = shooter_update;
	ent->think = shooter_think;
	ent->rotation.x = 32;
	ent->rotation.y = 32;
	ent->health = 1;
	ent->ent_type = 2;
	return ent;
}

Entity *pellet_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the shooter");
		return NULL;
	}

	Vector2D pos;
	pos.x = position.x + 15;
	pos.y = position.y + 15;

	ent->sprite = gf2d_sprite_load_image("images/pellet.png");
	vector2d_copy(ent->position, pos);
	ent->speed = 4;
	ent->health = 1;
	ent->ent_type = 2;


	Vector2D aimdir, thrust;
	float angle;
	int mx, my;

	mx = get_player_entity()->position.x + 30;
	my = get_player_entity()->position.y + 30;

	aimdir.x = mx - (ent->position.x);
	aimdir.y = my - (ent->position.y);

	// turn aimdir into a unit vector
	vector2d_normalize(&aimdir);
	// check for motion

	vector2d_scale(thrust, aimdir, ent->speed);
	vector2d_add(ent->velocity, ent->velocity, thrust);
}


void shooter_update(Entity *self)
{
	if (!self)return;

	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void shooter_think(Entity *self)
{
	Vector2D aimdir, thrust;
	float angle;
	int mx, my;
	if (!self)return;
	
	mx = get_player_entity()->position.x;
	my = get_player_entity()->position.y;

	aimdir.x = mx - (self->position.x+32);
	aimdir.y = my - (self->position.y+32);
	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;

	// turn aimdir into a unit vector
	vector2d_normalize(&aimdir);
	// check for motion

	vector2d_scale(thrust, aimdir, 1.2);
	vector2d_add(self->velocity, self->velocity, thrust);

	if (SDL_GetTicks() % 100 == 0) pellet_spawn(self->position);
}