#include "physic.h"

void move(struct Ball* ball, struct block platform, ALLEGRO_SAMPLE* hit)
{
    ball->x += ball->vx;
    ball->y -= ball->vy;

    if (ball->x == 790 || ball->x == 10)
    {
        if (sound > 0)
            al_play_sample(hit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        ball->vx = (-1) * ball->vx;
    }

    if (ball->y == 110)
    {
        if (sound > 0)
            al_play_sample(hit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        ball->vy = (-1) * ball->vy;
    }

    if (ball->y == 890) {
        lives--;
        points -= 100;
        ball_move = 0;
        ball->vy = (-1) * ball->vy;
        ball->x = platform.x;
        ball->y = platform.y - platform.h - 5;
    }
}

bool check_collision(struct Ball* ball, struct block* block)
{
    float testX = ball->x;
    float testY = ball->y;

    if (ball->x < block->x - block->w)
        testX = block->x - block->w;
    else if (ball->x > block->x + block->w)
        testX = block->x + block->w;
    if (ball->y < block->y - block->h)
        testY = block->y - block->h;
    else if (ball->y > block->y + block->h)
        testY = block->y + block->h;

    float distX = ball->x - testX;
    float distY = ball->y - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    if (distance <= ball->r && block->state == 1)
    {
        ball->y -= 1;
        ball->vy = (-1) * ball->vy;
        block->state = 0;
        return true;
    }
    return false;
}