///@file uninstall.c jest w niej zawarta funkcja, która jest wywo³ywana przy koñczeniu pracy programu i odinstalowywuje ona funkcje z allegro oraz niszczy bitmapy i dŸwiêki
#include "uninstall.h"

/**
* @brief Funkcja uninstall_arkanoid() odinstalowywuje funkcje z allegro oraz niszczy bitmapy i dŸwiêki
*/
void uninstall_arkanoid()
{
    al_uninstall_keyboard();
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer_FPS);
    al_destroy_bitmap(tlo);
    al_destroy_bitmap(menu1);
    al_destroy_bitmap(menu2);
    al_destroy_bitmap(menu3);
    al_destroy_bitmap(menu4);
    al_destroy_bitmap(opcje1);
    al_destroy_bitmap(opcje2);
    al_destroy_bitmap(opcje3);
    al_destroy_bitmap(wyniki);
    al_destroy_bitmap(zycie);
    al_destroy_bitmap(gameover);
    al_destroy_bitmap(youwin);
    al_destroy_bitmap(faster_ball);
    al_destroy_bitmap(slower_ball);
    al_destroy_bitmap(bigger_platform);
    al_destroy_bitmap(smaller_platform);
    al_destroy_bitmap(going_through);
    al_destroy_bitmap(add_life);
    al_destroy_bitmap(double_points);
    al_destroy_sample(ruch);
    al_destroy_sample(klik);
    al_destroy_sample(check);
    al_destroy_sample(hit);
    al_destroy_sample(destroy);
    al_destroy_sample(gameover_m);
    al_destroy_sample(youwin_m);
    al_destroy_sample(music);
    al_destroy_sample(bonus_m);
    al_destroy_sample_instance(musicInstance);
    al_destroy_font(font);
    al_shutdown_primitives_addon();
    al_uninstall_system();
}