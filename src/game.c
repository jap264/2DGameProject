#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "gf2d_list.h"
#include "gf2d_audio.h"
#include "gf2d_windows.h"
#include "simple_logger.h"
#include "gf2d_config.h"
#include "gf2d_mouse.h"
#include "gf2d_input.h"
#include "combat.h"
#include "skills.h"


int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    Sprite *sprite;
    
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
    gf2d_audio_init(256,16,4,1,1,1);
    gf2d_sprite_init(1024);
    gf2d_action_list_init(128);
    gf2d_text_init("config/font.cfg");
    gf2d_input_init("config/input.cfg");
    gf2d_windows_init(128);
    skill_list_load("config/skilllist.cfg");
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/grassbattlefield.png");
    gf2d_mouse_load("actors/mouse.actor");
    combat_init();
    /*main game loop*/
    while(done == 0)
    {
        gf2d_input_update();
        /*update things here*/
        gf2d_mouse_update();
        gf2d_windows_update_all();
        
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));
            
            //UI elements last
            gf2d_windows_draw_all();
            gf2d_mouse_draw();
        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

        if (gf2d_input_command_released("exit"))done = 1;
   //     slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
