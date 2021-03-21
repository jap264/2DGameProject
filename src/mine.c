#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "mine.h"

void mine_update(Entity *self);
void mine_think(Entity *self);
void mine_collide(Entity *self);
void mine_explosion_update(Entity *self);

Entity *mine_spawn()
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the mine");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/mine.png");
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x + 50;
	spawn.y = get_player_entity()->position.y + 50;
	vector2d_copy(ent->position, spawn);
	ent->update = mine_update;
	ent->think = mine_think;
	ent->collide = mine_collide;
	ent->ttv = 1000;
	ent->ent_type = 1;

	return ent;
}

Entity *mine_explosion_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the rocket");
		return NULL;
	}

	ent->sprite = gf2d_sprite_load_image("images/explosion_small.png");
	ent->position = position;
	ent->update = mine_explosion_update;

	ent->ttv = 100;
	ent->ent_type = 6;

	return ent;
}

void mine_collide(Entity *self, Entity *other)
{
	if (!self || !other) return;

	if (other->ent_type != 2) return;

	entity_free(self);
	mine_explosion_spawn(self->position);
}

void mine_update(Entity *self)
{
	self->circle = shape_circle(self->position.x + 16, self->position.y + 16, 8);
}

void mine_explosion_update(Entity *self)
{
	self->circle = shape_circle(self->position.x + 16, self->position.y + 16, 8);
}

void mine_think(Entity *self)
{
	if (!self) return;
	if (self->ttv == 1) mine_explosion_spawn(self->position);
}
