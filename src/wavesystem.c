#include "simple_logger.h"

#include "wavesystem.h"
#include "player.h"
#include "e_armored.h"
#include "e_freeze.h"
#include "e_shifty.h"
#include "e_shooter.h"
#include "e_walker.h"
#include "boss_melee.h"
#include "boss_projectile.h"

static int randNum();

static WaveSystem *wavesystem = { 0 };

void wavesystem_init()
{
	wavesystem = (WaveSystem *)gfc_allocate_array(sizeof(WaveSystem), 1);
	wavesystem->waveCount = 1;
	wavesystem->spawnCount = 10;
	return;
}

void enemy_spawn()
{
	Vector2D topleft = vector2d(0, 0),
			topright = vector2d(1200,0),
			bottomleft = vector2d(0,720),
			bottomright = vector2d(1200,720);

	Vector2D position;

	int num = randNum();
	if (num <= 2) position = topleft;
	else if (num <= 4) position = topright;
	else if (num <= 6) position = bottomleft;
	else position = bottomright;

	num = randNum();
	if (num <= 3) walker_spawn(position);
	else if (num <= 6) armored_spawn(position);
	else if (num == 7) shooter_spawn(position);
	else if (num == 8) shifty_spawn(position);
	else freeze_spawn(position);

}

WaveSystem *get_wavesystem()
{
	return wavesystem;
}

int *get_wave_count()
{
	return wavesystem->waveCount;
}

int *get_spawn_count()
{
	return wavesystem->spawnCount;
}

static int integer(float f)
{
	int result = f;
	return result;
}

static int randNum()
{
	return integer(gfc_crandom() * 5 + 5); //random number from 0-9
}


/*eol@eof*/
