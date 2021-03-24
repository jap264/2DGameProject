#include "simple_logger.h"

#include "boss_melee.h"
#include "camera.h"
#include "entity.h"

void boss_melee_update(Entity *self);
void boss_melee_think(Entity *self);
void boss_melee_collide(Entity *self, Entity *other);

static int frozenDelay = 0;
static int sheathedDelay = 0;
static Boss_Melee *boss_melee = { 0 };

Entity *boss_melee_spawn(Vector2D position)
{
	boss_melee = (Boss_Melee *)gfc_allocate_array(sizeof(Boss_Melee), 1);
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the boss_melee");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_all("images/boss_unsheathed.png", 160, 160, 2);
	vector2d_copy(ent->position, position);
	ent->frameRate = 0.1;
	ent->frameCount = 2;
	ent->rotation.x = 80;
	ent->rotation.y = 80;
	ent->update = boss_melee_update;
	ent->think = boss_melee_think;
	ent->collide = boss_melee_collide;
	ent->health = 200;
	ent->ent_type = 7;
	boss_melee->ent = ent;
	boss_melee->frozen = false;
	boss_melee->sheathed = false;

	return ent;
}

void boss_melee_collide(Entity *self, Entity *other)
{
	if (!self || !other) return;

	if (other->weapon == 4 && boss_melee->frozen)
	{
		boss_melee->sheathed = true;
		sheathedDelay = frozenDelay;
		slog("unsheathing");
	}

	if (other->ent_type == 1)
	{
		if (other->weapon == 0 && boss_melee->sheathed && other->dmg != NULL)
		{
			self->health -= other->dmg;
			entity_free(other);
			slog("ent type: %i", other->ent_type);
		}

		if (other->weapon == 4) entity_free(other);
	}

	if (other->ent_type == 6 && other->weapon == 3)
	{
		boss_melee->frozen = true;
		frozenDelay = 1000;
	}

}

void boss_melee_update(Entity *self)
{
	if (!self)return;

	int radius;
	if (boss_melee->sheathed) radius = 40;
	else radius = 80;

	self->circle = shape_circle(self->position.x + 80, self->position.y + 80, radius);

	if (boss_melee->sheathed)
	{
		if (self->health > 150) self->sprite = gf2d_sprite_load_image("images/boss_sheathed.png"); 
		if (self->health <= 150 && self->health > 100) self->sprite = gf2d_sprite_load_image("images/boss_sheathed_75.png");
		if (self->health <= 100 && self->health > 50) self->sprite = gf2d_sprite_load_image("images/boss_sheathed_50.png");
		if (self->health <= 50) self->sprite = gf2d_sprite_load_image("images/boss_sheathed_25.png");
	}
	else self->sprite = gf2d_sprite_load_all("images/boss_unsheathed.png", 160, 160, 2);

	if (frozenDelay > 0) frozenDelay--;
	if (frozenDelay <= 0) boss_melee->frozen = false;

	if (sheathedDelay > 0) sheathedDelay--;
	if (sheathedDelay <= 0) boss_melee->sheathed = false;

	if (self->health <= 0)
	{
		get_player()->bossesKilled++;
		get_player()->enemiesKilled++;
		entity_free(self);
	}

	vector2d_scale(self->velocity, self->velocity, 0.75);
	if (vector2d_magnitude_squared(self->velocity) < 2)
	{
		vector2d_clear(self->velocity);
	}
}

void boss_melee_think(Entity *self)
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

	vector2d_scale(thrust, aimdir, 1.8);
	if (!boss_melee->frozen) vector2d_add(self->velocity, self->velocity, thrust);
	else vector2d_clear(self->velocity);
}