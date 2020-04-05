#include "scene_start.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "game.h"
#include "utility.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "scene_menu.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_opengl.h>
#include "shared.h"
#include "scene_settings.h"
#include "scene_pause.h"
#include "scene_gameover.h"
#include "scene_level2.h"
#include "scene_pause2.h"
#include "scene_2to3.h"
// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
static const char* score = "Scores";
static ALLEGRO_BITMAP* img_background;
static ALLEGRO_BITMAP* img_plane;
static ALLEGRO_BITMAP* img_enemy;
static ALLEGRO_BITMAP* img_enemy2;
static ALLEGRO_BITMAP* img_life;
static ALLEGRO_BITMAP* img_pause1;
static ALLEGRO_BITMAP* img_pause2;
static int scores;

// [HACKATHON 2-1]
// TODO: Declare a variable to store your bullet's image.
// Uncomment and fill in the code below.
static ALLEGRO_BITMAP* img_bullet;

typedef struct
{
    // The center coordinate of the image.
    float x, y;
    // The width and height of the object.
    float w, h;
    // The velocity in x, y axes.
    float vx, vy;
    // Should we draw this object on the screen.
    bool hidden;
    // The pointer to the object¡¦s image.
    ALLEGRO_BITMAP* img;
} MovableObject;

static void init(void);
static void update(void);
static void draw_movable_object(MovableObject obj);
static void draw(void);
static void destroy(void);

#define MAX_ENEMY 5
#define MAX_ENEMY2 2
// [HACKATHON 2-2]
// TODO: Declare the max bullet count that will show on screen.
// You can try max 4 bullets here and see if you needed more.
// Uncomment and fill in the code below.
#define MAX_BULLET 4
static MovableObject plane;
static MovableObject enemies[MAX_ENEMY];
static MovableObject enemies2[MAX_ENEMY2];
// [HACKATHON 2-3]
// TODO: Declare an array to store bullets with size of max bullet count.
// Uncomment and fill in the code below.
static MovableObject bullets[MAX_BULLET];
// [HACKATHON 2-4]
// TODO: Set up bullet shooting cool-down variables.
// 1) Declare your shooting cool-down time as constant. (0.2f will be nice)
// 2) Declare your last shoot timestamp.
// Uncomment and fill in the code below.
static const float MAX_COOLDOWN = 0.2f;
static double last_shoot_timestamp;
static double last_hitten_time;
static ALLEGRO_SAMPLE* bgm;
static ALLEGRO_SAMPLE_ID bgm_id;
static bool draw_gizmos;
static int blood=150;
static int life=3;
static void init(void)
{
    left_time = 90*60;
    img_pause1 =  load_bitmap_resized("pause1.jpg",38,38);
    img_pause2 =  load_bitmap_resized("pause2.png",38,38);


    int i;
    img_background = load_bitmap_resized("iceland.jpg", SCREEN_W, SCREEN_H);
    img_plane = plane.img = load_bitmap_resized("Moana.png",54,102);
    plane.x = 400;
    plane.y = 500;
    plane.w = 54;
    plane.h = 102;
    img_enemy = load_bitmap("smallfighter0006.png");
    for (i = 0; i < MAX_ENEMY; i++)
    {
        enemies[i].w = 28;
        enemies[i].h = 68;
        enemies[i].x = enemies[i].w / 2 + (float)rand() / RAND_MAX * (SCREEN_W - enemies[i].w);
        enemies[i].y = enemies[i].h/2 + (float)rand()/RAND_MAX * (SCREEN_H - enemies[i].h);
        enemies[i].vx = 0;
        enemies[i].vy = 2;
        enemies[i].img = img_enemy;
    }
    img_enemy2 = load_bitmap_resized("Maui.png",94,105);
    for(i=0; i<MAX_ENEMY2; i++)
    {
        enemies2[i].w = 94;
        enemies2[i].h = 105;
        enemies2[i].x = enemies2[i].w / 2 + (float)rand() / RAND_MAX * (SCREEN_W - enemies2[i].w);
        enemies2[i].y = enemies2[i].h/2 + (float)rand()/RAND_MAX * (SCREEN_H - enemies2[i].h);
        enemies2[i].vx = 0;
        enemies2[i].vy = 3;
        enemies2[i].img = img_enemy2;
    }
    // [HACKATHON 2-5]
    // TODO: Initialize bullets.
    // 1) Search for a bullet image online and put it in your project.
    //    You can use the image we provided.
    // 2) Load it in by 'load_bitmap' or 'load_bitmap_resized'.
    // 3) For each bullets in array, set their w and h to the size of
    //    the image, and set their img to bullet image, hidden to true,
    //    (vx, vy) to (0, -3).
    // Uncomment and fill in the code below.
    img_bullet = load_bitmap_resized("Rapunzel.png",90,120);
    for (i=0; i<MAX_BULLET; i++)
    {
        bullets[i].w = 90;
        bullets[i].h = 120;
        bullets[i].img = img_bullet;
        bullets[i].vx = 0;
        bullets[i].vy = -3;
        bullets[i].hidden = true;
    }

    img_life = load_bitmap_resized("life.png",40,40);
    // Can be moved to shared_init to decrease loading time.
    bgm = load_audio("Where No one Goes.ogg");
    game_log("Start scene initialized");
    bgm_id = play_bgm(bgm, vol);
}

static void update(void)
{
    left_time--;
    plane.vx = plane.vy = 0;
    if (key_state[ALLEGRO_KEY_UP] || key_state[ALLEGRO_KEY_W])
        plane.vy -= 1;
    if (key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_S])
        plane.vy += 1;
    if (key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_A])
        plane.vx -= 1;
    if (key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_D])
        plane.vx += 1;
    // 0.71 is (1/sqrt(2)).
    plane.y += plane.vy * 4 * (plane.vx ? 0.71f : 1);
    plane.x += plane.vx * 4 * (plane.vy ? 0.71f : 1);
    // [HACKATHON 1-1]
    // TODO: Limit the plane's collision box inside the frame.
    //       (x, y axes can be separated.)
    // Uncomment and fill in the code below.
    if (plane.x-plane.w/2 < 0)
        plane.x = plane.w/2;
    else if (plane.x+plane.w/2 > SCREEN_W)
        plane.x = SCREEN_W-plane.w/2;
    if (plane.y -plane.h/2 < 0)
        plane.y = plane.h/2;
    else if (plane.y + plane.h/2 > SCREEN_H)
        plane.y = SCREEN_H-plane.h/2;
    // [HACKATHON 2-6]
    // TODO: Update bullet coordinates.
    // 1) For each bullets, if it's not hidden, update x, y
    // according to vx, vy.
    // 2) If the bullet is out of the screen, hide it.
    // Uncomment and fill in the code below.
    int i;
    for (i=0; i<MAX_BULLET; i++)
    {
        if (bullets[i].hidden)
        {
            bullets[i].x = SCREEN_W+10;
            bullets[i].y = SCREEN_H+10;
            continue;
        }
        bullets[i].x += bullets[i].vx;
        bullets[i].y += bullets[i].vy;
        if (bullets[i].y < 0)
            bullets[i].hidden = true;
    }

    for(i=0; i<MAX_ENEMY; i++)
    {
        enemies[i].y += enemies[i].vy;
        if(enemies[i].y -enemies[i].h/2 -1.5 >SCREEN_H)
        {
            enemies[i].x = enemies[i].w / 2 + (float)rand() / RAND_MAX * (SCREEN_W - enemies[i].w);
            enemies[i].y = 0;
        }

    }
    for(i=0; i<MAX_ENEMY2; i++)
    {
        enemies2[i].y += enemies2[i].vy;
        if(enemies2[i].y -enemies2[i].h/2 -1.5 >SCREEN_H)
        {
            enemies2[i].x = enemies2[i].w / 2 + (float)rand() / RAND_MAX * (SCREEN_W - enemies2[i].w);
            enemies2[i].y = 0;
        }

    }

    // [HACKATHON 2-7]
    // TODO: Shoot if key is down and cool-down is over.
    // 1) Get the time now using 'al_get_time'.
    // 2) If Space key is down in 'key_state' and the time
    //    between now and last shoot is not less that cool
    //    down time.
    // 3) Loop through the bullet array and find one that is hidden.
    //    (This part can be optimized.)
    // 4) The bullet will be found if your array is large enough.
    // 5) Set the last shoot time to now.
    // 6) Set hidden to false (recycle the bullet) and set its x, y to the
    //    front part of your plane.
    // Uncomment and fill in the code below.
    now = al_get_time();
    if (key_state[ALLEGRO_KEY_SPACE] && now - last_shoot_timestamp >= MAX_COOLDOWN)
    {
        for (i=0; i<MAX_BULLET; i++)
        {
            if (bullets[i].hidden)
                break;
        }
        if (i == MAX_BULLET)
            return;
        last_shoot_timestamp = now;
        bullets[i].x = plane.x;
        bullets[i].y = plane.y-plane.h/2;
        bullets[i].hidden = false;
    }

    //if bullet hit enemies. enemies will disappear. and scores plus ten.
    int j;
    for(i=0; i<MAX_BULLET; i++)
    {
        for(j=0; j<MAX_ENEMY; j++)
        {
            if(bullets[i].x<=enemies[j].x+enemies[j].w/2 && bullets[i].x>=enemies[j].x-enemies[j].w/2 && bullets[i].y<=enemies[j].y+enemies[j].h/2 &&bullets[i].y>=enemies[j].y - enemies[j].h/2)
            {
                bullets[i].hidden = true;
                enemies[j].y = -50;
                scores +=10;
            }
        }
    }

    for(i=0; i<MAX_BULLET; i++)
    {
        for(j=0; j<MAX_ENEMY2; j++)
        {
            if(bullets[i].x<=enemies2[j].x+enemies2[j].w/2 && bullets[i].x>=enemies2[j].x-enemies2[j].w/2 && bullets[i].y<=enemies2[j].y+enemies2[j].h/2 &&bullets[i].y>=enemies2[j].y - enemies2[j].h/2)
            {
                bullets[i].hidden = true;
                enemies2[j].y = -50;
                scores +=30;
            }
        }
    }

    double safe_time= al_get_time();
    for(i=0; i<MAX_ENEMY; i++)
    {
        if (plane.x<= enemies[i].x + (enemies[i].w)/2 && plane.x>= enemies[i].x-(enemies[i].w)/2 && plane.y<=enemies[i].y+(enemies[i].h)/2 && plane.y>=enemies[i].y-enemies[i].h/2&& safe_time - last_hitten_time>= 5)
        {
            blood -=1;
            if(blood <= 0)
            {
                life--;
                blood = 150;
            }
        }
    }
    safe_time= al_get_time();
    for(i=0; i<MAX_ENEMY2; i++)
    {
        if (plane.x<= enemies2[i].x + (enemies2[i].w)/2 && plane.x>= enemies2[i].x-(enemies2[i].w)/2 && plane.y<=enemies2[i].y+(enemies2[i].h)/2 && plane.y>=enemies2[i].y-enemies2[i].h/2&& safe_time - last_hitten_time>= 5)
        {
            blood -=10;
            if(blood <= 0)
            {
                life--;
                blood = 150;
            }
        }
    }

    if(left_time==0)
        game_change_scene(scene_gameover_create());
    if(scores>=20)
        game_change_scene(scene_2to3_create());
}



static void draw_movable_object(MovableObject obj)
{
    if (obj.hidden)
        return;
    al_draw_bitmap(obj.img, round(obj.x - obj.w / 2), round(obj.y - obj.h / 2), 0);
    if (draw_gizmos)
    {
        al_draw_rectangle(round(obj.x - obj.w / 2), round(obj.y - obj.h / 2),
                          round(obj.x + obj.w / 2) + 1, round(obj.y + obj.h / 2) + 1, al_map_rgb(255, 0, 0), 0);
    }
}

static void draw(void)
{

    int i;
    al_draw_bitmap(img_background, 0, 0, 0);
    if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W-48, 10, 38, 38))
        al_draw_bitmap(img_pause2, SCREEN_W-48, 10, 0);
    else
        al_draw_bitmap(img_pause1, SCREEN_W-48, 10, 0);
    // [HACKATHON 2-8]
    // TODO: Draw all bullets in your bullet array.
    // Uncomment and fill in the code below.

    al_draw_rectangle(10, 50, 150, 60, al_map_rgb(0,0,0), 1.5);//last parameter->thickness of line.
    al_draw_filled_rectangle(10,50,10+blood,60,al_map_rgb(220,20,60));

    for (i=0; i<MAX_BULLET; i++)
        draw_movable_object(bullets[i]);
    draw_movable_object(plane);
    for (i = 0; i < MAX_ENEMY; i++)
        draw_movable_object(enemies[i]);
    for (i = 0; i < MAX_ENEMY2; i++)
        draw_movable_object(enemies2[i]);

    if(life>=1)
        al_draw_bitmap(img_life,10,10,0);
    if(life>=2)
        al_draw_bitmap(img_life,50,10,0);
    if(life>=3)
        al_draw_bitmap(img_life,90,10,0);
    if(life==0)
        game_change_scene(scene_gameover_create());
    al_draw_textf(font_score, al_map_rgb(255, 255, 255), 150, SCREEN_H-50, ALLEGRO_ALIGN_CENTER,"Scores : %d",scores);
    al_draw_text(font_pirulen_24, al_map_rgb(255, 255, 255), SCREEN_W-200, 15, ALLEGRO_ALIGN_CENTER,"Target : 200");
    al_draw_textf(font_time, al_map_rgb(255, 255, 255), SCREEN_W-300,SCREEN_H-40, ALLEGRO_ALIGN_LEFT,"Time left : %i",(left_time/FPS));
}

static void destroy(void)
{
    al_destroy_bitmap(img_background);
    al_destroy_bitmap(img_plane);
    al_destroy_bitmap(img_enemy);
    al_destroy_sample(bgm);
    al_destroy_bitmap(img_pause1);
    al_destroy_bitmap(img_pause2);
    // [HACKATHON 2-9]
    // TODO: Destroy your bullet image.
    // Uncomment and fill in the code below.
    al_destroy_bitmap(img_bullet);
    stop_bgm(bgm_id);
    game_log("Level 2 scene destroyed");
}

static void on_key_down(int keycode)
{
    if (keycode == ALLEGRO_KEY_TAB)
        draw_gizmos = !draw_gizmos;
}
static void on_mouse_down(int btn, int x, int y, int dz)
{
    if (btn == 1)
    {
        if (pnt_in_rect(x, y, SCREEN_W-48, 10, 38, 38))
            game_change_scene(scene_pause2_create());
    }
}

// TODO: Add more event callback functions such as keyboard, mouse, ...

// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_level2_create(void)
{
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "Level 2";
    scene.initialize = &init;
    scene.update = &update;
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_key_down = &on_key_down;
    scene.on_mouse_down = &on_mouse_down;
    // TODO: Register more event callback functions such as keyboard, mouse, ...
    game_log("Level2 scene created");
    return scene;
}
