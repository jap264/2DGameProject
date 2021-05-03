#include <SDL.h>

#include "math.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"

#include "player.h"
#include "shape.h"
#include "camera.h"
#include "entity.h"
#include "level.h"
#include "rocket.h"
#include "e_walker.h"
#include "e_shooter.h"
#include "e_shifty.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *background;
    
    int mx,my;
    float mf = 0;
    Sprite *mouse, *health, *weapon, *p_speed, *p_firerate, *p_invinc, *p_instakill, *frozen, *multiplier, *combobar;
    Vector4D mouseColor = {255,100,255,200};

	Entity *playerEnt = NULL;
	Player *player;

	Level *level;
    
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
	camera_set_dimensions(vector2d(1200, 720));
	camera_set_position(vector2d(0, 0));
    gf2d_sprite_init(1024);
	entity_manager_init(1024);

    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    background = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
	level = level_load("levels/exampleLevel.json");
    mouse = gf2d_sprite_load_image("images/crosshair.png");
	weapon = gf2d_sprite_load_image("images/pistol.png");

	//Player Spawn
	player_spawn(vector2d(500, 250));
	player = get_player();
	playerEnt = get_player_entity();

	//Weapon Init
	rocket_init();

	//Powerup UI Init
	p_speed = gf2d_sprite_load_image("images/p_speedUI.png");
	p_firerate = gf2d_sprite_load_image("images/p_firerateUI.png");
	p_invinc = gf2d_sprite_load_image("images/p_invincUI.png");
	p_instakill = gf2d_sprite_load_image("images/p_instakillUI.png");
	frozen = gf2d_sprite_load_image("images/frozen.png");

	slog("main game loop begin");
    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        /*mf+=0.1;
        if (mf >= 16.0)mf = 0;*/
        
		entity_manager_think_entities();
		entity_manager_update_entities();
		check_all_collisions();

		level_update(level);
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first

			
            gf2d_sprite_draw_image(background,vector2d(0,0));

			level_draw(level);
			//gf2d_sprite_draw_image(player->ent->sprite, vector2d(0, 0));

			entity_manager_draw_entities();
            
			//UI elements last
				//Weapon UI
			if (keys[SDL_SCANCODE_1])
			{
				weapon = gf2d_sprite_load_image("images/pistol.png");
				player->currWeapon = 1;
			}

			else if (keys[SDL_SCANCODE_2])
			{
				weapon = gf2d_sprite_load_image("images/submachine_gun.png");
				player->currWeapon = 2;
			}

			else if (keys[SDL_SCANCODE_3])
			{
				weapon = gf2d_sprite_load_image("images/shotgun.png");
				player->currWeapon = 3;
			}

			else if (keys[SDL_SCANCODE_4])
			{
				weapon = gf2d_sprite_load_image("images/lmg.png");
				player->currWeapon = 4;
			}

			else if (keys[SDL_SCANCODE_5])
			{
				weapon = gf2d_sprite_load_image("images/sniper.png");
				player->currWeapon = 5;
			}

			else if (keys[SDL_SCANCODE_6])
			{
				weapon = gf2d_sprite_load_image("images/rocket_launcher.png");
				player->currWeapon = 6;
			}

			else if (keys[SDL_SCANCODE_7])
			{
				weapon = gf2d_sprite_load_image("images/thunder_gun.png");
				player->currWeapon = 7;
			}

			else if (keys[SDL_SCANCODE_Q])
			{
				weapon = gf2d_sprite_load_image("images/grenadeUI.png");
				player->currWeapon = 8;
			}

			else if (keys[SDL_SCANCODE_E])
			{
				weapon = gf2d_sprite_load_image("images/mineUI.png");
				player->currWeapon = 9;
			}

			else if (keys[SDL_SCANCODE_F])
			{
				weapon = gf2d_sprite_load_image("images/hammer.png");
				player->currWeapon = 10;
			}

			if (keys[SDL_SCANCODE_Y] && SDL_GetTicks() % 50 == 0)
			{
				walker_spawn(vector2d(700,250));
			}
			if (keys[SDL_SCANCODE_U] && SDL_GetTicks() % 50 == 0)
			{
				shooter_spawn(vector2d(700, 250));
			}
			if (keys[SDL_SCANCODE_O] && SDL_GetTicks() % 50 == 0)
			{
				shifty_spawn(vector2d(700, 250));
			}
			if (keys[SDL_SCANCODE_I] && SDL_GetTicks() % 50 == 0)
			{
				armored_spawn(vector2d(700, 250));
			}

			if (keys[SDL_SCANCODE_P] && SDL_GetTicks() % 50 == 0)
			{
				freeze_spawn(vector2d(700, 250));
			}

			if (keys[SDL_SCANCODE_LEFTBRACKET] && SDL_GetTicks() % 50 == 0)
			{
				boss_melee_spawn(vector2d(700, 250));
			}

			if (keys[SDL_SCANCODE_RIGHTBRACKET] && SDL_GetTicks() % 50 == 0)
			{
				boss_projectile_spawn(vector2d(700, 250));
			}

			if (keys[SDL_SCANCODE_G] && SDL_GetTicks() % 50 == 0)
			{
				p_health_spawn(vector2d(700, 250));
			}

			if (keys[SDL_SCANCODE_H] && SDL_GetTicks() % 50 == 0)
			{
				p_speed_spawn(vector2d(700, 250));
			}

			if (keys[SDL_SCANCODE_J] && SDL_GetTicks() % 50 == 0)
			{
				p_firerate_spawn(vector2d(700, 250));
			}

			if (keys[SDL_SCANCODE_K] && SDL_GetTicks() % 50 == 0)
			{
				p_invinc_spawn(vector2d(700, 250));
			}

			if (keys[SDL_SCANCODE_L] && SDL_GetTicks() % 50 == 0)
			{
				p_instakill_spawn(vector2d(700, 250));
			}

			if (keys[SDL_SCANCODE_RETURN] && SDL_GetTicks() % 50 == 0 && player->alive == false)
			{
				player_respawn(vector2d(500, 250));
			}

			gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf
			);

			//Health UI
			if (get_player_health() == 3) health = gf2d_sprite_load_image("images/full_health.png");
			else if (get_player_health() == 2) health = gf2d_sprite_load_image("images/half_health.png");
			else if (get_player_health() == 1) health = gf2d_sprite_load_image("images/low_health.png");
			else health = gf2d_sprite_load_image("images/no_health.png");

			gf2d_sprite_draw(
				health,
				vector2d(10, 615),
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				(int)mf
			);

			//Weapon UI
			gf2d_sprite_draw(
				weapon,
				vector2d(140, 615),
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				(int)mf
				);

			//Multiplier
			if (get_player()->multiplier == 2) multiplier = gf2d_sprite_load_image("images/combo_2x.png");
			else if (get_player()->multiplier == 1) multiplier = gf2d_sprite_load_image("images/combo_1x.png");
			else multiplier = gf2d_sprite_load_image("images/combo_3x.png");

			gf2d_sprite_draw(
				multiplier,
				vector2d(1200-69, 5),
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				(int)mf
				);
			
			//Combo Bar
			if (get_player()->inARow == 0) combobar = gf2d_sprite_load_image("images/0inarow.png");
			else if (get_player()->inARow == 1) combobar = gf2d_sprite_load_image("images/1inarow.png");
			else if (get_player()->inARow == 2) combobar = gf2d_sprite_load_image("images/2inarow.png");
			else if (get_player()->inARow == 3) combobar = gf2d_sprite_load_image("images/3inarow.png");
			else if (get_player()->inARow == 4) combobar = gf2d_sprite_load_image("images/4inarow.png");

			gf2d_sprite_draw(
				combobar,
				vector2d(1200 - 80, 5),
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				(int)mf
				);
			//Powerup UI
			if (get_player()->p_speed)
			{
				gf2d_sprite_draw(
					p_speed,
					vector2d(1200-69, 720-69),
					NULL,
					NULL,
					NULL,
					NULL,
					NULL,
					(int)mf
					);
			}

			if (get_player()->p_firerate)
			{
				gf2d_sprite_draw(
					p_firerate,
					vector2d(1200 - (2*69), 720 - 69),
					NULL,
					NULL,
					NULL,
					NULL,
					NULL,
					(int)mf
					);
			}

			if (get_player()->p_invinc)
			{
				gf2d_sprite_draw(
					p_invinc,
					vector2d(1200 - (3 * 69), 720 - 69),
					NULL,
					NULL,
					NULL,
					NULL,
					NULL,
					(int)mf
					);
			}

			if (get_player()->p_instakill)
			{
				gf2d_sprite_draw(
					p_instakill,
					vector2d(1200 - (4 * 69), 720 - 69),
					NULL,
					NULL,
					NULL,
					NULL,
					NULL,
					(int)mf
					);
			}

			if (get_player()->frozen)
			{
				gf2d_sprite_draw(
					frozen,
					vector2d(1200 - (5 * 69), 720 - 69),
					NULL,
					NULL,
					NULL,
					NULL,
					NULL,
					(int)mf
					);
			}

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
		
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
