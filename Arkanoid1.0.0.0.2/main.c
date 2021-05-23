#include "quadtree.h"
#include "menu.h"
#include "physic.h"
#include "levels.h"
#include "scores.h"
#include "init.h"
#include "uninstall.h"

struct queue_node
{
    int x;
    int y;
    int w;
    int h;
    ALLEGRO_BITMAP* bonus_bitmap;
    struct queue_node* next;
};
struct queue_pointers
{
    struct queue_node* head, * tail;
};
bool enqueue(struct queue_pointers* queue, struct block* block, ALLEGRO_BITMAP* bonus_bitmap)
{
    struct queue_node* new_node = (struct queue_node*)malloc(sizeof(struct queue_node));
    if (new_node != NULL)
    {
        new_node->x = block->x;
        new_node->y = block->y;
        new_node->w = 50;
        new_node->h = 50;
        new_node->bonus_bitmap = bonus_bitmap;
        new_node->next = NULL;
        if (queue->head == NULL)
        {
            queue->head = queue->tail = new_node;
        }
        else
        {
            queue->tail->next = new_node;
            queue->tail = new_node;
        }
        return true;
    }
    return false;
}
bool dequeue(struct queue_pointers* queue)
{
    if (NULL != queue->head)
    {
        struct queue_node* tmp = queue->head->next;
       // free(queue->head);
        queue->head = tmp;
        if (NULL == tmp)
            queue->tail = NULL;
        return true;
    }
    return false;
}
void print_queue(struct queue_node* queue)
{
    al_draw_bitmap(queue->bonus_bitmap, queue->x, queue->y, 0);
    if (queue->next == NULL)
    {
        return;
    }
    print_queue(queue->next);
}

void move_bonus(struct queue_node* queue)
{
    if (queue != NULL)
    {
        queue->y += 1;
        if (queue->y > 900)
        {
            bonus_active--;
            if(dequeue(&queue));
                move_bonus(queue);
            
        }
        if(queue!=NULL)
            move_bonus(queue->next);
    }
    else
        return;
}

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
    ALLEGRO_BITMAP* gameover, ALLEGRO_BITMAP* youwin, FILE* scores, ALLEGRO_FONT* font,ALLEGRO_SAMPLE* ruch,ALLEGRO_SAMPLE* klik,ALLEGRO_SAMPLE* check , 
    ALLEGRO_SAMPLE* hit ,ALLEGRO_SAMPLE* destroy,ALLEGRO_SAMPLE* gameover_m, ALLEGRO_SAMPLE* youwin_m, ALLEGRO_SAMPLE_INSTANCE* musicInstance, struct queue_pointers* queue)
{
    init_level1(array);

    int bonus_time = 0;
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
            Sleep(2000);
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
               //init_level2(array);
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
        if (i == ball_speed && ball_move == 1) {
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
                i = ball_speed-1;
                break;
            case ALLEGRO_KEY_ESCAPE:
                working = false;
                pause *= (-1);
                working = menu(event_queue, menu1, menu2, menu3, menu4, opcje1, opcje2, opcje3, wyniki, scores, font,ruch, klik, check,musicInstance);
                pause *= (-1);
                break;
            }
        }
        update(&root, &New_Ball, &Platform, array, hit, destroy, queue);
        if (bonus_active > 0)
        {
            move_bonus(queue->head);
            if (bonus_active > 0)
            {
                print_queue(queue->head);
                al_flip_display();
            }

            //if (bonus_time == 1000)
            //{
            //    bonus_time = 0;
            //    bonus_active = (-1);
            //}
        }
        i++;
        if(bonus_active>0)
            bonus_time++;
    }
}

void make_bonus(int bonus_type, struct block* block, struct queue_pointers* queue)
{

    switch (bonus_type)
    {
    case 1:
        enqueue(queue, block, faster_ball);
        printf("1.");
        bonus_active += 1;
        break;
    case 2:
        enqueue(queue, block, slower_ball);
        printf("2.");
        bonus_active += 1;
        break;
    case 3:
        enqueue(queue, block, bigger_platform);
        printf("3.");
        bonus_active += 1;
        break;
    case 4:
        enqueue(queue, block, smaller_platform);
        printf("4.");
        bonus_active += 1;
        break;
    case 5:
        enqueue(queue, block, going_through);
        printf("5.");
        bonus_active += 1;
        break;
    }
}

void bonus(struct block* block,struct queue_pointers* queue)
{
    int chance = 0;
    srand(time(NULL));
    chance = rand() % 100;
    if (chance < 5)
        return;
    else
    {
        int bonus_type = 0;
        bonus_type = 1 + rand() % 4;
        make_bonus(bonus_type, block, queue);
    }

}

int main(int argc, char* argv[])
{
    struct block Platform = { (width / 2), height - 30,75,10, 1 };
    struct Ball New_Ball = { Platform.x , Platform.y - Platform.h - 5, 10, 1, 1 };
    struct queue_pointers queue = { NULL, NULL };
    init_arkanoid();
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
        working = menu(event_queue, menu1, menu2, menu3, menu4, opcje1, opcje2, opcje3, wyniki, scores, font, ruch, klik, check, musicInstance);
        game(working, array, root, Platform, New_Ball,
            event_queue, menu1, menu2, menu3, menu4,
            opcje1, opcje2, opcje3, wyniki, tlo, zycie, gameover, youwin, scores, font,
            ruch, klik, check, hit, destroy, gameover_m, youwin_m, musicInstance, &queue);
        al_stop_sample_instance(musicInstance);
        free_ptr(array);
        save_score(scores);
    } while (working);
    uninstall_arkanoid();
    return 0;
}