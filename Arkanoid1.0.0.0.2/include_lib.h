#pragma once
/// @file include_lib.h Plik include_lib.h zawiera deklaracje wszystkich do��czonych bibliotek potrzebnych do naszego projektu, 
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
///@param width Szeroko�� ekranu aplikacji
#define width  800
///@param height Wysoko�� ekranu aplikacji
#define height  900
///@param MAX_LVL Maksymalny poziom zagnie�d�enia drzewa czw�rkowego
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
* @brief Struktura zawieraj�ca informacje o koordynatach bloczk�w oraz platformy
* @param x Wsp�rz�dna x bloczku
* @param y Wsp�rz�dna y bloczku
* @param w Szeroko�� bloczku
* @param h Wysoko�� bloczku
* @param state Okre�la stan bloczku(dla platformy jest zawsze ustawiany na jeden przy ka�dej nowej p�tli gry)
*/ 
struct block
{
    int x;
    int y;
    int w;
    int h;
    bool state;
};
/**@brief Struktura zawieraj�ca informacje o w�z�ach drzewa czw�rkowego
* @param x Wsp�rz�dna x �wiartki
* @param y Wsp�rz�dna y �wiartki
* @param w Szeroko�� �wiartki
* @param h Wysoko�� �wiartki
* @param ne Wska�nik na praw� g�rn� �wiartk�
* @param nw Wska�nik na lew� g�rn� �wiartk�
* @param sw Wska�nik na lew� doln� �wiartk�
* @param se Wska�nik na praw� doln� �wiartk�
*/
struct Quad_Tree_Node
{
    int h;
    int w;
    int x;
    int y;
    struct Quad_Tree_Node* ne, * nw, * sw, * se;
};
/** @brief Struktura zawierajaca informacje o pi�ce
* @param x Wsp�rz�dna x pi�ki
* @param y Wsp�rz�dna y pi�ki
* @param r Promie� pi�ki
* @param vx Wektor przesuni�cia w osi X pi�ki
* @param vy Wektor przesuni�cia w osi Y pi�ki
*/
struct Ball
{
    int x;
    int y;
    int r;
    int vx;
    int vy;
};
/**@brief Struktura zawieraj�ca informacje o bonusie
* @param x Wsp�rz�dna x bonusu
* @param y Wsp�rz�dna y bonusu
* @param w Szeroko�� bonusu
* @param h Wysoko�� bonusu
* @param type Typ bonusu
* @param bonus_bitmap Wska�nik na bitmap� reprezentuj�c� odpowiedni bonus
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
