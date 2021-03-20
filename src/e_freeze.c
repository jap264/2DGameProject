#include "simple_logger.h"

#include "e_freeze.h"
#include "camera.h"
#include "entity.h"

void freeze_update(Entity *self);
void freeze_think(Entity *self);

static Freeze *freeze = { 0 };

Entity *freeze_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the freeze");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/e_freeze.png");
	vector2d_copy(ent->position, position);
	ent->update = freeze_update;
	ent->think = freeze_think;
	ent->rotation.x = 32;
	ent->rotation.y = 32;
	ent->health = 5;
	return ent;
}


void freeze_update(Entity *self)
{
	if (!self)return;

	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void freeze_think(Entity *self)
{
	const Uint8 *keys;
	Vector2D aimdir, thrust;
	float angle;
	int mx, my;
	if (!self)return;
	
	mx = get_player_entity()->position.x + 30;
	my = get_player_entity()->position.y + 30;

	aimdir.x = mx - (self->position.x);
	aimdir.y = my - (self->position.y);
	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;

	// turn aimdir into a unit vector
	vector2d_normalize(&aimdir);
	// check for motion

	vector2d_scale(thrust, aimdir, 1.8);
	vector2d_add(self->velocity, self->velocity, thrust);

}