///@file menu.c Plik menu.c zawiera funkcjê pozwalaj¹ce poruszaæ siê po menu oraz zmieniaæ w nim ustawienia, b¹dŸ rozpocz¹æ/zamkn¹æ grê
#include "menu.h"

/**
* @brief Funkcja wynik() jest funkcj¹, która wypisuje najlepsze wyniki na ekran
* @param event_queue WskaŸnik na kolejkê zdarzeñ, które s¹ interpretowane jako wciœniêcia klawisza
* @param wyniki WskaŸnik na bitmapê ³adowan¹ w menu najlepszych wyników
* @param scores WskaŸnik na plik zawieraj¹cy najlepsze wyniki
* @param font WskaŸnik na czcionkê u¿ywan¹ w programie
* @param klik WskaŸnik na plik dŸwiêkowy, który wywo³ywany jest w menu podczas klikniêcia w dan¹ opcjê
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
* @brief Funkcja opcje() odpowiada za w³¹czanie/wy³¹czanie opcji programu np. dŸwiêku gry
* @param event_queue WskaŸnik na kolejkê zdarzeñ, które s¹ interpretowane jako wciœniêcia klawisza
* @param opcje1 WskaŸnik na bitmapê ³adowan¹ w menu opcji
* @param opcje2 WskaŸnik na bitmapê ³adowan¹ w menu opcji
* @param opcje3 WskaŸnik na bitmapê ³adowan¹ w menu opcji
* @param font WskaŸnik na czcionkê u¿ywan¹ w programie
* @param ruch WskaŸnik na plik dŸwiêkowy, który wywo³ywany jest w menu podczas przechodzenia miêdzy opcjami
* @param klik WskaŸnik na plik dŸwiêkowy, który wywo³ywany jest w menu podczas klikniêcia w dan¹ opcjê
* @param check WskaŸnik na plik dŸwiêkowy, który wywo³ywany jest w menu opcji podczas prze³¹czenia, którejœ z wybranych opcji
* @param musicInstance WskaŸnik na odtwarzaln¹ instancjê, która zawiera wczeœniej predefiniowany dŸwiêk, który jest muzyk¹ graj¹c¹ podczas gry. Instancja jest zapêtlona
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
* @brief Funkcja menu() wyœwietla g³ówne menu i odpowiada za przechodzenie po innych funkcjach menu
* @param event_queue WskaŸnik na kolejkê zdarzeñ, które s¹ interpretowane jako wciœniêcia klawisza
* @param menu1 WskaŸnik na bitmapê ³adowan¹ w g³ównym menu
* @param menu2 WskaŸnik na bitmapê ³adowan¹ w g³ównym menu
* @param menu3 WskaŸnik na bitmapê ³adowan¹ w g³ównym menu
* @param menu4 WskaŸnik na bitmapê ³adowan¹ w g³ównym menu
* @param opcje1 WskaŸnik na bitmapê ³adowan¹ w menu opcji
* @param opcje2 WskaŸnik na bitmapê ³adowan¹ w menu opcji
* @param opcje3 WskaŸnik na bitmapê ³adowan¹ w menu opcji
* @param wyniki WskaŸnik na bitmapê ³adowan¹ w menu najlepszych wyników
* @param scores WskaŸnik na plik zawieraj¹cy najlepsze wyniki
* @param font WskaŸnik na czcionkê u¿ywan¹ w programie
* @param ruch WskaŸnik na plik dŸwiêkowy, który wywo³ywany jest w menu podczas przechodzenia miêdzy opcjami
* @param klik WskaŸnik na plik dŸwiêkowy, który wywo³ywany jest w menu podczas klikniêcia w dan¹ opcjê
* @param check WskaŸnik na plik dŸwiêkowy, który wywo³ywany jest w menu opcji podczas prze³¹czenia, którejœ z wybranych opcji
* @param musicInstance WskaŸnik na odtwarzaln¹ instancjê, która zawiera wczeœniej predefiniowany dŸwiêk, który jest muzyk¹ graj¹c¹ podczas gry. Instancja jest zapêtlona
* @return true je¿eli u¿ytkownik wciœnie przycisk graj
* @return false je¿eli u¿ytkownik wciœnie przycisk wyjœcie
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
