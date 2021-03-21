#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "hammer.h"

void hammer_update(Entity *self);
void hammer_think(Entity *self);

Entity *ground_pound_spawn()
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the mine");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_all("images/ground_pound.png", 128, 128, 5);
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x;
	spawn.y = get_player_entity()->position.y;
	ent->frameRate = 0.05;
	ent->frameCount = 5;
	vector2d_copy(ent->position, spawn);
	ent->update = hammer_update;
	ent->think = hammer_think;
	ent->ttv = 100;
	ent->ent_type = 1;

	return ent;
}

void hammer_update(Entity *self)
{
	if (!self) return;
}

void hammer_think(Entity *self)
{
	if (!self) return;
	self->position = get_player_entity()->position;
}
