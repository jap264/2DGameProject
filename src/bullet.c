#include "simple_logger.h"

#include "player.h"
#include "camera.h"
#include "entity.h"
#include "bullet.h"

void bullet_update(Entity *self);
void bullet_collide(Entity *self);
void thunderwave_update(Entity *self);
void bullet_travel(Entity *self);
void shotgun_spread(Entity *bullet1, Entity *bullet2, Entity *bullet3);

Entity *pistol_round_spawn(int destinationx, int destinationy)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the bullet");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/pistol_round.png");
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x + 50;
	spawn.y = get_player_entity()->position.y + 50;
	vector2d_copy(ent->position, spawn);
	ent->destinationx = destinationx;
	ent->destinationy = destinationy;
	ent->update = bullet_update;
	ent->collide = bullet_collide;
	if (get_player()->p_instakill) ent->dmg = 20;
	else ent->dmg = 3;
	ent->ttv = 400;
	ent->speed = 2;
	ent->ent_type = 1;
	ent->weapon = 0;
	bullet_travel(ent);
	return ent;
}

Entity *light_round_spawn(int destinationx, int destinationy)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the bullet");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/light_round.png");
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x + 50;
	spawn.y = get_player_entity()->position.y + 50;
	vector2d_copy(ent->position, spawn);
	ent->destinationx = destinationx;
	ent->destinationy = destinationy;
	ent->update = bullet_update;
	ent->collide = bullet_collide;
	ent->ttv = 400;
	ent->speed = 4;
	ent->ent_type = 1;
	ent->weapon = 0;
	if (get_player()->p_instakill) ent->dmg = 20;
	else ent->dmg = 2;
	bullet_travel(ent);
	return ent;
}

Entity *heavy_round_spawn(int destinationx, int destinationy)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the bullet");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/heavy_round.png");
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x + 50;
	spawn.y = get_player_entity()->position.y + 50;
	vector2d_copy(ent->position, spawn);
	ent->destinationx = destinationx;
	ent->destinationy = destinationy;
	ent->update = bullet_update;
	ent->collide = bullet_collide;
	ent->ttv = 200;
	ent->speed = 6;
	ent->ent_type = 1;
	ent->weapon = 0;
	if (get_player()->p_instakill) ent->dmg = 20;
	else ent->dmg = 1;
	bullet_travel(ent);
	return ent;
}

Entity *sniper_round_spawn(int destinationx, int destinationy)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the bullet");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/sniper_round.png");
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x + 50;
	spawn.y = get_player_entity()->position.y + 50;
	vector2d_copy(ent->position, spawn);
	ent->destinationx = destinationx;
	ent->destinationy = destinationy;
	ent->update = bullet_update;
	ent->collide = bullet_collide;
	ent->ttv = 400;
	ent->speed = 10;
	ent->ent_type = 1;
	ent->weapon = 0;
	if (get_player()->p_instakill) ent->dmg = 20;
	else ent->dmg = 10;
	bullet_travel(ent);
	return ent;
}

void *shotgun_shells_spawn(int destinationx, int destinationy)
{
	Entity *ent = entity_new(), *ent2 = entity_new(), *ent3 = entity_new();
	if (!ent || !ent2 || !ent3)
	{
		slog("failed to create entity for the bullet");
		return NULL;
	}

	ent->sprite = gf2d_sprite_load_image("images/shell.png");
	ent2->sprite = gf2d_sprite_load_image("images/shell.png");
	ent3->sprite = gf2d_sprite_load_image("images/shell.png");

	Vector2D spawn;
	spawn.x = get_player_entity()->position.x + 50;
	spawn.y = get_player_entity()->position.y + 45;
	vector2d_copy(ent->position, spawn);

	spawn.x = get_player_entity()->position.x + 55;
	spawn.y = get_player_entity()->position.y + 50;
	vector2d_copy(ent2->position, spawn);

	spawn.x = get_player_entity()->position.x + 45;
	spawn.y = get_player_entity()->position.y + 50;
	vector2d_copy(ent3->position, spawn);

	ent->destinationx = destinationx;
	ent->destinationy = destinationy;
	
	ent->update = bullet_update;
	ent2->update = bullet_update;
	ent3->update = bullet_update;
	
	ent->collide = bullet_collide;
	ent2->collide = bullet_collide;
	ent3->collide = bullet_collide;

	ent->ttv = 200;
	ent2->ttv = 200;
	ent3->ttv = 200;

	ent->speed = 6;
	ent2->speed = 6;
	ent3->speed = 6;

	ent->ent_type = 1;
	ent2->ent_type = 1;
	ent3->ent_type = 1;

	ent->weapon = 0;
	ent2->weapon = 0;
	ent3->weapon = 0;

	if (get_player()->p_instakill)
	{
		ent->dmg = 20;
		ent2->dmg = 20;
		ent3->dmg = 20;
	}
	else
	{
		ent->dmg = 2;
		ent2->dmg = 2;
		ent3->dmg = 2;
	}


	shotgun_spread(ent, ent2, ent3);
}

Entity *thunderwave_spawn(int destinationx, int destinationy)
{
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the bullet");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/thunderwave.png");
	Vector2D spawn;
	spawn.x = get_player_entity()->position.x;
	spawn.y = get_player_entity()->position.y;
	vector2d_copy(ent->position, spawn);
	ent->destinationx = destinationx;
	ent->destinationy = destinationy;
	ent->update = thunderwave_update;
	ent->collide = bullet_collide;
	ent->ttv = 400;
	ent->speed = 8;
	ent->ent_type = 6;
	ent->weapon = 2;
	thunderwave_travel(ent);
	return ent;
}

void thunderwave_update(Entity *self)
{
	if (!self) return;
	self->circle = shape_circle(self->position.x + 64, self->position.y + 64, 32);
}

void bullet_update(Entity *self)
{
	if (!self) return;
	self->circle = shape_circle(self->position.x + 16, self->position.y + 16, 8);
}

void bullet_collide(Entity *self, Entity *other)
{
	if (!self) return;
	if (other->ent_type == 7 || other->ent_type == 8)
	{

	}
}

void bullet_travel(Entity *self)
{
	if (!self) return;
	int mx = self->destinationx, my = self->destinationy;
	Vector2D aimdir, camera, thrust;
	/*mx += camera.x;
	my += camera.y;*/
	aimdir.x = mx - (self->position.x);
	aimdir.y = my - (self->position.y);
	vector2d_normalize(&aimdir);
	vector2d_scale(thrust, aimdir, self->speed);
	vector2d_add(self->velocity, self->velocity, thrust);
}

void shotgun_spread(Entity *bullet1, Entity *bullet2, Entity *bullet3)
{
	if (!bullet1 || !bullet2 || !bullet3) return;
	int mx = bullet1->destinationx, my = bullet1->destinationy;
	Vector2D aimdir, aimdir2, aimdir3, camera, thrust;
	/*mx += camera.x;
	my += camera.y;*/

	aimdir.x = mx - (bullet1->position.x + 60);
	aimdir.y = my - (bullet1->position.y + 60);

	aimdir2.x = mx - (bullet2->position.x);
	aimdir2.y = my - (bullet2->position.y);

	aimdir3.x = mx - (bullet3->position.x - 100);
	aimdir3.y = my - (bullet3->position.y - 100);

	vector2d_normalize(&aimdir);
	vector2d_normalize(&aimdir2);
	vector2d_normalize(&aimdir3);

	vector2d_scale(thrust, aimdir, bullet1->speed);
	vector2d_add(bullet1->velocity, bullet1->velocity, thrust);

	vector2d_scale(thrust, aimdir2, bullet2->speed);
	vector2d_add(bullet2->velocity, bullet2->velocity, thrust);

	vector2d_scale(thrust, aimdir3, bullet3->speed);
	vector2d_add(bullet3->velocity, bullet3->velocity, thrust);
}

void thunderwave_travel(Entity *self)
{
	if (!self) return;
	int mx = self->destinationx, my = self->destinationy;
	Vector2D aimdir, camera, thrust;
	mx += camera.x;
	my += camera.y;
	aimdir.x = mx - (self->position.x +50);
	aimdir.y = my - (self->position.y +50);
	vector2d_normalize(&aimdir);
	vector2d_scale(thrust, aimdir, self->speed);
	vector2d_add(self->velocity, self->velocity, thrust);
}