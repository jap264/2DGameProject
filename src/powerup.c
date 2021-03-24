#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "powerup.h"

void powerup_update(Entity *self);
void powerup_think(Entity *self);
void powerup_collide(Entity *self);

static int integer(float f)
{
	int result = f;
	return result;
}

static int randNum()
{
	return integer(gfc_crandom() * 5 + 5);
}

Entity *p_health_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the powerup");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/p_health.png");
	Vector2D spawn;
	spawn.x = position.x + 16;
	spawn.y = position.y + 16;
	vector2d_copy(ent->position, spawn);
	ent->update = powerup_update;
	ent->think = powerup_think;
	ent->collide = powerup_collide;
	ent->ttv = 1000;
	ent->ent_type = 4;
	ent->powerup = 0;

	return ent;
}

Entity *p_speed_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the powerup");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/p_speed.png");
	Vector2D spawn;
	spawn.x = position.x + 16;
	spawn.y = position.y + 16;
	vector2d_copy(ent->position, spawn);
	ent->update = powerup_update;
	ent->think = powerup_think;
	ent->collide = powerup_collide;
	ent->ttv = 1000;
	ent->ent_type = 4;
	ent->powerup = 1;

	return ent;
}

Entity *p_firerate_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the powerup");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/p_firerate.png");
	Vector2D spawn;
	spawn.x = position.x + 16;
	spawn.y = position.y + 16;
	vector2d_copy(ent->position, spawn);
	ent->update = powerup_update;
	ent->think = powerup_think;
	ent->collide = powerup_collide;
	ent->ttv = 1000;
	ent->ent_type = 4;
	ent->powerup = 2;

	return ent;
}

Entity *p_invinc_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the powerup");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/p_invinc.png");
	Vector2D spawn;
	spawn.x = position.x + 16;
	spawn.y = position.y + 16;
	vector2d_copy(ent->position, spawn);
	ent->update = powerup_update;
	ent->think = powerup_think;
	ent->collide = powerup_collide;
	ent->ttv = 1000;
	ent->ent_type = 4;
	ent->powerup = 3;

	return ent;
}

Entity *p_instakill_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the powerup");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/p_instakill.png");
	Vector2D spawn;
	spawn.x = position.x + 16;
	spawn.y = position.y + 16;
	vector2d_copy(ent->position, spawn);
	ent->update = powerup_update;
	ent->think = powerup_think;
	ent->collide = powerup_collide;
	ent->ttv = 1000;
	ent->ent_type = 4;
	ent->powerup = 4;

	return ent;
}

void powerup_update(Entity *self)
{
	if (!self) return;
	self->circle = shape_circle(self->position.x + 16, self->position.y + 16, 8);
}

void powerup_think(Entity *self)
{
	if (!self) return;

}

void powerup_collide(Entity *self)
{
	if (!self) return;

}