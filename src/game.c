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

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *background;
    
    int mx,my;
    float mf = 0;
    Sprite *mouse, *health, *weapon;
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

	//Health UI
	if (get_player_health() == 3) health = gf2d_sprite_load_image("images/full_health.png");
	else if (get_player_health() == 2) health = gf2d_sprite_load_image("images/half_health.png");
	else if (get_player_health() == 1) health = gf2d_sprite_load_image("images/low_health.png");
	else health = gf2d_sprite_load_image("images/no_health.png");

	slog("main game loop begin");
    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
		//if (SDL_GetTicks() % 10000) slog("%i, %i", mx, my);
        /*mf+=0.1;
        if (mf >= 16.0)mf = 0;*/
        
		entity_manager_think_entities();
		entity_manager_update_entities();

		level_update(level);
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first

			level_draw(level);
            gf2d_sprite_draw_image(background,vector2d(0,0));
			//gf2d_sprite_draw_image(player->ent->sprite, vector2d(0, 0));

			entity_manager_draw_entities();
            
			//UI elements last
				//Weapon UI
			if (keys[SDL_SCANCODE_1]) weapon = gf2d_sprite_load_image("images/pistol.png");
			else if (keys[SDL_SCANCODE_2]) weapon = gf2d_sprite_load_image("images/submachine_gun.png");
			else if (keys[SDL_SCANCODE_3]) weapon = gf2d_sprite_load_image("images/lmg.png");
			else if (keys[SDL_SCANCODE_4]) weapon = gf2d_sprite_load_image("images/sniper.png");
			else if (keys[SDL_SCANCODE_5]) weapon = gf2d_sprite_load_image("images/rocket_launcher.png");
			else if (keys[SDL_SCANCODE_6]) weapon = gf2d_sprite_load_image("images/thunder_gun.png");
			else if (keys[SDL_SCANCODE_Q]) weapon = gf2d_sprite_load_image("images/hammer.png");
			else if (keys[SDL_SCANCODE_E]) weapon = gf2d_sprite_load_image("images/grenade.png");
			else if (keys[SDL_SCANCODE_Z]) weapon = gf2d_sprite_load_image("images/mine.png");
			else if (keys[SDL_SCANCODE_C]) weapon = gf2d_sprite_load_image("images/monkey_bomb.png");


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

        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
		
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
