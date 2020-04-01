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

static ALLEGRO_BITMAP* img_background;
static ALLEGRO_BITMAP* back1;
static ALLEGRO_BITMAP* back2;
static ALLEGRO_BITMAP* tryagain;
static void init()
{
    img_background = load_bitmap_resized("pause bg.png",SCREEN_W,SCREEN_H);
    back1 = load_bitmap_resized("return1.png",38,38);

    back2 = load_bitmap_resized("return2.jpg",38,38);
    tryagain = load_bitmap_resized("try_again.jpg",430,430);
    game_log("Pause scene initialized");

}
static void draw(void)
{
    al_draw_bitmap(img_background,0,0,0);
    al_draw_bitmap(tryagain,175,125,0);
    if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W-48, 10, 38, 38))
        al_draw_bitmap(back2, SCREEN_W-48, 10, 0);
    else
        al_draw_bitmap(back1, SCREEN_W-48, 10, 0);

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
        if (pnt_in_rect(x, y, SCREEN_W-48, 10, 38, 38))
            game_change_scene(scene_menu_create());
    }
}
static void destroy(void)
{
    al_destroy_bitmap(img_background);
    al_destroy_bitmap(back1);
    al_destroy_bitmap(back2);
    al_destroy_bitmap(tryagain);
    game_log("Gameover scene destroyed");
}
Scene scene_gameover_create(void)
{
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "Gameover";
    scene.initialize = &init;
    scene.draw = &draw;
    scene.destroy = &destroy;
//	scene.on_key_down = &on_key_down;
    // [HACKATHON 3-8]
    // TODO: Register on_mouse_down.
    // Uncomment the code below.
    scene.on_mouse_down = &on_mouse_down;
    // TODO: Register more event callback functions such as update, mouse, ...
    game_log("Gameover scene created");
    return scene;
}
