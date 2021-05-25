#include "game.h"

void wait_for_keypress()
{
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_EVENT event;

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    do
        al_wait_for_event(event_queue, &event);
    while (event.type != ALLEGRO_EVENT_KEY_DOWN);

    al_destroy_event_queue(event_queue);
}

void game(bool working, struct block** array, struct Quad_Tree_Node* root, struct block Platform, struct Ball New_Ball, struct bonus New_bonus,
    ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* menu1, ALLEGRO_BITMAP* menu2, ALLEGRO_BITMAP* menu3, ALLEGRO_BITMAP* menu4,
    ALLEGRO_BITMAP* opcje1, ALLEGRO_BITMAP* opcje2, ALLEGRO_BITMAP* opcje3, ALLEGRO_BITMAP* wyniki, ALLEGRO_BITMAP* tlo, ALLEGRO_BITMAP* zycie,
    ALLEGRO_BITMAP* gameover, ALLEGRO_BITMAP* youwin, FILE* scores, ALLEGRO_FONT* font, ALLEGRO_SAMPLE* ruch, ALLEGRO_SAMPLE* klik, ALLEGRO_SAMPLE* check,
    ALLEGRO_SAMPLE* hit, ALLEGRO_SAMPLE* destroy, ALLEGRO_SAMPLE* gameover_m, ALLEGRO_SAMPLE* youwin_m, ALLEGRO_SAMPLE_INSTANCE* musicInstance)
{
    while (working)
    {
        
        if (lives == 0)
        {
            ball_move = 0;
            al_stop_sample_instance(musicInstance);
            if (sound > 0)
                al_play_sample(gameover_m, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            al_draw_bitmap(gameover, 200, 300, 0);
            al_flip_display();
            Sleep(2000);
            wait_for_keypress();
            working = false;
        }
        if (block_counter == 0 && choice_lvl <= 5)
        {
            choice_lvl++;
            ball_move = 0;
            New_Ball.vy = (-1) * New_Ball.vy;
            New_Ball.x = Platform.x;
            New_Ball.y = Platform.y - Platform.h - 5;
            switch (choice_lvl)
            {
            case 1:
                init_level1(array);
                break;
            case 2:
                init_level2(array);
                break;
            case 3:
                init_level3(array);
                break;
            case 4:
                init_level4(array);
                break;
            case 5:
                ball_move = 0;
                al_stop_sample_instance(musicInstance);
                if (sound > 0)
                    al_play_sample(youwin_m, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                al_draw_bitmap(youwin, 200, 300, 0);
                al_flip_display();
                Sleep(3000);
                wait_for_keypress();
                working = false;
                points += lives * 100;
                break;
            }
        }
        Platform.state = 1;
        al_draw_textf(font, al_map_rgb(255, 255, 255), 30, 30, 0, "SCORE: %d", points);
        for (int j = 0; j < lives;j++)
            al_draw_scaled_bitmap(zycie, 0, 0, 570, 570, 700 - j * 100, 10, 70, 70, 0);
        al_draw_rectangle(1, height * 1.0 / 9.0, width - 1, height - 1, al_map_rgb(150, 150, 150), 4);
        al_draw_filled_rectangle(Platform.x - Platform.w, Platform.y - Platform.h, Platform.x + Platform.w, Platform.y + Platform.h, al_map_rgb(200, 200, 200));
        al_draw_filled_circle(New_Ball.x, New_Ball.y, New_Ball.r, al_map_rgb(0, 255, 255));
        al_flip_display();
        al_draw_bitmap(tlo, 0, 0, 0);
        switch (choice_lvl)
        {
        case 1:
            draw_block1(array);
            break;
        case 2:
            draw_block2(array);
            break;
        case 3:
            draw_block3(array);
            break;
        case 4:
            draw_block4(array);
            break;
        }
        ALLEGRO_EVENT ev;
        if (ball_s == ball_speed && ball_move == 1) {
            move(&New_Ball, Platform, hit);
            ball_s = 0;
        }
        al_get_next_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_CHAR)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                if (Platform.x - Platform.w > 0 && ball_move == 0)
                {
                    Platform.x -= 5;
                    New_Ball.x -= 5;
                    New_Ball.vx = -1;
                }
                else if (Platform.x - Platform.w > 0)
                {
                    Platform.x -= 5;
                }
                break;
            case ALLEGRO_KEY_RIGHT:
                if (Platform.x + Platform.w < width && ball_move == 0)
                {
                    Platform.x += 5;
                    New_Ball.x += 5;
                    New_Ball.vx = 1;
                }
                else if (Platform.x + Platform.w < width)
                {
                    Platform.x += 5;
                }
                break;
            case ALLEGRO_KEY_SPACE:
                ball_move = 1;
                ball_s = ball_speed - 1;
                break;
            case ALLEGRO_KEY_ESCAPE:
                working = false;
                pause *= (-1);
                working = menu(event_queue, menu1, menu2, menu3, menu4, opcje1, opcje2, opcje3, wyniki, scores, font, ruch, klik, check, musicInstance);
                pause *= (-1);
                break;
            }
        }
        update(&root, &New_Ball, &Platform, &New_bonus, array, hit, destroy);
        if (bonus_active > 0)
        {
            if (New_bonus.bonus_bitmap != NULL)
                al_draw_bitmap(New_bonus.bonus_bitmap, New_bonus.x-New_bonus.w, New_bonus.y-New_bonus.h, 0);
            if (bonus_speed == 10)
            {
                move_bonus(&New_bonus);
                bonus_speed = 0;
            }
            if (check_bonus(&Platform, &New_bonus))
                give_bonus(&New_bonus, &Platform, bonus_m);
        }
        if (bonus_time > 0)
        {
            bonus_time--;
        }
        if (bonus_time == 1)
        {
            Platform.w = 75;
            ball_speed = 6;
            g_t = 0;
            ball_s = ball_speed - 1;
        }
        bonus_speed++;
        ball_s++;
    }
}
