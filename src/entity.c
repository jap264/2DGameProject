#include <stdlib.h>
#include "simple_logger.h"

#include "camera.h"
#include "entity.h"
#include "shape.h"

typedef struct
{
	Entity *entity_list;
	Uint32  max_entities;
	int		entity_count;
}EntityManager;

static EntityManager entity_manager = { 0 };

void entity_manager_init(Uint32 max_entities)
{
	if (max_entities == 0)
	{
		slog("cannot allocate 0 entities!");
		return;
	}
	if (entity_manager.entity_list != NULL)
	{
		entity_manager_free();
	}
	entity_manager.entity_list = (Entity *)gfc_allocate_array(sizeof (Entity), max_entities);
	if (entity_manager.entity_list == NULL)
	{
		slog("failed to allocate entity list!");
		return;
	}
	entity_manager.max_entities = max_entities;
	atexit(entity_manager_free);
	slog("entity system initialized");
}

void entity_manager_free()
{
	if (entity_manager.entity_list != NULL)
	{
		free(entity_manager.entity_list);
	}
	memset(&entity_manager, 0, sizeof(EntityManager));
	slog("entity system closed");
}

void entity_update(Entity *self)
{
	if (!self)return;
	// DO ANY GENERIC UPDATE CODE
	vector2d_add(self->position, self->position, self->velocity);
	self->frame += self->frameRate;
	if (self->frame >= self->frameCount)self->frame = 0;
	// IF THERE IS A CUSTOM UPDATE, DO THAT NOW
	if (self->update)self->update(self);
}

void entity_manager_update_entities()
{
	int i;
	if (entity_manager.entity_list == NULL)
	{
		slog("entity system does not exist");
		return;
	}
	for (i = 0; i < entity_manager.max_entities; i++)
	{
		if (entity_manager.entity_list[i]._inuse == 0)continue;
		entity_update(&entity_manager.entity_list[i]);
	}
}

void entity_manager_think_entities()
{
	int i;
	if (entity_manager.entity_list == NULL)
	{
		slog("entity system does not exist");
		return;
	}
	for (i = 0; i < entity_manager.max_entities; i++)
	{
		if (entity_manager.entity_list[i]._inuse == 0)continue;
		if (entity_manager.entity_list[i].think != NULL)
		{
			entity_manager.entity_list[i].think(&entity_manager.entity_list[i]);
		}

		if (entity_manager.entity_list[i].ttv == NULL)continue;
		if (entity_manager.entity_list[i].ttv > 0) entity_manager.entity_list[i].ttv--;
		if (entity_manager.entity_list[i].ttv == 0) entity_free(&entity_manager.entity_list[i]);
	}
}

void entity_manager_draw_entities()
{
	int i;
	if (entity_manager.entity_list == NULL)
	{
		slog("entity system does not exist");
		return;
	}
	for (i = 0; i < entity_manager.max_entities; i++)
	{
		if (entity_manager.entity_list[i]._inuse == 0)continue;
		entity_draw(&entity_manager.entity_list[i]);
	}
}

void entity_manager_free_entities()
{
	int i;
	if (entity_manager.entity_list == NULL)
	{
		slog("entity system does not exist");
		return;
	}
	for (i = 0; i < entity_manager.max_entities; i++)
	{
		if (entity_manager.entity_list[i]._inuse == 0)continue;
		entity_free(&entity_manager.entity_list[i]);
	}
}

Entity *entity_new()
{
	int i;
	if (entity_manager.entity_list == NULL)
	{
		slog("entity system does not exist");
		return NULL;
	}
	for (i = 0; i < entity_manager.max_entities; i++)
	{
		if (entity_manager.entity_list[i]._inuse)continue;// someone else is using this one
		memset(&entity_manager.entity_list[i], 0, sizeof(Entity));
		entity_manager.entity_list[i]._inuse = 1;
		entity_manager.entity_count++;
		return &entity_manager.entity_list[i];
	}
	slog("no free entities available");
	return NULL;
}

void entity_free(Entity *ent)
{
	if (!ent)
	{
		slog("cannot free a NULL entity");
		return;
	}
	gf2d_sprite_free(ent->sprite);
	ent->sprite = NULL;
	ent->_inuse = 0;
	entity_manager.entity_count--;
}

void entity_draw(Entity *ent)
{
	Vector2D drawPosition, offset;
	if (!ent)
	{
		slog("cannot draww a NULL entity");
		return;
	}
	if (ent->draw)
	{
		ent->draw(ent);
	}
	else
	{
		if (ent->sprite == NULL)
		{
			return;// nothing to draw
		}
		offset = camera_get_offset();
		drawPosition.x = ent->position.x;
		drawPosition.y = ent->position.y;
		if (!camera_rect_on_screen(gfc_sdl_rect(ent->position.x, ent->position.y, ent->sprite->frame_w, ent->sprite->frame_h)))
		{
			//ent not on screen, skip
			return;
		}
		drawPosition.x += offset.x;
		drawPosition.y += offset.y;
		gf2d_sprite_draw(
			ent->sprite,
			ent->position,
			NULL,
			NULL,
			&ent->rotation,
			NULL,
			NULL,
			(Uint32)ent->frame);
	}
}

void follow(Entity *self, Entity *other, float speed)
{
	if (!self || !other) return;

	if (self->position.y > other->position.y)
	{
		self->position.y -= speed;
		//slog("following -y");
	}

	if (self->position.y < other->position.y)
	{
		self->position.y += speed;
		//slog("following +y");
	}
	if (self->position.x > other->position.x)
	{
		self->position.x -= speed;
		//slog("following -x");
	}

	if (self->position.x < other->position.x)
	{
		self->position.x += speed;
		//slog("following +x");
	}

}

void check_all_collisions()
{
	//if (SDL_GetTicks() % 100 == 0) slog("checking collisions");

	for (int i = 0; i < entity_manager.max_entities; i++)
	{
		if (!entity_manager.entity_list[i]._inuse) continue;

		//if (SDL_GetTicks() % 100 == 0) slog("ent type: %i", entity_manager.entity_list[i].ent_type);

		for (int x = 0; x < entity_manager.max_entities; x++)
		{
			if (!entity_manager.entity_list[x]._inuse) continue;
			if (&entity_manager.entity_list[x] == &entity_manager.entity_list[i]) continue;
			if (!&entity_manager.entity_list[x] || !&entity_manager.entity_list[i])
			{
				slog("null entities");
				continue;
			}

			if (shape_circle_collision(entity_manager.entity_list[x].circle, entity_manager.entity_list[i].circle) == true)
			{
				if (entity_manager.entity_list[x].collide != NULL)
					entity_manager.entity_list[x].collide(&entity_manager.entity_list[x] , & entity_manager.entity_list[i]);

				if (entity_manager.entity_list[i].collide != NULL)
					entity_manager.entity_list[i].collide(&entity_manager.entity_list[i], &entity_manager.entity_list[x]);
			}
		}
	}
}

int get_entity_count()
{
	return entity_manager.entity_count;
}
/*eol@eof*/