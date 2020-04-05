// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_menu.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"
#include "utility.h"
#include "shared.h"
#include "scene_start.h"
#include "scene_settings.h"
#include "scene_2P_start.h"
#include "scene_rules.h"
// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
static const char* op1 = "One Player Mode";
static const char* op2 = "Two Player Mode";
static const char* volume = "Volume";
static ALLEGRO_BITMAP* back1;
static ALLEGRO_BITMAP* back2;
static ALLEGRO_BITMAP* plus;
static ALLEGRO_BITMAP* minus;
static ALLEGRO_BITMAP* plus2;
static ALLEGRO_BITMAP* minus2;
static ALLEGRO_SAMPLE* bgm;
static ALLEGRO_SAMPLE_ID bgm_id;
static void init(void);
static void draw(void);
static void destroy(void);
static void init()
{
    back1 = load_bitmap_resized("return1.png",38,38);

    back2 = load_bitmap_resized("return2.jpg",38,38);
    plus = load_bitmap_resized("plus.png",45,45);
    minus = load_bitmap_resized("minus.png",45,45);
    plus2 = load_bitmap_resized("plus2.png",45,45);
    minus2 = load_bitmap_resized("minus2.png",45,45);

    bgm = load_audio("Everything I Need.ogg");
    bgm_id = play_bgm(bgm, vol);
    game_log("Setting scene initialized");

}
static void update(void)
{
    bgm_id = play_bgm(bgm,vol);
}
static void draw(void)
{
    al_clear_to_color(al_map_rgb(32, 178, 170));
    //  One player mode.
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
    // Two player mode.
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
    if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W-48, 10, 38, 38))
        al_draw_bitmap(back2, SCREEN_W-48, 10, 0);
    else
        al_draw_bitmap(back1, SCREEN_W-48, 10, 0);
    //draw volume button.
    if (pnt_in_rect(mouse_x, mouse_y, 510, 405, 45, 45))
        al_draw_bitmap(plus2, 510, 405, 0);
    else
        al_draw_bitmap(plus, 510, 405, 0);
    if (pnt_in_rect(mouse_x, mouse_y, 245, 405, 45, 45))
        al_draw_bitmap(minus2, 245, 405, 0);
    else
        al_draw_bitmap(minus, 245, 405, 0);
    al_draw_text(font_pirulen_24, al_map_rgb(0, 0, 0), 400, 210, ALLEGRO_ALIGN_CENTER, op1);
    al_draw_text(font_pirulen_24, al_map_rgb(0, 0, 0), 400, 310, ALLEGRO_ALIGN_CENTER, op2);
    al_draw_text(font_pirulen_32, al_map_rgb(0, 0, 0), 400, 410, ALLEGRO_ALIGN_CENTER, volume);
}
static void on_mouse_down(int btn, int x, int y, int dz)
{
    if (btn == 1)
    {
        if (pnt_in_rect(x, y, SCREEN_W-48, 10, 38, 38))
            game_change_scene(scene_menu_create());

        if (pnt_in_rect(x, y, 200, 200, 400, 50))//choose 1P.
            game_change_scene(scene_rules_create());
        if (pnt_in_rect(x, y, 200, 300, 400, 50))//choose 2P.
            game_change_scene(scene_2P_start_create());

        if (pnt_in_rect(x, y, 510, 405, 45, 45))//volume++.
        {
            vol+=0.1;
            printf("%.1f\n",vol);
        }
        if (pnt_in_rect(x, y, 245, 405, 45, 45))//volume--.
        {
            vol-=0.1;
            printf("%.1f\n",vol);
        }
    }
}

static void destroy(void)
{
    al_destroy_bitmap(back1);
    al_destroy_bitmap(back2);
    al_destroy_bitmap(plus);
    al_destroy_bitmap(plus2);
    al_destroy_bitmap(minus);
    al_destroy_bitmap(minus2);
    stop_bgm(bgm_id);
    game_log("Settings scene destroyed");
}

// The only function that is shared across files.
Scene scene_settings_create(void)
{
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "Settings";
    scene.initialize = &init;
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_mouse_down = &on_mouse_down;
    // TODO: Register more event callback functions such as keyboard, mouse, ...
    game_log("Settings scene created");
    return scene;
}
