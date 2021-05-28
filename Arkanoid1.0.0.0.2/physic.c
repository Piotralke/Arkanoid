///@file physic.c zawiera implementacjê kolizji elementów znajduj¹cych siê na planszy oraz funkcje przemieszczaj¹ce pi³kê oraz bonusy
#include "physic.h"

/**
* @brief Funkcja move() odpowiada za poruszanie siê pi³ki oraz za odbicie od borderów, a tak¿e za ponowne ustawienie pi³ki na platformie gdy u¿ytkownik straci ¿ycie
* @param ball Struktura zawieraj¹ca informacje o pi³ce
* @param platform Struktura zawieraj¹ca informacje o platformie
* @param hit  WskaŸnik na plik dŸwiêkowy, który jest wywo³ywany przy kolizji pi³ki od elementu
*/

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
        lifes--;
        points -= 100;
        ball_move = 0;
        ball->vy = (-1) * ball->vy;
        ball->x = platform.x;
        ball->y = platform.y - platform.h - 5;
    }
}

/**
* @brief Funkcja move_bonus() odpowiada za poruszanie siê bonusu
* @param New_Bonus Struktura zawieraj¹ca informacje o bonusie
*/

void move_bonus(struct bonus* New_bonus)
{
    New_bonus->y++;
    if (New_bonus->y > 900)
        bonus_active--;
}

/**
* @brief Funkcja check_block() sprawdza odleg³oœæ miêdzy pi³eczk¹ i bloczkiem oraz odpowiada za odpowiedni¹ zmianê wektora poruszania siê pi³ki
* @param ball Struktura zawieraj¹ca informacje o pi³ce
* @param block Struktura zawieraj¹ca informacje o bloczku
* @return true je¿eli funkcja wykry³a kolizjê
* @return false je¿eli funkcja nie wykry³a kolizji
*/

bool check_block(struct Ball* ball, struct block* block)
{
    float testX = ball->x;
    float testY = ball->y;
    int odbicie = 0;

    if (ball->x < block->x - block->w) {
        testX = block->x - block->w;
        odbicie = 1;
    }

    else if (ball->x > block->x + block->w) {
        testX = block->x + block->w;
        odbicie = 1;
    }

    if (ball->y < block->y - block->h) {
        testY = block->y - block->h;
        odbicie = 2;
    }

    else if (ball->y > block->y + block->h) {
        testY = block->y + block->h;
        odbicie = 2;
    }


    float distX = ball->x - testX;
    float distY = ball->y - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    if (distance <= ball->r && block->state == 1)
    {
        if (g_t <= 0)
        {
            ball->y -= 1;
            if (odbicie == 1)
                ball->vx = (-1) * ball->vx;
            if (odbicie == 2)
                ball->vy = (-1) * ball->vy;
        }
        block->state = 0;
        return true;
    }
    return false;
}

/**
* @brief Funkcja check_platform() sprawdza odleg³oœæ miêdzy pi³eczk¹ i bloczkiem oraz odpowiada za odpowiedni¹ zmianê wektora poruszania siê pi³ki
* @param ball Struktura zawieraj¹ca informacje o pi³ce
* @param block Struktura zawieraj¹ca informacje o platformie
* @return true je¿eli funkcja wykry³a kolizjê
* @return false je¿eli funkcja nie wykry³a kolizji
*/

bool check_platform(struct Ball* ball, struct block* block)
{
    float testX = ball->x;
    float testY = ball->y;
    int odbicie = 0;

    if (ball->x < block->x - block->w) {
        testX = block->x - block->w;
        odbicie = 1;
    }

    else if (ball->x > block->x + block->w) {
        testX = block->x + block->w;
        odbicie = 1;
    }

    if (ball->y < block->y - block->h) {
        testY = block->y - block->h;
        odbicie = 2;
    }

    else if (ball->y > block->y + block->h) {
        testY = block->y + block->h;
        odbicie = 2;
    }


    float distX = ball->x - testX;
    float distY = ball->y - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    if (distance <= ball->r && block->state == 1)
    {
        ball->y -= 1;
        if (odbicie == 1)
            ball->vx = (-1) * ball->vx;
        if (odbicie == 2)
            ball->vy = (-1) * ball->vy;
        block->state = 0;
        return true;
    }
    return false;
}

/**
* @brief Funkcja check_bonus() sprawdza odleg³oœæ miêdzy platform¹ i bonusem
* @param block Struktura zawieraj¹ca informacje o platformie
* @param bonus Struktura zawieraj¹ca informacje o bonusie
* @return true je¿eli funkcja wykry³a kolizjê
* @return false je¿eli funkcja nie wykry³a kolizji
*/

bool check_bonus(struct block* block, struct bonus* bonus)
{
    float testX = bonus->x;
    float testY = bonus->y;
    int odbicie = 0;

    if (bonus->x < block->x - block->w) {
        testX = block->x - block->w;
        odbicie = 1;
    }

    else if (bonus->x > block->x + block->w) {
        testX = block->x + block->w;
        odbicie = 1;
    }

    if (bonus->y < block->y - block->h) {
        testY = block->y - block->h;
        odbicie = 2;
    }

    else if (bonus->y > block->y + block->h) {
        testY = block->y + block->h;
        odbicie = 2;
    }


    float distX = bonus->x - testX;
    float distY = bonus->y - testY;
    float distance = sqrt((distX * distX) + (distY * distY));
    if (distance <= 0.5 * (bonus->h))
        return true;
    return false;
}