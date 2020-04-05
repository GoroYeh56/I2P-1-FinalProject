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
static ALLEGRO_BITMAP* enemy1;
static ALLEGRO_BITMAP* enemy2;
static ALLEGRO_BITMAP* enemy3;
static ALLEGRO_BITMAP* attack;
static ALLEGRO_BITMAP* poison;
static ALLEGRO_BITMAP* heal;
static ALLEGRO_BITMAP* weapon1;
static ALLEGRO_BITMAP* weapon2;
static ALLEGRO_BITMAP* weapon3;
static ALLEGRO_BITMAP* player1;
static ALLEGRO_BITMAP* player2;
static ALLEGRO_BITMAP* player3;
static void init()
{
    img_background = load_bitmap_resized("start-bg.jpg",SCREEN_W,SCREEN_H);
    enemy1 = load_bitmap_resized("pirate.png",50,50);
    enemy2 = load_bitmap_resized("Maui.png",90,120);
    enemy3 = load_bitmap_resized("bad_mask.png",80,120);
    attack = load_bitmap_resized("knife.png",50,50);
    poison = load_bitmap_resized("poison.jpg",50,50);
    heal = load_bitmap_resized("heal bottle.png",50,50);
    weapon1 = load_bitmap_resized("baseball.png",50,50);
    weapon2 = load_bitmap_resized("Rapunzel.png",50,50);
    weapon3 = load_bitmap_resized("iceball.png",50,50);
    player1 = load_bitmap_resized("player.png",50,50);
    player2 = load_bitmap_resized("Moana.png",90,120);
    player3 = load_bitmap_resized("Anna.png",50,100);
    game_log("Rules scene initialized");

}
static void draw(void)
{
    al_draw_bitmap(img_background,0,0,0);

    al_draw_text(font_pirulen_32, al_map_rgb(0,0,0),400,20,ALLEGRO_ALIGN_CENTER,"Rules :");
    al_draw_text(font_pirulen_24, al_map_rgb(0,0,0),100,80,ALLEGRO_ALIGN_LEFT,"Enemies :");
    al_draw_text(font_pirulen_24, al_map_rgb(0,0,0),100,180,ALLEGRO_ALIGN_LEFT,"Attack :");
    al_draw_text(font_pirulen_24, al_map_rgb(0,0,0),300,180,ALLEGRO_ALIGN_LEFT,"Poison :");
    al_draw_text(font_pirulen_24, al_map_rgb(0,0,0),500,180,ALLEGRO_ALIGN_LEFT,"Heal bottle :");
    al_draw_text(font_pirulen_24, al_map_rgb(0,0,0),100,300,ALLEGRO_ALIGN_LEFT,"Your Weapons :");
    al_draw_text(font_pirulen_24, al_map_rgb(0,0,0),100,430,ALLEGRO_ALIGN_LEFT,"Heroes :");
    al_draw_text(font_pirulen_24, al_map_rgb(0,0,0),SCREEN_W/2,SCREEN_H-50,ALLEGRO_ALIGN_CENTER,"Press Enter to start...");


    al_draw_bitmap(enemy1,100,120,0);
    al_draw_bitmap(enemy2,300,50,0);
    al_draw_bitmap(enemy3,500,50,0);
    al_draw_bitmap(attack,100,220,0);
    al_draw_bitmap(poison,300,220,0);
    al_draw_bitmap(heal,500,220,0);
    al_draw_bitmap(weapon1,100,350,0);
    al_draw_bitmap(weapon2,300,350,0);
    al_draw_bitmap(weapon3,500,350,0);
    al_draw_bitmap(player1,100,480,0);
    al_draw_bitmap(player2,300,410,0);
    al_draw_bitmap(player3,500,430,0);


}

static void on_key_down(int keycode)
{
    if (keycode == ALLEGRO_KEY_ENTER)
        game_change_scene(scene_start_create());
}
/*
static void on_mouse_down(int btn, int x, int y, int dz) {
	if (btn == 1) {

        if (pnt_in_rect(x, y, 200, 200, 400, 50))//back to menu.
			game_change_scene(scene_level2_create());
        if (pnt_in_rect(x, y, 200, 300, 400, 50))//quit the game.
			game_change_scene(scene_gameover_create());
	}
}*/
static void destroy(void)
{
    al_destroy_bitmap(enemy1);
    al_destroy_bitmap(enemy2);
    al_destroy_bitmap(enemy3);
    al_destroy_bitmap(attack);
    al_destroy_bitmap(poison);
    al_destroy_bitmap(heal);
    al_destroy_bitmap(weapon1);
    al_destroy_bitmap(weapon2);
    al_destroy_bitmap(weapon3);
    al_destroy_bitmap(player1);
    al_destroy_bitmap(player2);
    al_destroy_bitmap(player3);
    game_log("Rules scene destroyed");
}
Scene scene_rules_create(void)
{
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "Rules";
    scene.initialize = &init;
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_key_down = &on_key_down;
    // [HACKATHON 3-8]
    // TODO: Register on_mouse_down.
    // Uncomment the code below.
//	scene.on_mouse_down = &on_mouse_down;
    // TODO: Register more event callback functions such as update, mouse, ...
    game_log("Rules scene created");
    return scene;
}
