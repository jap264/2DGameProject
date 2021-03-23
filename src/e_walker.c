#include "simple_logger.h"

#include "e_walker.h"
#include "camera.h"
#include "entity.h"

void walker_update(Entity *self);
void walker_think(Entity *self);

static Walker *walker = { 0 };

Entity *walker_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the walker");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/e_walker.png");
	vector2d_copy(ent->position, position);
	ent->update = walker_update;
	ent->think = walker_think;
	ent->collide = walker_collide;
	ent->rotation.x = 32;
	ent->rotation.y = 32;
	ent->health = 3;
	ent->ent_type = 2;

	return ent;
}

void walker_collide(Entity *self, Entity *other)
{
	if (!self || !other) return;
	
	if (other->ent_type == 1)
	{
		if (other->dmg != NULL) self->health -= other->dmg;
		entity_free(other);
	}

	if (self->health <= 0 || other->ent_type == 6) entity_free(self);
}

void walker_update(Entity *self)
{
	if (!self)return;

	self->circle = shape_circle(self->position.x + 32, self->position.y + 32, 16);

	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void walker_think(Entity *self)
{
	const Uint8 *keys;
	Vector2D aimdir, thrust;
	float angle;
	int mx, my;
	if (!self)return;
	
	mx = get_player_entity()->position.x + 64;
	my = get_player_entity()->position.y + 64;

	aimdir.x = mx - (self->position.x + 32);
	aimdir.y = my - (self->position.y + 32);
	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;

	// turn aimdir into a unit vector
	vector2d_normalize(&aimdir);
	// check for motion

	vector2d_scale(thrust, aimdir, 1.4);
	vector2d_add(self->velocity, self->velocity, thrust);

}