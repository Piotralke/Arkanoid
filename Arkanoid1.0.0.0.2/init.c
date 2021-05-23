#include "init.h"

void init_arkanoid()
{
    display = NULL;
    event_queue = NULL;
    timer_FPS = NULL;
    tlo = NULL;
    menu1 = NULL;
    menu2 = NULL;
    menu3 = NULL;
    menu4 = NULL;
    opcje1 = NULL;
    opcje2 = NULL;
    opcje3 = NULL;
    wyniki = NULL;
    zycie = NULL;
    gameover = NULL;
    youwin = NULL;
    faster_ball = NULL;
    slower_ball = NULL;
    bigger_platform = NULL;
    smaller_platform = NULL;
    going_through = NULL;
    ruch = NULL;
    klik = NULL;
    check = NULL;
    hit = NULL;
    destroy = NULL;
    gameover_m = NULL;
    youwin_m = NULL;
    music = NULL;
    musicInstance = NULL;
    font = NULL;
    scores = fopen("scores.txt", "a");
    if (scores == NULL)
    {
        fprintf(stderr, "Blad otwarcia pliku");
        return -1;
    }

    if (!al_init()) {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return -1;
    }
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(7);
    event_queue = al_create_event_queue();
    display = al_create_display(width, height);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }
    font = al_load_ttf_font("font.ttf", 28, ALLEGRO_TTF_MONOCHROME);
    if (!font)
    {
        fprintf(stderr, "Failed to initialize font!\n");
        return -1;
    }
    tlo = al_load_bitmap("BACKGROUND.png");
    if (!tlo) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    menu1 = al_load_bitmap("MENU1.png");
    if (!menu1) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    menu2 = al_load_bitmap("MENU2.png");
    if (!menu2) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    menu3 = al_load_bitmap("MENU3.png");
    if (!menu3) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    menu4 = al_load_bitmap("MENU4.png");
    if (!menu4) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    opcje1 = al_load_bitmap("OPCJE1.png");
    if (!opcje1) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    opcje2 = al_load_bitmap("OPCJE2.png");
    if (!opcje2) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    opcje3 = al_load_bitmap("OPCJE3.png");
    if (!opcje3) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    wyniki = al_load_bitmap("WYNIKI.png");
    if (!wyniki) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    zycie = al_load_bitmap("SERCE.png");
    if (!zycie) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    gameover = al_load_bitmap("GAMEOVER.png");
    if (!gameover) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    youwin = al_load_bitmap("YOUWIN.png");
    if (!youwin) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    faster_ball = al_load_bitmap("FASTER_BALL.png");
    if (!faster_ball) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    slower_ball = al_load_bitmap("SLOWER_BALL.png");
    if (!slower_ball) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    bigger_platform = al_load_bitmap("BIGGER_PLATFORM.png");
    if (!bigger_platform) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    smaller_platform = al_load_bitmap("SMALLER_PLATFORM.png");
    if (!smaller_platform) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    going_through = al_load_bitmap("GOING_THROUGH.png");
    if (!going_through) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }
    ruch = al_load_sample("przechodzenie.ogg");
    if (!ruch) {
        fprintf(stderr, "Failed to load audio!\n");
        return -1;
    }
    klik = al_load_sample("wybor.ogg");
    if (!klik) {
        fprintf(stderr, "Failed to load audio!\n");
        return -1;
    }
    check = al_load_sample("odchaczenie.ogg");
    if (!check) {
        fprintf(stderr, "Failed to load audio!\n");
        return -1;
    }
    hit = al_load_sample("odbicie.ogg");
    if (!hit) {
        fprintf(stderr, "Failed to load audio!\n");
        return -1;
    }
    destroy = al_load_sample("zbicie.ogg");
    if (!destroy) {
        fprintf(stderr, "Failed to load audio!\n");
        return -1;
    }
    gameover_m = al_load_sample("gameover.ogg");
    if (!gameover_m) {
        fprintf(stderr, "Failed to load audio!\n");
        return -1;
    }
    youwin_m = al_load_sample("youwin.ogg");
    if (!youwin_m) {
        fprintf(stderr, "Failed to load audio!\n");
        return -1;
    }
    music = al_load_sample("muzyka.ogg");
    if (!music) {
        fprintf(stderr, "Failed to load audio!\n");
        return -1;
    }
    musicInstance = al_create_sample_instance(music);
    if (!musicInstance) {
        fprintf(stderr, "Failed to create audio!\n");
        return -1;
    }
    al_set_sample_instance_playmode(musicInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musicInstance, al_get_default_mixer());
    timer_FPS = al_create_timer(1.0 / 160);
    if (!timer_FPS) {
        fprintf(stderr, "Failed to create FPS timer!\n");
        return -1;
    }
    al_register_event_source(event_queue, al_get_timer_event_source(timer_FPS));
    al_install_keyboard();
    al_start_timer(timer_FPS);
    al_flip_display();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

}
