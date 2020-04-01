#include "scene_menu.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include "game.h"
#include "utility.h"
#include "shared.h"
#include "scene_start.h"
#include "scene_settings.h"
#include "scene_gameover.h"
#include "scene_level2.h"
static const char* op1 = "Ready!";
static const char* op2 = "Quit game";
static ALLEGRO_BITMAP* img_background;
static ALLEGRO_BITMAP* back1;
static ALLEGRO_BITMAP* back2;
static void init()
{
    img_background = load_bitmap_resized("pause bg.png",SCREEN_W,SCREEN_H);
    back1 = load_bitmap_resized("return1.png",38,38);

    back2 = load_bitmap_resized("return2.jpg",38,38);
    game_log("1 to 2 scene initialized");

}
static void draw(void)
{
    al_draw_bitmap(img_background,0,0,0);
    al_clear_to_color(al_map_rgb(32, 178, 170));

    al_draw_text(font_pirulen_32, al_map_rgb(0,0,0),400,100,ALLEGRO_ALIGN_CENTER,"Congratulations!");
    al_draw_text(font_pirulen_24, al_map_rgb(0,0,0),400,150,ALLEGRO_ALIGN_CENTER,"Ready for Level 2?");

    if (pnt_in_rect(mouse_x, mouse_y, 200, 200, 400, 50))
    {
        al_draw_rounded_rectangle(200, 200,600, 250,10,10, al_map_rgb(0,0,0), 1.5); //last parameter->thickness of line.
        al_draw_filled_rounded_rectangle(200,200,600,250,10,10,al_map_rgb(255,140,0));
    }
    else
    {
        al_draw_rounded_rectangle(200, 200,600, 250,10,10, al_map_rgb(0,0,0), 1.5); //last parameter->thickness of line.
        al_draw_filled_rounded_rectangle(200,200,600,250,10,10,al_map_rgb(255,255,255));
    }

    if (pnt_in_rect(mouse_x, mouse_y, 200, 300, 400, 50))
    {
        al_draw_rounded_rectangle(200, 300,600, 350,10,10, al_map_rgb(0,0,0), 1.5); //last parameter->thickness of line.
        al_draw_filled_rounded_rectangle(200,300,600,350,10,10,al_map_rgb(255,140,0));
    }
    else
    {
        al_draw_rounded_rectangle(200, 300,600, 350,10,10, al_map_rgb(0,0,0), 1.5); //last parameter->thickness of line.
        al_draw_filled_rounded_rectangle(200,300,600,350,10,10,al_map_rgb(255,255,255));
    }


    al_draw_text(font_pirulen_32, al_map_rgb(0, 0, 0), 400, 210, ALLEGRO_ALIGN_CENTER, op1);
    al_draw_text(font_pirulen_24, al_map_rgb(0, 0, 0), 400, 310, ALLEGRO_ALIGN_CENTER, op2);



}
/*
static void on_key_down(int keycode) {
	if (keycode == ALLEGRO_KEY_ENTER)
		game_change_scene(scene_start_create());
}*/

static void on_mouse_down(int btn, int x, int y, int dz)
{
    if (btn == 1)
    {

        if (pnt_in_rect(x, y, 200, 200, 400, 50))//back to menu.
            game_change_scene(scene_level2_create());
        if (pnt_in_rect(x, y, 200, 300, 400, 50))//quit the game.
            game_change_scene(scene_gameover_create());
    }
}
static void destroy(void)
{
    al_destroy_bitmap(back1);
    al_destroy_bitmap(back2);
    game_log("1 to 2 scene destroyed");
}
Scene scene_1to2_create(void)
{
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "1 to 2";
    scene.initialize = &init;
    scene.draw = &draw;
    scene.destroy = &destroy;
//	scene.on_key_down = &on_key_down;
    // [HACKATHON 3-8]
    // TODO: Register on_mouse_down.
    // Uncomment the code below.
    scene.on_mouse_down = &on_mouse_down;
    // TODO: Register more event callback functions such as update, mouse, ...
    game_log("1 to 2 scene created");
    return scene;
}
