#ifndef __WAVE_SYSTEM_H__
#define __WAVE_SYSTEM_H__

typedef struct
{
	int		waveCount;	//current wave number
	int		spawnCount; //number of enemies to spawn per round
}WaveSystem;

/*
* @brief initializes the wavesystem
*/
void wavesystem_init();

/*
 * @brief spawns one random enemy in a random location
 */
void enemy_spawn();

/*
* @brief gives wavesystem
*/
WaveSystem *get_wavesystem();

/*
* @brief gives waveCount
*/
int *get_wave_count();

/*
* @brief gives spawnCount
*/
int *get_spawn_count();

#endif