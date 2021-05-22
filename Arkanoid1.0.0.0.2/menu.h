#pragma once
#ifndef MENU_H
#define MENU_H
#include "include_lib.h"

extern void wynik(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* wyniki, FILE* scores, ALLEGRO_SAMPLE* klik);
extern void opcje(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* opcje1, ALLEGRO_BITMAP* opcje2, ALLEGRO_BITMAP* opcje3, ALLEGRO_FONT* font,
                 ALLEGRO_SAMPLE* ruch, ALLEGRO_SAMPLE* klik, ALLEGRO_SAMPLE* check, ALLEGRO_SAMPLE_INSTANCE* musicInstance);
extern bool menu(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* menu1, ALLEGRO_BITMAP* menu2, ALLEGRO_BITMAP* menu3, ALLEGRO_BITMAP* menu4,
                 ALLEGRO_BITMAP* opcje1, ALLEGRO_BITMAP* opcje2, ALLEGRO_BITMAP* opcje3, ALLEGRO_BITMAP* wyniki, FILE* scores, ALLEGRO_FONT* font,
                 ALLEGRO_SAMPLE* ruch, ALLEGRO_SAMPLE* klik, ALLEGRO_SAMPLE* check, ALLEGRO_SAMPLE_INSTANCE* musicInstance);
extern void read_scores(FILE* scores, ALLEGRO_FONT* font);
#endif // !MENU_H
