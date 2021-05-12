#include "simple_logger.h"

#include "e_freeze.h"
#include "camera.h"
#include "entity.h"
#include "sounds.h"
#include "wavesystem.h"
#include "rocket.h"
#include "skilltree.h"

void freeze_update(Entity *self);
void freeze_think(Entity *self);
void freeze_collide(Entity *self);

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
	ent->collide = freeze_collide;
	ent->rotation.x = 32;
	ent->rotation.y = 32;
	ent->health = 5;
	ent->ent_type = 5;
	get_wavesystem()->enemyCount++;
	return ent;
}

void freeze_collide(Entity *self, Entity *other)
{
	if (!self || !other) return;

	if (other->ent_type == 1)
	{
		if (other->dmg != NULL) self->health -= other->dmg;
		entity_free(other);
	}

	if (self->health <= 0 || other->ent_type == 6)
	{
		get_player()->inARow++;
		get_player()->enemiesKilled++;
		sounds_play_enemydeath();
		if (get_skilltree()->explode_perk == 3) explosion_spawn(self->position);
		get_wavesystem()->enemyCount--;
		entity_free(self);
	}
}

void freeze_update(Entity *self)
{
	if (!self)return;

	self->circle = shape_circle(self->position.x + 32, self->position.y + 32, 16);

	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void freeze_think(Entity *self)
{
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

	vector2d_scale(thrust, aimdir, 1.885);
	vector2d_add(self->velocity, self->velocity, thrust);

}