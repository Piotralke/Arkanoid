#include "quadtree.h"
#include "menu.h"
#include "physic.h"
#include "levels.h"

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

void game(bool working, struct block** array,struct Quad_Tree_Node* root, struct block Platform, struct Ball New_Ball, 
    ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* menu1, ALLEGRO_BITMAP* menu2, ALLEGRO_BITMAP* menu3, ALLEGRO_BITMAP* menu4,
    ALLEGRO_BITMAP* opcje1, ALLEGRO_BITMAP* opcje2, ALLEGRO_BITMAP* opcje3, ALLEGRO_BITMAP* wyniki, ALLEGRO_BITMAP* tlo, ALLEGRO_BITMAP* zycie,
    ALLEGRO_BITMAP* gameover, FILE* scores, ALLEGRO_FONT* font,ALLEGRO_SAMPLE* ruch,ALLEGRO_SAMPLE* klik,ALLEGRO_SAMPLE* check , 
    ALLEGRO_SAMPLE* hit ,ALLEGRO_SAMPLE* destroy,ALLEGRO_SAMPLE* gameover_m, ALLEGRO_SAMPLE_INSTANCE* musicInstance)
{
    init_level1(array);

    int i = 0;
    while (working)
    {
        if (lives == 0)
        {
            ball_move = 0;
            al_stop_sample_instance(musicInstance);
            if (sound > 0)
                al_play_sample(gameover_m, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            al_draw_bitmap(gameover,200,300,0);
            al_flip_display();
            wait_for_keypress();
            working = false;
        }
        if (block_counter == 0 && choice_lvl <=5)
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
               //init_level3(array);
               break;
           case 4:
               //init_level4(array);
               break;
           case 5:
               ball_move = 0;
               al_stop_sample_instance(musicInstance);
               if (sound > 0)
                   al_play_sample(gameover_m, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
               al_draw_bitmap(gameover, 200, 300, 0);
               al_flip_display();
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
            draw_block1(array, size);
            break;
        case 2:
            draw_block2(array, size);
            break;
        case 3:
            draw_block3(array, size);
            break;
        case 4:
            draw_block4(array, size);
            break;
        }
        ALLEGRO_EVENT ev;
        if (i == 7 && ball_move == 1) {
            move(&New_Ball, Platform, hit);
            i = 0;
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
                i = 6;
                break;
            case ALLEGRO_KEY_ESCAPE:
                working = false;
                working = menu(event_queue, menu1, menu2, menu3, menu4, opcje1, opcje2, opcje3, wyniki, scores, font,ruch, klik, check,musicInstance);
                break;
            }
        }
        update(&root, &New_Ball, &Platform, array, hit, destroy);
        i++;
        
    }
}

void swap(int* first, int* second)
{
    int t;
    t = *first;
    *first = *second;
    *second = *first;
}

void bubble_sort(int array[])
{
    int i, j;
    for (i = 0; i < 6; i++)
        for (j = 6 - 1; j > i; j--)
            if (array[j - 1] > array[j])
                swap(&array[j - 1], &array[j]);
}


/*void sort_scores()
{
    int i=0, size=5, liczba;
    int scores_table[6];
    FILE* scores;
    scores = fopen("scores.txt", "r");
 
    while (fscanf(scores, "%d", &liczba) != EOF && i<7)
    {
        scores_table[i] = liczba;
        i++;
    }
    fclose(scores);

    bubble_sort(scores_table);
 
    scores = fopen("scores.txt", "w");
    if (scores == NULL)
    {
        fprintf(stderr, "Blad otwarcia pliku");
        return -1;
    }
    for (int i = 0; i < 5;i++)
    {
        fprintf(scores, "%d\n", scores_table[i]);
    }
    fclose(scores);
}*/
void sort_scores(FILE* scores)
{
    int* highscore_table = NULL;
    fclose(scores);
    int number, counter = 0;
    scores = fopen("scores.txt", "r");
    if (scores)
    {
        while (!feof(scores))
        {
            fscanf(scores, "%d", &number);
            counter++;
            if (!feof(scores))
            {
                highscore_table = realloc(highscore_table, sizeof(int) * counter);
                highscore_table[counter - 1] = number;
            }
        }
        fclose(scores);
    }
    int i = 0, tmp;
    while (i < counter - 1)
    {
        int j = 0;
        while (j < counter - i - 1)
        {
            if (highscore_table[j] < highscore_table[j + 1])
            {
                tmp = highscore_table[j];
                highscore_table[j] = highscore_table[j + 1];
                highscore_table[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
    scores = fopen("scores.txt", "w");
    if (scores)
    {
        int m = 0;
        while (m < 5)
        {
            fprintf(scores, "%d\n", highscore_table[m]);
            m++;
            counter--;
        }
        fclose(scores);
    }
}
void save_score(FILE* scores)
{
    fprintf(scores, "%d\n", points);
    sort_scores(scores);
}
int main(int argc, char* argv[])
{   
    bool working;
    
    struct block Platform = { (width / 2), height - 30,75,10, 1 };
    struct Ball New_Ball = { Platform.x , Platform.y - Platform.h - 5, 10, 1, 1 };
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer_FPS = NULL;
    ALLEGRO_BITMAP* tlo = NULL;
    ALLEGRO_BITMAP* menu1 = NULL;
    ALLEGRO_BITMAP* menu2 = NULL;
    ALLEGRO_BITMAP* menu3 = NULL;
    ALLEGRO_BITMAP* menu4 = NULL;
    ALLEGRO_BITMAP* opcje1 = NULL;
    ALLEGRO_BITMAP* opcje2 = NULL;
    ALLEGRO_BITMAP* opcje3 = NULL;
    ALLEGRO_BITMAP* wyniki = NULL;
    ALLEGRO_BITMAP* zycie = NULL;
    ALLEGRO_BITMAP* gameover = NULL;
    ALLEGRO_SAMPLE* ruch = NULL;
    ALLEGRO_SAMPLE* klik = NULL;
    ALLEGRO_SAMPLE* check = NULL;
    ALLEGRO_SAMPLE* hit = NULL;
    ALLEGRO_SAMPLE* destroy = NULL;
    ALLEGRO_SAMPLE* gameover_m = NULL;
    ALLEGRO_SAMPLE* music = NULL;
    ALLEGRO_SAMPLE_INSTANCE* musicInstance = NULL;
    ALLEGRO_FONT* font = NULL;
    FILE* scores;
    scores = fopen("scores.txt", "a" );
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

    do
    {
        lives = 3;
        points = 0;
        ball_move = 0;
        choice_lvl = 1;
        struct block** array = (struct block**)calloc(size, sizeof(struct block*));
        for (int a = 0; a < size; a++)
            array[a] = (struct block*)calloc(size, sizeof(struct block));
        if (!array)
        {
            fprintf(stderr, "Blad zalokowania pamieci");
            free_ptr(array);
            return -1;
        }
        struct Quad_Tree_Node* root = NULL;
        root = init_node(root, 0);
        working = menu(event_queue, menu1, menu2, menu3, menu4, opcje1, opcje2, opcje3, wyniki, scores, font, ruch, klik, check,musicInstance);
        game(working, array, root, Platform, New_Ball,
            event_queue, menu1, menu2, menu3, menu4,
            opcje1, opcje2, opcje3, wyniki, tlo,zycie,gameover, scores, font,
            ruch, klik, check, hit, destroy, gameover_m, musicInstance);
        al_stop_sample_instance(musicInstance);
        free_ptr(array);
        save_score(scores);
    }while (working);

    al_uninstall_keyboard();
    al_destroy_display(display);
    return 0;
}