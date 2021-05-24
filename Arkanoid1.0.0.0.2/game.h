#ifndef GAME_H
#define GAME_H
#include "include_lib.h"
#include "levels.h"
#include "physic.h"
#include "bonus.h"
#include "quadtree.h"
#include "menu.h"

extern void wait_for_keypress();
extern void game(bool working, struct block** array, struct Quad_Tree_Node* root, struct block Platform, struct Ball New_Ball, struct bonus New_bonus,
    ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* menu1, ALLEGRO_BITMAP* menu2, ALLEGRO_BITMAP* menu3, ALLEGRO_BITMAP* menu4,
    ALLEGRO_BITMAP* opcje1, ALLEGRO_BITMAP* opcje2, ALLEGRO_BITMAP* opcje3, ALLEGRO_BITMAP* wyniki, ALLEGRO_BITMAP* tlo, ALLEGRO_BITMAP* zycie,
    ALLEGRO_BITMAP* gameover, ALLEGRO_BITMAP* youwin, FILE* scores, ALLEGRO_FONT* font, ALLEGRO_SAMPLE* ruch, ALLEGRO_SAMPLE* klik, ALLEGRO_SAMPLE* check,
    ALLEGRO_SAMPLE* hit, ALLEGRO_SAMPLE* destroy, ALLEGRO_SAMPLE* gameover_m, ALLEGRO_SAMPLE* youwin_m, ALLEGRO_SAMPLE_INSTANCE* musicInstance);

#endif // !GAME_H
