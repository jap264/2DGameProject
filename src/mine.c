#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "mine.h"

void mine_update(Entity *self);
void mine_think(Entity *self);

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
	ent->ttv = 400;

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
	ent->ttv = 100;

	return ent;
}

void mine_update(Entity *self)
{
	//Vector2D camera;
	//Vector2D cameraSize;

	//if (!self)return;
	//cameraSize = camera_get_dimensions();
	//camera.x = (self->position.x + 64) - (cameraSize.x * 0.5);
	//camera.y = (self->position.y + 64) - (cameraSize.y * 0.5);
	//camera_set_position(camera);
	// apply dampening on velocity
	//vector2d_scale(self->velocity, self->velocity, 0.75);
	//if (vector2d_magnitude_squared(self->velocity) < 2)
	//{
	//	vector2d_clear(self->velocity);
	//}
}

void mine_think(Entity *self)
{
	if (!self) return;
	if (self->ttv == 1) mine_explosion_spawn(self->position);
}
