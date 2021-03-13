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
	return bullet->ent;
}


void bullet_update(Entity *self)
{

}

void bullet_think(Entity *self)
{
	if (!self) return;

	travel(self, self->destinationx, self->destinationy, 1);

	if (&self->position.x == self->destinationx && &self->position.y == self->destinationy)
	{
		entity_free(self);
	}
}

Entity *get_bullet_entity()
{
	return bullet->ent;
}

Bullet *get_bullet()
{
	return bullet;
}