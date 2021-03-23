#include "simple_logger.h"

#include "e_shifty.h"
#include "camera.h"
#include "entity.h"

void shifty_update(Entity *self);
void shifty_think(Entity *self);
void shifty_collide(Entity *self);
static Shifty *shifty = { 0 };
static int randNum();

Entity *shifty_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the shifty");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/e_shifty.png");
	vector2d_copy(ent->position, position);
	ent->update = shifty_update;
	ent->think = shifty_think;
	ent->collide = shifty_collide;
	ent->rotation.x = 32;
	ent->rotation.y = 32;
	ent->health = 5;
	ent->ent_type = 2;
	return ent;
}

void shifty_collide(Entity *self, Entity *other)
{
	if (!self || !other) return;

	if (other->ent_type == 1)
	{
		if (other->dmg != NULL) self->health -= other->dmg;
		entity_free(other);
	}

	if (self->health <= 0 || other->ent_type == 6) entity_free(self);
}

void shifty_update(Entity *self)
{
	if (!self)return;

	self->circle = shape_circle(self->position.x + 32, self->position.y + 32, 16);

	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void shifty_think(Entity *self)
{
	const Uint8 *keys;
	Vector2D aimdir, aimdir2, aimdir3, thrust;
	float angle;
	int mx, my;
	if (!self)return;
	
	mx = get_player_entity()->position.x + 64;
	my = get_player_entity()->position.y + 64;

	aimdir.x = mx - (self->position.x + 32);
	aimdir.y = my - (self->position.y + 32);

	aimdir2.x = mx - (self->position.x + 100);
	aimdir2.y = my - (self->position.y - 100);

	aimdir3.x = mx - (self->position.x - 100);
	aimdir3.y = my - (self->position.y + 100);

	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;


	// turn aimdir into a unit vector
	vector2d_normalize(&aimdir);
	vector2d_normalize(&aimdir2);
	vector2d_normalize(&aimdir3);

	// check for motion
	vector2d_scale(thrust, aimdir, 1.6);
	vector2d_add(self->velocity, self->velocity, thrust);


	if (SDL_GetTicks() % 100 == 0)
	{
		int num = randNum();

		if (num <= 2) self->position.x += 100;
		else if (num > 2 && num <= 5) self->position.x -= 100;
		else if (num > 5 && num <= 8) self->position.y -= 100;
		else self->position.y += 100;
	}

}

static int integer(float f)
{
	int result = f;
	return result;
}

static int randNum()
{
	return integer(gfc_crandom() * 5 + 5);
}