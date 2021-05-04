#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#include "gfc_audio.h"

typedef struct
{
	Sound *_game;
	Sound *_playerhit;
	Sound *_playerdeath;
	Sound *_enemydeath;
	Sound *_bulletshot;
	Sound *_doground;
}Sounds;
/*
 * @brief allocates memory for the sounds
 */
void sounds_init();

/*
* @brief plays player hit sound
*/
void sounds_play_gamesound();

/*
* @brief plays player hit sound
*/
void sounds_play_playerhit();

void sounds_play_playerdeath();

/*
* @brief plays enemy death sound
*/
void sounds_play_enemydeath();

/*
* @brief plays bullet shot sound
*/
void sounds_play_bulletshot();

/*
* @brief plays dog round sount
*/
void sounds_play_doground();
#endif