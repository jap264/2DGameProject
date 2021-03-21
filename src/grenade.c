#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "grenade.h"

void grenade_update(Entity *self);
void grenade_think(Entity *self);
void grenade_explosion_update(Entity *self);

Entity *grenade_spawn(int destinationx, int destinationy)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the grenade");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/grenade.png");
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x + 50;
	spawn.y = get_player_entity()->position.y + 50;
	vector2d_copy(ent->position, spawn);
	ent->destinationx = destinationx;
	ent->destinationy = destinationy;
	ent->think = grenade_think;
	ent->ttv = 200;
	ent->speed = 2;
	ent->ent_type = 1;
	grenade_travel(ent);
	return ent;
}

Entity *grenade_explosion_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the rocket");
		return NULL;
	}

	ent->sprite = gf2d_sprite_load_image("images/explosion_large.png");
	Vector2D spawn;
	spawn.x = position.x - 24;
	spawn.y = position.y - 24;
	ent->position = spawn;
	ent->ttv = 100;
	ent->ent_type = 6;
	ent->update = grenade_explosion_update;

	return ent;
}

void grenade_explosion_update(Entity *self)
{
	self->circle = shape_circle(self->position.x + 32, self->position.y + 32, 16);
}

void grenade_think(Entity *self)
{
	if (!self) return;
	
	if (self->ttv == 100) vector2d_clear(self->velocity);
	if (self->ttv == 1) grenade_explosion_spawn(self->position);
}



void grenade_travel(Entity *self)
{
	if (!self) return;
	int mx = self->destinationx, my = self->destinationy;
	Vector2D aimdir, camera, thrust;
	mx += camera.x;
	my += camera.y;
	aimdir.x = mx - (self->position.x);
	aimdir.y = my - (self->position.y);
	vector2d_normalize(&aimdir);
	vector2d_scale(thrust, aimdir, self->speed);
	vector2d_add(self->velocity, self->velocity, thrust);
}