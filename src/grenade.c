#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "grenade.h"

void grenade_update(Entity *self);
void grenade_think(Entity *self);

Entity *grenade_spawn(int destinationx, int destinationy)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the grenade");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/pistol_round.png");
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x + 50;
	spawn.y = get_player_entity()->position.y + 50;
	vector2d_copy(ent->position, spawn);
	ent->destinationx = destinationx;
	ent->destinationy = destinationy;
	ent->update = grenade_update;
	ent->think = grenade_think;
	ent->ttv = 200;
	ent->speed = 2;
	grenade_travel(ent);
	return ent;
}

void grenade_update(Entity *self)
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

void grenade_think(Entity *self)
{
	if (!self) return;
	//need a fail safe to delete grenades
	self->ttv--;
	if (self->ttv == 0) entity_free(self);
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