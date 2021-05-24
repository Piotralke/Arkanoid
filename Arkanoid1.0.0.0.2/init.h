#pragma once
#ifndef INIT_H
#define INIT_H
#include "include_lib.h"

bool working;
ALLEGRO_DISPLAY* display ;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer_FPS ;
ALLEGRO_BITMAP* tlo ;
ALLEGRO_BITMAP* menu1 ;
ALLEGRO_BITMAP* menu2 ;
ALLEGRO_BITMAP* menu3 ;
ALLEGRO_BITMAP* menu4 ;
ALLEGRO_BITMAP* opcje1 ;
ALLEGRO_BITMAP* opcje2;
ALLEGRO_BITMAP* opcje3 ;
ALLEGRO_BITMAP* wyniki ;
ALLEGRO_BITMAP* zycie ;
ALLEGRO_BITMAP* gameover ;
ALLEGRO_BITMAP* youwin ;
ALLEGRO_BITMAP* faster_ball;
ALLEGRO_BITMAP* slower_ball;
ALLEGRO_BITMAP* bigger_platform;
ALLEGRO_BITMAP* smaller_platform;
ALLEGRO_BITMAP* going_through;
ALLEGRO_SAMPLE* ruch ;
ALLEGRO_SAMPLE* klik ;
ALLEGRO_SAMPLE* check ;
ALLEGRO_SAMPLE* hit ;
ALLEGRO_SAMPLE* destroy ;
ALLEGRO_SAMPLE* gameover_m;
ALLEGRO_SAMPLE* youwin_m ;
ALLEGRO_SAMPLE* music ;
ALLEGRO_SAMPLE* bonus_m;
ALLEGRO_SAMPLE_INSTANCE* musicInstance ;
ALLEGRO_FONT* font ;
FILE* scores;
extern void init_arkanoid();
#endif // !INIT_H
