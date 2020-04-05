// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"
#include "utility.h"
#include "shared.h"
#include "scene_menu.h"
#include <math.h>

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.
static const char* txt_plane = "Planes";
static const char* txt_difficulty = "Difficulty";
static const char* txt_volume= "Volume";

int difficulty = 100;
int volume = 0;
int planePick = 1;

/* Define your static vars / function prototypes below. */
static ALLEGRO_BITMAP* img_settingsBG;
static ALLEGRO_BITMAP* img_back;
static ALLEGRO_BITMAP* img_back2;
static ALLEGRO_BITMAP* img_plane1pick;
static ALLEGRO_BITMAP* img_plane1pick2;
static ALLEGRO_BITMAP* img_plane2pick;
static ALLEGRO_BITMAP* img_plane2pick2;
static ALLEGRO_SAMPLE* bgm;
static ALLEGRO_SAMPLE_ID bgm_id;

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
static void init(void);
static void draw(void);
static void destroy(void);

static void init(void) {
    img_settingsBG = load_bitmap_resized("new_BG.png", SCREEN_W, SCREEN_H);
    img_back = al_load_bitmap("back.png");
	img_back2 = al_load_bitmap("back2.png");
	img_plane1pick = al_load_bitmap("pick_plane1.png");
	img_plane1pick2 = al_load_bitmap("pick2_plane1.png");
	img_plane2pick = al_load_bitmap("pick_plane2.png");
	img_plane2pick2 = al_load_bitmap("pick2_plane2.png");
    bgm = load_audio("Smoke.ogg");
	bgm_id = play_bgm(bgm, 1+volume);
	game_log("Setting scene initialized");
}


static void draw(void) {
	al_draw_bitmap(img_settingsBG, 0, 0, 0);

    if (pnt_in_rect(mouse_x, mouse_y, 300, 460, 200, 60))
		al_draw_bitmap(img_back2, 300, 460, 0);
	else
		al_draw_bitmap(img_back, 300, 460, 0);

    if (pnt_in_rect(mouse_x, mouse_y, 325, 130, 70, 92))
		al_draw_bitmap(img_plane1pick2, 325, 130, 0);
	else
		al_draw_bitmap(img_plane1pick, 325, 130, 0);

    if (pnt_in_rect(mouse_x, mouse_y, 402, 130, 76, 92))
		al_draw_bitmap(img_plane2pick2, 402, 130, 0);
	else
		al_draw_bitmap(img_plane2pick, 402, 130, 0);


    al_draw_text(font_Bearskin_48, al_map_rgb(255, 255, 255), 353, 80, 0, txt_plane);


    al_draw_text(font_Bearskin_48, al_map_rgb(255, 255, 255), 334, 230, 0, txt_difficulty);
    if (pnt_in_rect(mouse_x, mouse_y, 310, 288, 48, 48))
        al_draw_text(font_04b03_48, al_map_rgb(255, 237, 237), 310, 288, 0, "<");
    else
        al_draw_text(font_04b03_48, al_map_rgb(255, 219, 218), 310, 288, 0, "<");
    if (pnt_in_rect(mouse_x, mouse_y, 476, 288, 48, 48))
        al_draw_text(font_04b03_48, al_map_rgb(255, 237, 237), 476, 288, 0, ">");
    else
        al_draw_text(font_04b03_48, al_map_rgb(255, 219, 218), 476, 288, 0, ">");
    if (difficulty%3 == 0) {
        al_draw_text(font_04b03_48, al_map_rgb(255, 219, 218), 350, 288, 0, "EASY");
    }
    else if (difficulty%3 == 1) {
        al_draw_text(font_04b03_48, al_map_rgb(255, 219, 218), 342, 288, 0, "NORM");
    }
    else if (difficulty%3 == 2) {
        al_draw_text(font_04b03_48, al_map_rgb(255, 219, 218), 348, 288, 0, "HARD");
    }


    al_draw_text(font_Bearskin_48, al_map_rgb(255, 255, 255), 350, 350, 0, txt_volume);
    al_draw_textf(font_04b03_48, al_map_rgb(255, 219, 218), 403, 408, ALLEGRO_ALIGN_CENTER, "%d", volume);
    if (pnt_in_rect(mouse_x, mouse_y, 342, 408, 48, 48))
        al_draw_text(font_04b03_48, al_map_rgb(255, 237, 237), 342, 408, 0, "-");
    else
        al_draw_text(font_04b03_48, al_map_rgb(255, 219, 218), 342, 408, 0, "-");
    if (pnt_in_rect(mouse_x, mouse_y, 444, 408, 48, 48))
        al_draw_text(font_04b03_48, al_map_rgb(255, 237, 237), 444, 408, 0, "+");
    else
        al_draw_text(font_04b03_48, al_map_rgb(255, 219, 218), 444, 408, 0, "+");
}

static void destroy(void) {
    al_destroy_sample(bgm);
	al_destroy_bitmap(img_settingsBG);
	al_destroy_bitmap(img_back);
	al_destroy_bitmap(img_back2);

	game_log("Settings scene destroyed");
}

static void on_mouse_down(int btn, int x, int y, int dz) {
	if (btn == 1) {
		if (pnt_in_rect(x, y, 300, 460, 200, 60))
            game_change_scene(scene_menu_create());
        if (pnt_in_rect(x, y, 320, 130, 70, 92))
            planePick = 1;
        if (pnt_in_rect(x, y, 395, 130, 76, 92))
            planePick = 2;
        if (pnt_in_rect(x, y, 342, 408, 48, 48))
            volume--;
        if (pnt_in_rect(x, y, 444, 408, 48, 48))
            volume++;
        if (pnt_in_rect(x, y, 310, 288, 48, 48))
            difficulty--;
        if (pnt_in_rect(x, y, 476, 288, 48, 48))
            difficulty++;
	}
}


// The only function that is shared across files.
Scene scene_settings_create(void) {
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
