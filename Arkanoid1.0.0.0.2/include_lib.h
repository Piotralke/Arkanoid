#pragma once
/// @file include_lib.h Plik include_lib.h zawiera deklaracje wszystkich do³¹czonych bibliotek potrzebnych do naszego projektu, 
///takich jak np. allegro, stdio, czy stdbool oraz deklaracje zmiennych globalnych i struktur
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_native_dialog.h>
#include <Windows.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
///@param width Szerokoœæ ekranu aplikacji
#define width  800
///@param height Wysokoœæ ekranu aplikacji
#define height  900
///@param MAX_LVL Maksymalny poziom zagnie¿d¿enia drzewa czwórkowego
#define MAX_LVL 5
int ball_move;
int size;
int debug ;
int sound ;
int pause;
int lifes ;
int block_counter;
int points ;
int choice_lvl;
int ball_speed;
int ball_s;
int bonus_active;
int bonus_speed;
int g_t;
int bonus_time;
int score_multiplier;
/**
* @brief Struktura zawieraj¹ca informacje o koordynatach bloczków oraz platformy
* @param x Wspó³rzêdna x bloczku
* @param y Wspó³rzêdna y bloczku
* @param w Szerokoœæ bloczku
* @param h Wysokoœæ bloczku
* @param state Okreœla stan bloczku(dla platformy jest zawsze ustawiany na jeden przy ka¿dej nowej pêtli gry)
*/ 
struct block
{
    int x;
    int y;
    int w;
    int h;
    bool state;
};
/**@brief Struktura zawieraj¹ca informacje o wêz³ach drzewa czwórkowego
* @param x Wspó³rzêdna x æwiartki
* @param y Wspó³rzêdna y æwiartki
* @param w Szerokoœæ æwiartki
* @param h Wysokoœæ æwiartki
* @param ne WskaŸnik na praw¹ górn¹ æwiartkê
* @param nw WskaŸnik na lew¹ górn¹ æwiartkê
* @param sw WskaŸnik na lew¹ doln¹ æwiartkê
* @param se WskaŸnik na praw¹ doln¹ æwiartkê
*/
struct Quad_Tree_Node
{
    int h;
    int w;
    int x;
    int y;
    struct Quad_Tree_Node* ne, * nw, * sw, * se;
};
/** @brief Struktura zawierajaca informacje o pi³ce
* @param x Wspó³rzêdna x pi³ki
* @param y Wspó³rzêdna y pi³ki
* @param r Promieñ pi³ki
* @param vx Wektor przesuniêcia w osi X pi³ki
* @param vy Wektor przesuniêcia w osi Y pi³ki
*/
struct Ball
{
    int x;
    int y;
    int r;
    int vx;
    int vy;
};
/**@brief Struktura zawieraj¹ca informacje o bonusie
* @param x Wspó³rzêdna x bonusu
* @param y Wspó³rzêdna y bonusu
* @param w Szerokoœæ bonusu
* @param h Wysokoœæ bonusu
* @param type Typ bonusu
* @param bonus_bitmap WskaŸnik na bitmapê reprezentuj¹c¹ odpowiedni bonus
*/ 
struct bonus
{
    int x;
    int y;
    int w;
    int h;
    int type;
    ALLEGRO_BITMAP* bonus_bitmap;
};
