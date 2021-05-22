#pragma once
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
#define width  800
#define height  900
#define MAX_LVL 5
int ball_move;
int size;
int debug ;
int sound ;
int pause;
int lives ;
int block_counter;
int points ;
int choice_lvl;
struct block
{
    int x;
    int y;
    int w;
    int h;
    bool state;
};

struct Quad_Tree_Node
{
    int h;
    int w;
    int x;
    int y;
    struct Quad_Tree_Node* ne, * nw, * sw, * se;
};
struct Ball
{
    int x;
    int y;
    int r;
    int vx;
    int vy;
};
