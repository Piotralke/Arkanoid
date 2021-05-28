/// @file bonus.c Plik bonus.c zawiera funkcje odpowiedzialne za przydial bonusu oraz jego utworzenie
#include "bonus.h"
/**
* Funkcja give_bonus() na poczatku ustawia domyœlne wartoœci, które s¹ modyfikowane przez bonusy, a póŸniej zale¿nie od rodzaju bonusu, modyfikuje któr¹œ z nich
* @param New_bonus Struktura przechowujaca dane o bonusie (np.: koordynaty, typ bonusu)
* @param platform struktura reprezentujaca platforme
* @param bonus plik dŸwiêkowy, który jest wywo³ywany przy zebraniu bonusa
*/
void give_bonus(struct bonus* New_bonus, struct block* platform, ALLEGRO_SAMPLE* bonus)
{
    platform->w = 75;
    ball_speed = 6;
    g_t = 0;
    score_multiplier = 1;
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
    case 6:
        if(lifes<3)
            lifes++;
        bonus_active--;
        break;
    case 7:
        score_multiplier = 2;
        bonus_active--;
        break;
    }
    bonus_time = 7000;
    ball_s = ball_speed - 1;
}
/**
* Funkcja make_bonus() tworzy bonus w miejscu bloczka, który zosta³ zbity i zale¿nie od wylosowanego rodzaju zmienia jego typ oraz ³aduje odpowiedni¹ bitmapê
* @param bonus_type rodzaj bonusu (1-Wiêksza platforma, 2-Mniejsza platforma, 3-Szybsza pi³ka, 4-Wolniejsza pi³ka, 5-Przechodzenie, 6-Dodatkowe ¿ycie, 7-Mno¿nik punktów)
* @param block struktura zawieraj¹ca informacje o zbitym bloczku
* @param New_bonus Struktura przechowujaca dane o bonusie (np.: koordynaty, typ bonusu)
*/
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
    case 6:
        New_bonus->bonus_bitmap = add_life;
        New_bonus->type = 6;
        bonus_active += 1;
        break;
    case 7:
        New_bonus->bonus_bitmap = double_points;
        New_bonus->type = 7;
        bonus_active += 1;
        break;
    }
}
/**
* Funkcja bonus() jest wywo³ywana przy zbiciu bloczku i losuje liczbê, od której bêdzie zale¿a³o, czy bonus zostanie utworzony
* @param block struktura zawieraj¹ca informacje o zbitym bloczku
* @param New_bonus Struktura przechowujaca dane o bonusie (np.: koordynaty, typ bonusu)
*/
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
        bonus_type = 1 + rand() % 7;
        make_bonus(bonus_type, block, New_bonus);
    }

}