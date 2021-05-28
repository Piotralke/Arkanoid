///@file menu.c Plik menu.c zawiera funkcj� pozwalaj�ce porusza� si� po menu oraz zmienia� w nim ustawienia, b�d� rozpocz��/zamkn�� gr�
#include "menu.h"

/**
* @brief Funkcja wynik() jest funkcj�, kt�ra wypisuje najlepsze wyniki na ekran
* @param event_queue Wska�nik na kolejk� zdarze�, kt�re s� interpretowane jako wci�ni�cia klawisza
* @param wyniki Wska�nik na bitmap� �adowan� w menu najlepszych wynik�w
* @param scores Wska�nik na plik zawieraj�cy najlepsze wyniki
* @param font Wska�nik na czcionk� u�ywan� w programie
* @param klik Wska�nik na plik d�wi�kowy, kt�ry wywo�ywany jest w menu podczas klikni�cia w dan� opcj�
*/
void wynik(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* wyniki, FILE* scores, ALLEGRO_SAMPLE* klik, ALLEGRO_FONT* font)
{
    bool working_wyniki = true;
    al_draw_bitmap(wyniki, 0, 0, 0);
    al_flip_display();
    while (working_wyniki)
    {
        read_scores(scores, font);
        al_flip_display();
        ALLEGRO_EVENT ev;
        al_get_next_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ENTER:
                if (sound > 0)
                    al_play_sample(klik, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                working_wyniki = false;
                break;
            }
        }
    }
}

/**
* @brief Funkcja opcje() odpowiada za w��czanie/wy��czanie opcji programu np. d�wi�ku gry
* @param event_queue Wska�nik na kolejk� zdarze�, kt�re s� interpretowane jako wci�ni�cia klawisza
* @param opcje1 Wska�nik na bitmap� �adowan� w menu opcji
* @param opcje2 Wska�nik na bitmap� �adowan� w menu opcji
* @param opcje3 Wska�nik na bitmap� �adowan� w menu opcji
* @param font Wska�nik na czcionk� u�ywan� w programie
* @param ruch Wska�nik na plik d�wi�kowy, kt�ry wywo�ywany jest w menu podczas przechodzenia mi�dzy opcjami
* @param klik Wska�nik na plik d�wi�kowy, kt�ry wywo�ywany jest w menu podczas klikni�cia w dan� opcj�
* @param check Wska�nik na plik d�wi�kowy, kt�ry wywo�ywany jest w menu opcji podczas prze��czenia, kt�rej� z wybranych opcji
* @param musicInstance Wska�nik na odtwarzaln� instancj�, kt�ra zawiera wcze�niej predefiniowany d�wi�k, kt�ry jest muzyk� graj�c� podczas gry. Instancja jest zap�tlona
*/
void opcje(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* opcje1, ALLEGRO_BITMAP* opcje2, ALLEGRO_BITMAP* opcje3, ALLEGRO_FONT* font,
    ALLEGRO_SAMPLE* ruch, ALLEGRO_SAMPLE* klik, ALLEGRO_SAMPLE* check, ALLEGRO_SAMPLE_INSTANCE* musicInstance)
{
    int choice = 1;
    bool working_opcje = true;
    al_draw_bitmap(opcje1, 0, 0, 0);
    al_flip_display();
    while (working_opcje)
    {
        ALLEGRO_EVENT ev;
        al_get_next_event(event_queue, &ev);
        switch (choice)
        {
        case 1:
            al_draw_bitmap(opcje1, 0, 0, 0);
            break;
        case 2:
            al_draw_bitmap(opcje2, 0, 0, 0);
            break;
        case 3:
            al_draw_bitmap(opcje3, 0, 0, 0);
            break;
        }
        if (debug > 0)
            al_draw_text(font, al_map_rgb(0, 0, 0), 634, 485, 3, "X");
        if (sound > 0)
            al_draw_text(font, al_map_rgb(0, 0, 0), 578, 575, 3, "X");
        al_flip_display();
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                if (choice > 1)
                {
                    if (sound > 0)
                        al_play_sample(ruch, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    choice--;
                }
                break;
            case ALLEGRO_KEY_DOWN:
                if (choice < 3)
                {
                    if (sound > 0)
                        al_play_sample(ruch, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    choice++;
                }
                break;
            case ALLEGRO_KEY_ENTER:
                switch (choice)
                {
                case 1:
                    debug *= (-1);
                    if (sound > 0)
                        al_play_sample(check, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    break;
                case 2:
                    if (sound > 0)
                        al_play_sample(check, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    sound *= (-1);
                    if (sound < 0)
                        al_stop_sample_instance(musicInstance);
                    break;
                case 3:
                    if (sound > 0)
                        al_play_sample(klik, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    working_opcje = 0;
                    break;
                }
                break;
            }
        }

    }
}

/**
* @brief Funkcja menu() wy�wietla g��wne menu i odpowiada za przechodzenie po innych funkcjach menu
* @param event_queue Wska�nik na kolejk� zdarze�, kt�re s� interpretowane jako wci�ni�cia klawisza
* @param menu1 Wska�nik na bitmap� �adowan� w g��wnym menu
* @param menu2 Wska�nik na bitmap� �adowan� w g��wnym menu
* @param menu3 Wska�nik na bitmap� �adowan� w g��wnym menu
* @param menu4 Wska�nik na bitmap� �adowan� w g��wnym menu
* @param opcje1 Wska�nik na bitmap� �adowan� w menu opcji
* @param opcje2 Wska�nik na bitmap� �adowan� w menu opcji
* @param opcje3 Wska�nik na bitmap� �adowan� w menu opcji
* @param wyniki Wska�nik na bitmap� �adowan� w menu najlepszych wynik�w
* @param scores Wska�nik na plik zawieraj�cy najlepsze wyniki
* @param font Wska�nik na czcionk� u�ywan� w programie
* @param ruch Wska�nik na plik d�wi�kowy, kt�ry wywo�ywany jest w menu podczas przechodzenia mi�dzy opcjami
* @param klik Wska�nik na plik d�wi�kowy, kt�ry wywo�ywany jest w menu podczas klikni�cia w dan� opcj�
* @param check Wska�nik na plik d�wi�kowy, kt�ry wywo�ywany jest w menu opcji podczas prze��czenia, kt�rej� z wybranych opcji
* @param musicInstance Wska�nik na odtwarzaln� instancj�, kt�ra zawiera wcze�niej predefiniowany d�wi�k, kt�ry jest muzyk� graj�c� podczas gry. Instancja jest zap�tlona
* @return true je�eli u�ytkownik wci�nie przycisk graj
* @return false je�eli u�ytkownik wci�nie przycisk wyj�cie
*/

bool menu(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* menu1, ALLEGRO_BITMAP* menu2, ALLEGRO_BITMAP* menu3, ALLEGRO_BITMAP* menu4,
    ALLEGRO_BITMAP* opcje1, ALLEGRO_BITMAP* opcje2, ALLEGRO_BITMAP* opcje3, ALLEGRO_BITMAP* wyniki, FILE* scores, ALLEGRO_FONT* font,
    ALLEGRO_SAMPLE* ruch, ALLEGRO_SAMPLE* klik, ALLEGRO_SAMPLE* check, ALLEGRO_SAMPLE_INSTANCE* musicInstance)
{

    int choice = 1;
    bool working_menu = true;
    al_draw_bitmap(menu1, 0, 0, 0);
    al_flip_display();
    while (working_menu)
    {
        ALLEGRO_EVENT ev;
        al_get_next_event(event_queue, &ev);
        switch (choice)
        {
        case 1:
            al_draw_bitmap(menu1, 0, 0, 0);
            break;
        case 2:
            al_draw_bitmap(menu2, 0, 0, 0);
            break;
        case 3:
            al_draw_bitmap(menu3, 0, 0, 0);
            break;
        case 4:
            al_draw_bitmap(menu4, 0, 0, 0);
            break;
        }
        if (pause < 0)
            al_draw_text(font, al_map_rgb(255, 0, 0), 300, 330, 0, "PAUSE");

        al_flip_display();
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                if (choice > 1)
                {
                    if (sound > 0)
                        al_play_sample(ruch, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    choice--;
                }
                break;
            case ALLEGRO_KEY_DOWN:
                if (choice < 4)
                {
                    if (sound > 0)
                        al_play_sample(ruch, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    choice++;
                }
                break;
            case ALLEGRO_KEY_ENTER:
                switch (choice)
                {
                case 1:
                    if (sound > 0)
                    {
                        al_play_sample_instance(musicInstance);
                        al_play_sample(klik, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    }
                    working_menu = 0;
                    return true;
                    break;
                case 2:
                    if (sound > 0)
                        al_play_sample(klik, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    opcje(event_queue, opcje1, opcje2, opcje3, font, ruch, klik, check, musicInstance);
                    break;
                case 3:
                    if (sound > 0)
                        al_play_sample(klik, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    wynik(event_queue, wyniki, scores, klik, font);
                    break;
                case 4:
                    if (sound > 0)
                        al_play_sample(klik, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    working_menu = 0;
                    return false;
                    break;

                }
                break;
            }
        }

    }
}
