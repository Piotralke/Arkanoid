#include "bonus.h"

void move_bonus(struct bonus* New_bonus)
{
    New_bonus->y++;
    if (New_bonus->y > 900)
        bonus_active--;
}

void give_bonus(struct bonus* New_bonus, struct block* platform, ALLEGRO_SAMPLE* bonus)
{
    platform->w = 75;
    ball_speed = 6;
    g_t = 0;
    if(sound>0)
        al_play_sample(bonus, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    switch (New_bonus->type)
    {
    case 1:
        platform->w += 25;
        bonus_active--;
        break;
    case 2:
        platform->w -= 25;
        bonus_active--;
        break;
    case 3:
        ball_speed -= 2;
        bonus_active--;
        break;
    case 4:
        ball_speed += 2;
        bonus_active--;
        break;
    case 5:
        g_t++;
        bonus_active--;
        break;
    }
    bonus_time = 7000;
    ball_s = ball_speed - 1;
}

void make_bonus(int bonus_type, struct block* block, struct bonus* New_bonus)
{
    New_bonus->x = block->x;
    New_bonus->y = block->y;
    New_bonus->w = 25;
    New_bonus->h = 25;
    switch (bonus_type)
    {
    case 1:
        New_bonus->bonus_bitmap = bigger_platform;
        New_bonus->type = 1;
        bonus_active += 1;
        break;
    case 2:
        New_bonus->bonus_bitmap = smaller_platform;
        New_bonus->type = 2;
        bonus_active += 1;
        break;
    case 3:
        New_bonus->bonus_bitmap = faster_ball;
        New_bonus->type = 3;
        bonus_active += 1;
        break;
    case 4:
        New_bonus->bonus_bitmap = slower_ball;
        New_bonus->type = 4;
        bonus_active += 1;
        break;
    case 5:
        New_bonus->bonus_bitmap = going_through;
        New_bonus->type = 5;
        bonus_active += 1;
        break;
    }
}

void bonus(struct block* block, struct bonus* New_bonus)
{
    int chance = 0;
    srand(time(NULL));
    chance = rand() % 100;
    if (chance < 70)
        return;
    else
    {
        int bonus_type = 0;
        bonus_type = 1 + rand() % 5;
        make_bonus(bonus_type, block, New_bonus);
    }

}