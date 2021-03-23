#include "simple_logger.h"

#include "boss_projectile.h"
#include "camera.h"
#include "entity.h"

void boss_projectile_update(Entity *self);
void boss_projectile_think(Entity *self);
void boss_projectile_collide(Entity *self);

void cannonball_update(Entity *self);
void cannonball_think(Entity *self);
void cannonball_collide(Entity *self, Entity *other);

void minion_update(Entity *self);
void minion_think(Entity *self);
void minion_collide(Entity *self, Entity *other);

static int frozenDelay = 0;
static Boss_Projectile *boss_projectile = { 0 };

Entity *boss_projectile_spawn(Vector2D position)
{
	boss_projectile = (Boss_Projectile *)gfc_allocate_array(sizeof(Boss_Projectile), 1);
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the boss_projectile");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/boss_projectile.png");
	vector2d_copy(ent->position, position);
	ent->rotation.x = 80;
	ent->rotation.y = 80;
	ent->update = boss_projectile_update;
	ent->think = boss_projectile_think;
	ent->collide = boss_projectile_collide;
	ent->health = 200;
	ent->ent_type = 8;
	boss_projectile->ent = ent;
	boss_projectile->frozen = false;
	boss_projectile->lives = 3;
	boss_projectile->alive = true;

	return ent;
}

Entity *minion_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the minion");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/minion.png");

	Vector2D pos;
	pos.x = position.x + 64;
	pos.y = position.y + 64;

	vector2d_copy(ent->position, pos);
	ent->rotation.x = 16;
	ent->rotation.y = 16;
	ent->update = minion_update;
	ent->think = minion_think;
	ent->collide = minion_collide;
	ent->ent_type = 9;

	return ent;
}

Entity *cannonball_spawn(Vector2D position)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the cannonball");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/cannonball.png");

	Vector2D pos;
	pos.x = position.x + 16;
	pos.y = position.y + 16;

	vector2d_copy(ent->position, pos);
	ent->rotation.x = 64;
	ent->rotation.y = 64;
	ent->update = cannonball_update;
	ent->think = cannonball_think;
	ent->collide = cannonball_collide;
	ent->ent_type = 3;

	Vector2D aimdir, thrust;
	float angle;
	int mx, my;

	mx = get_player_entity()->position.x + 80;
	my = get_player_entity()->position.y + 80;

	aimdir.x = mx - (ent->position.x + 64);
	aimdir.y = my - (ent->position.y + 64);

	// turn aimdir into a unit vector
	vector2d_normalize(&aimdir);
	// check for motion

	vector2d_scale(thrust, aimdir, 1.6);
	vector2d_add(ent->velocity, ent->velocity, thrust);

	return ent;
}

void boss_projectile_collide(Entity *self, Entity *other)
{
	if (!self || !other) return;

	if (other->ent_type == 1 && !boss_projectile->frozen)
	{
		self->health -= other->dmg;
		entity_free(other);
	}

	if (other->ent_type == 10)
	{
		boss_projectile->lives--;
		entity_free(other);
	}
}

void minion_collide(Entity *self, Entity *other)
{
	if (!self || !other) return;

	if (other->ent_type == 9) entity_free(self);
}

void cannonball_collide(Entity *self, Entity *other)
{
	if (!self || !other) return;

	if (other->weapon == 3)
	{
		Vector2D aimdir, thrust;
		float angle;
		int mx, my;

		mx = boss_projectile->ent->position.x + 80;
		my = boss_projectile->ent->position.y + 80;

		aimdir.x = mx - (self->position.x + 64);
		aimdir.y = my - (self->position.y + 64);

		// turn aimdir into a unit vector
		vector2d_normalize(&aimdir);
		// check for motion

		vector2d_scale(thrust, aimdir, 1.6);
		vector2d_add(self->velocity, self->velocity, thrust);

		self->ent_type = 10;
	}

	if (other->ent_type == 0) player_die();
}

void boss_projectile_update(Entity *self)
{
	if (!self)return;
	self->circle = shape_circle(self->position.x + 80, self->position.y + 80, 80);

	if (self->health <= 0)
	{
		boss_projectile->frozen = true;
		frozenDelay = 500;
		self->health = 200;
	}

	if (frozenDelay == 250) cannonball_spawn(self->position);
	if (frozenDelay > 0) frozenDelay--;
	if (frozenDelay <= 0) boss_projectile->frozen = false;

	if (boss_projectile->lives <= 0)
	{
		entity_free(self);
		boss_projectile->alive = false;
	}
	
	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void minion_update(Entity *self)
{
	if (!self) return;
	self->circle = shape_circle(self->position.x + 16, self->position.y + 16, 8);

	if (!boss_projectile->alive) entity_free(self);

	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void cannonball_update(Entity *self)
{
	if (!self) return;
	self->circle = shape_circle(self->position.x + 64, self->position.y + 64, 32);
}

void boss_projectile_think(Entity *self)
{
	const Uint8 *keys;
	Vector2D aimdir, thrust;
	float angle;
	int mx, my;
	if (!self)return;
	
	mx = get_player_entity()->position.x + 64;
	my = get_player_entity()->position.y + 64;

	aimdir.x = mx - (self->position.x + 80);
	aimdir.y = my - (self->position.y + 80);
	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;
	// turn aimdir into a unit vector
	vector2d_normalize(&aimdir);
	// check for motion

	vector2d_scale(thrust, aimdir, 1);
	if (!boss_projectile->frozen) vector2d_add(self->velocity, self->velocity, thrust);
	else vector2d_clear(self->velocity);

	if (boss_projectile->lives == 2) self->sprite = gf2d_sprite_load_image("images/boss_projectile_mad.png");
	if (boss_projectile->lives == 1) self->sprite = gf2d_sprite_load_image("images/boss_projectile_angry.png");
	if (SDL_GetTicks() % 100 == 0 && !boss_projectile->frozen) minion_spawn(self->position);

}

void minion_think(Entity *self)
{
	const Uint8 *keys;
	Vector2D aimdir, thrust;
	float angle;
	int mx, my;
	if (!self)return;

	mx = get_player_entity()->position.x + 64;
	my = get_player_entity()->position.y + 64;

	aimdir.x = mx - (self->position.x + 16);
	aimdir.y = my - (self->position.y + 16);
	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;
	// turn aimdir into a unit vector
	vector2d_normalize(&aimdir);
	// check for motion

	vector2d_scale(thrust, aimdir, 1.8);
	vector2d_add(self->velocity, self->velocity, thrust);
}

void cannonball_think(Entity *self)
{
	const Uint8 *keys;
	Vector2D aimdir, thrust;
	float angle;
	int mx, my;
	if (!self)return;

	//mx = get_player_entity()->position.x + 64;
	//my = get_player_entity()->position.y + 64;

	//aimdir.x = mx - (self->position.x + 80);
	//aimdir.y = my - (self->position.y + 80);
	//angle = vector_angle(aimdir.x, aimdir.y);
	//self->rotation.z = angle + 90;
	//// turn aimdir into a unit vector
	//vector2d_normalize(&aimdir);
	//// check for motion

	//vector2d_scale(thrust, aimdir, 1);
	//if (!boss_projectile->frozen) vector2d_add(self->velocity, self->velocity, thrust);
	//else vector2d_clear(self->velocity);

}