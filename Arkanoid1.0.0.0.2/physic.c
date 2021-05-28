///@file physic.c zawiera implementacj� kolizji element�w znajduj�cych si� na planszy oraz funkcje przemieszczaj�ce pi�k� oraz bonusy
#include "physic.h"

/**
* @brief Funkcja move() odpowiada za poruszanie si� pi�ki oraz za odbicie od border�w, a tak�e za ponowne ustawienie pi�ki na platformie gdy u�ytkownik straci �ycie
* @param ball Struktura zawieraj�ca informacje o pi�ce
* @param platform Struktura zawieraj�ca informacje o platformie
* @param hit  Wska�nik na plik d�wi�kowy, kt�ry jest wywo�ywany przy kolizji pi�ki od elementu
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
* @brief Funkcja move_bonus() odpowiada za poruszanie si� bonusu
* @param New_Bonus Struktura zawieraj�ca informacje o bonusie
*/

void move_bonus(struct bonus* New_bonus)
{
    New_bonus->y++;
    if (New_bonus->y > 900)
        bonus_active--;
}

/**
* @brief Funkcja check_block() sprawdza odleg�o�� mi�dzy pi�eczk� i bloczkiem oraz odpowiada za odpowiedni� zmian� wektora poruszania si� pi�ki
* @param ball Struktura zawieraj�ca informacje o pi�ce
* @param block Struktura zawieraj�ca informacje o bloczku
* @return true je�eli funkcja wykry�a kolizj�
* @return false je�eli funkcja nie wykry�a kolizji
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
* @brief Funkcja check_platform() sprawdza odleg�o�� mi�dzy pi�eczk� i bloczkiem oraz odpowiada za odpowiedni� zmian� wektora poruszania si� pi�ki
* @param ball Struktura zawieraj�ca informacje o pi�ce
* @param block Struktura zawieraj�ca informacje o platformie
* @return true je�eli funkcja wykry�a kolizj�
* @return false je�eli funkcja nie wykry�a kolizji
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
* @brief Funkcja check_bonus() sprawdza odleg�o�� mi�dzy platform� i bonusem
* @param block Struktura zawieraj�ca informacje o platformie
* @param bonus Struktura zawieraj�ca informacje o bonusie
* @return true je�eli funkcja wykry�a kolizj�
* @return false je�eli funkcja nie wykry�a kolizji
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