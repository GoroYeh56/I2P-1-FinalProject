// [shared.c]
// you should define the shared variable declared in the header here.

#include "shared.h"
#include "utility.h"
#include "game.h"
#include "scene_menu.h"

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;
ALLEGRO_FONT* font_score;
ALLEGRO_FONT* font_time;
double start_time;
double now;
int left_time=90*60;
double vol = 1.0;

void shared_init(void)
{
    font_pirulen_32 = load_font("pirulen.ttf", 32);
    font_pirulen_24 = load_font("pirulen.ttf", 24);
    font_score = load_font("04b_09__.ttf", 36);
    font_time = load_font("04b_09__.ttf",24);
    game_change_scene(scene_menu_create());
}

void shared_destroy(void)
{
    al_destroy_font(font_pirulen_32);
    al_destroy_font(font_pirulen_24);
    al_destroy_font(font_score);
    al_destroy_font(font_time);
}
