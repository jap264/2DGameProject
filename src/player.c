#include "simple_logger.h"

#include "entity.h"
#include "player.h"

void player_update(Entity *self);

static Player *player = { 0 };

Entity *player_spawn()
{
	player = (Player *)gfc_allocate_array(sizeof(Player), 1);
	Entity *ent = entity_new();
	if (!ent)
	{
		slog("failed to create entity for the player");
		return NULL;
	}
	player->ent = ent;
	player->ent->ent_type = 0;
	player->ent->position = vector2d(0, 0);
	player->ent->sprite = gf2d_sprite_load_image("images/player.png");
	//vector2d_copy(player->ent->position, position);
	/*player->ent->frameRate = 0.1;
	ent->frameCount = 16;
	player->ent->update = player_update;
	player->ent->rotation.x = 64;
	player->ent->rotation.y = 64;*/
	return ent;
}


void player_update(Entity *self)
{
	Vector2D aimdir;
	float angle;
	int mx, my;
	if (!self)return;
	SDL_GetMouseState(&mx, &my);
	aimdir.x = mx - (self->position.x + 64);
	aimdir.y = my - (self->position.y + 64);
	angle = vector_angle(aimdir.x, aimdir.y);
	self->rotation.z = angle + 90;
}

Entity *get_player_entity()
{
	return player->ent;
}

Player *get_player()
{
	return player;
}

int *get_player_health()
{
	return player->health;
}