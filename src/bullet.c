#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "bullet.h"

void bullet_update(Entity *self);
void bullet_think(Entity *self);

static Bullet *bullet = { 0 };

Entity *bullet_spawn(int destinationx, int destinationy)
{
	bullet = (Bullet *)gfc_allocate_array(sizeof(Bullet), 1);
	Entity *ent = ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the bullet");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/bullet.png");
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x + 50;
	spawn.y = get_player_entity()->position.y + 50;
	vector2d_copy(ent->position, spawn);
	ent->destinationx = destinationx;
	ent->destinationy = destinationy;
	ent->update = bullet_update;
	ent->think = bullet_think;
	bullet_travel(ent);
	return bullet->ent;
}


void bullet_update(Entity *self)
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

void bullet_think(Entity *self)
{
	if (!self) return;
	//need a fail safe to delete bullets
}

Entity *get_bullet_entity()
{
	return bullet->ent;
}

Bullet *get_bullet()
{
	return bullet;
}

void bullet_travel(Entity *self)
{
	if (!self) return;
	int mx = self->destinationx, my = self->destinationy;
	Vector2D aimdir, camera, thrust;
	mx += camera.x;
	my += camera.y;
	aimdir.x = mx - (self->position.x);
	aimdir.y = my - (self->position.y);
	vector2d_normalize(&aimdir);
	vector2d_scale(thrust, aimdir, 2);
	vector2d_add(self->velocity, self->velocity, thrust);
}