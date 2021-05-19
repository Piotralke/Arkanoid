#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define width  800
#define height  900
#define MAX_LVL 5
int ball_move = 0;
int size = 8;
int debug = -1;
int sound = -1;
int lives = 3;
int points = 0;
struct block
{
    int x;
    int y;
    int w;
    int h;
    bool state;
};

struct Quad_Tree_Node
{
    int h;
    int w;
    int x;
    int y;
    struct Quad_Tree_Node* ne, * nw, * sw, * se;
};
struct Ball
{
    int x;
    int y;
    int r;
    int vx;
    int vy;
};

void init_array(struct block** array)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <  size; j++)
        {
            array[i][j].x = 50 + j*100;
            array[i][j].y = 125 + i*50;
            array[i][j].h = 25;
            array[i][j].w = 50;
            array[i][j].state = 1;
        }
    }
}

void draw_block(struct block** array)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <  size; j++)
        {
            if (array[i][j].state == 1)
            {
                al_draw_filled_rectangle(array[i][j].x - array[i][j].w,
                    array[i][j].y - array[i][j].h,
                    array[i][j].x + array[i][j].w,
                    array[i][j].y + array[i][j].h,
                    al_map_rgb(255 - i*15, i*15, 0));
                al_draw_rectangle(array[i][j].x - array[i][j].w,
                    array[i][j].y - array[i][j].h,
                    array[i][j].x + array[i][j].w,
                    array[i][j].y + array[i][j].h,
                    al_map_rgb(0, 0, 0), 2);
            }
            
        }
    }
}

struct Quad_Tree_Node* init_node(struct Quad_Tree_Node* root, int choice)
{
    if (choice == 0)
    {
        root = (struct Quad_Tree_Node*)malloc(sizeof(struct Quad_Tree_Node));
        if (root) {
            root->x = width / 2;
            root->y = height * (5.0 / 9.0);
            root->h = height * (8.0 / 9.0) / 2.0;
            root->w = width / 2;
            root->ne = NULL;
            root->nw = NULL;
            root->sw = NULL;
            root->se = NULL;
        }
        return root;
    }
    else if (choice == 1) {   //ne
        struct Quad_Tree_Node* node = (struct Quad_Tree_Node*)malloc(sizeof(struct Quad_Tree_Node));
        if (node) {
            node->x = root->x + root->w / 2.0;
            node->y = root->y - root->h / 2.0;
            node->h = root->h / 2.0;
            node->w = root->w / 2.0;
            node->ne = NULL;
            node->nw = NULL;
            node->sw = NULL;
            node->se = NULL;
        }
        return node;
    }
    else if (choice == 2) { //nw
        struct Quad_Tree_Node* node = (struct Quad_Tree_Node*)malloc(sizeof(struct Quad_Tree_Node));
        if (node) {
            node->x = root->x - root->w / 2.0;
            node->y = root->y - root->h / 2.0;
            node->h = root->h / 2;
            node->w = root->w / 2;
            node->ne = NULL;
            node->nw = NULL;
            node->sw = NULL;
            node->se = NULL;
        }
        return node;
    }
    else if (choice == 3) { //sw
        struct Quad_Tree_Node* node = (struct Quad_Tree_Node*)malloc(sizeof(struct Quad_Tree_Node));
        if (node) {
            node->x = root->x - root->w / 2.0;
            node->y = root->y + root->h / 2.0;
            node->h = root->h / 2;
            node->w = root->w / 2;
            node->ne = NULL;
            node->nw = NULL;
            node->sw = NULL;
            node->se = NULL;
        }
        return node;
    }
    else if (choice == 4) { //se
        struct Quad_Tree_Node* node = (struct Quad_Tree_Node*)malloc(sizeof(struct Quad_Tree_Node));
        if (node) {
            node->x = root->x + root->w / 2.0;
            node->y = root->y + root->h / 2.0;
            node->h = root->h / 2;
            node->w = root->w / 2;
            node->ne = NULL;
            node->nw = NULL;
            node->sw = NULL;
            node->se = NULL;
        }
        return node;
    }
    return root;
}

void move(struct Ball* ball, struct block platform)
{
    ball->x += ball->vx;
    ball->y -= ball->vy;

    if (ball->x == 790 || ball->x == 10)
        ball->vx = (-1) * ball->vx;
    if (ball->y == 110)
        ball->vy = (-1) * ball->vy;
    if (ball->y == 890) {
        lives--;
        ball_move = 0;
        ball->vy = (-1) * ball->vy;
        ball->x = platform.x;
        ball->y = platform.y - platform.h - 5;
    }
}

void draw_node(struct Quad_Tree_Node* node)
{
    al_draw_rectangle(node->x, node->y - node->h, node->x + node->w, node->y, al_map_rgb(255, 255, 255), 2); //ne
    al_draw_rectangle(node->x - node->w, node->y - node->h, node->x, node->y, al_map_rgb(255, 255, 255), 2); //nw
    al_draw_rectangle(node->x - node->w, node->y, node->x, node->y + node->h, al_map_rgb(255, 255, 255), 2); //sw
    al_draw_rectangle(node->x, node->y, node->x + node->w, node->y + node->h, al_map_rgb(255, 255, 255), 2); //se
}

void draw_range(struct Ball* ball)
{
    al_draw_rectangle(ball->x - ball->r - 25, ball->y - ball->r - 25, ball->x + ball->r + 25, ball->y + ball->r + 25, al_map_rgb(0, 255, 0), 1);
}

bool contain(struct Quad_Tree_Node* node, struct Ball* ball)
{
    if (ball->x - ball->r - 25 >= node->x - node->w &&
        ball->x - ball->r - 25 <= node->x + node->w &&
        ball->y - ball->r - 25 >= node->y - node->h &&
        ball->y - ball->r - 25 <= node->y + node->h ||
        ball->x + ball->r + 25 <= node->x + node->w &&
        ball->x + ball->r + 25 >= node->x - node->w &&
        ball->y + ball->r + 25 <= node->y + node->h &&
        ball->y + ball->r + 25 >= node->y - node->h ||
        ball->x - ball->r - 25 >= node->x - node->w &&
        ball->x - ball->r - 25 <= node->x + node->w &&
        ball->y + ball->r + 25 >= node->y - node->h &&
        ball->y + ball->r + 25 <= node->y + node->h ||
        ball->x + ball->r + 25 <= node->x + node->w &&
        ball->x + ball->r + 25 >= node->x - node->w &&
        ball->y - ball->r - 25 >= node->y - node->h &&
        ball->y - ball->r - 25 <= node->y + node->h)
        return true;
    else
        return false;
}

bool contain_platform(struct Quad_Tree_Node* node, struct block* block)
{
    if (block->x - block->w > node->x - node->w &&
        block->x - block->w < node->x + node->w &&
        block->y - block->h > node->y - node->h &&
        block->y - block->h < node->y + node->h ||
        block->x + block->w < node->x + node->w &&
        block->x + block->w > node->x - node->w &&
        block->y + block->h < node->y + node->h &&
        block->y + block->h > node->y - node->h ||
        block->x - block->w > node->x - node->w &&
        block->x - block->w < node->x + node->w &&
        block->y + block->h > node->y - node->h &&
        block->y + block->h < node->y + node->h ||
        block->x + block->w < node->x + node->w &&
        block->x + block->w > node->x - node->w &&
        block->y - block->h > node->y - node->h &&
        block->y - block->h < node->y + node->h ||
        block->y > node->y - node->h &&
        block->y < node->y + node->h &&
        block->x > node->x - node->w &&
        block->x < node->x + node->w ||
        block->y > node->y - node->h &&
        block->y < node->y + node->h &&
        block->x + 0.5*block->w > node->x - node->w &&
        block->x + 0.5 * block->w < node->x + node->w ||
        block->y > node->y - node->h &&
        block->y < node->y + node->h &&
        block->x - 0.5 * block->w > node->x - node->w &&
        block->x - 0.5 * block->w < node->x + node->w)
        return true;
    else
        return false;
}

bool contain_block(struct Quad_Tree_Node* node, struct block* block)
{
    if (block->state == 1)
    {

        if (block->x - block->w > node->x - node->w &&
            block->x - block->w < node->x + node->w &&
            block->y - block->h > node->y - node->h &&
            block->y - block->h < node->y + node->h ||
            block->x + block->w < node->x + node->w &&
            block->x + block->w > node->x - node->w &&
            block->y + block->h < node->y + node->h &&
            block->y + block->h > node->y - node->h ||
            block->x - block->w > node->x - node->w &&
            block->x - block->w < node->x + node->w &&
            block->y + block->h > node->y - node->h &&
            block->y + block->h < node->y + node->h ||
            block->x + block->w < node->x + node->w &&
            block->x + block->w > node->x - node->w &&
            block->y - block->h > node->y - node->h &&
            block->y - block->h < node->y + node->h ||
            block->y >= node->y - node->h &&
            block->y <= node->y + node->h &&
            block->x >= node->x - node->w &&
            block->x <= node->x + node->w )
            return true;
        else
            return false;
    }
    else
        return false;
}


bool check_collision(struct Ball* ball, struct block* block)   
{
    float testX = ball->x;
    float testY = ball->y;

    if (ball->x < block->x - block->w)
        testX = block->x - block->w;
    else if (ball->x > block->x + block->w)
        testX = block->x + block->w;
    if (ball->y < block->y - block->h)
        testY = block->y - block->h;
    else if (ball->y > block->y + block->h)
        testY = block->y + block->h;

    float distX = ball->x - testX;
    float distY = ball->y - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    if (distance <= ball->r && block->state == 1)
    {
        ball->y -= 1;
        ball->vy = (-1)*ball->vy;
        block->state = 0;
        return true;
    }
    return false;
}

void free_node(struct Quad_Tree_Node* node)
{
    if (node != NULL)
    {
        free_node(node->ne);
        free_node(node->nw);
        free_node(node->sw);
        free_node(node->se);
    }
    free(node);
}

void free_ptr(struct block** array)
{
    for (int i = 0; i < size; i++)
    {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
    array = NULL;
}

void draw_outline(struct Quad_Tree_Node* node)
{
    al_draw_rectangle(node->x - node->w, node->y - node->h, node->x + node->w, node->y + node->h, al_map_rgb(255, 0, 0), 2);
}

void subdivide(struct Quad_Tree_Node* node, int levels, struct Ball* ball, struct block* platform, struct block** block)
{
    if (node && levels > 0 && contain(node, ball))
    {
        node->ne = init_node(node, 1);
        node->nw = init_node(node, 2);
        node->sw = init_node(node, 3);
        node->se = init_node(node, 4);
        if (debug>0)
        {
            draw_node(node);
            draw_range(ball);
        }

        levels--;
        subdivide(node->ne, levels, ball, platform, block);
        subdivide(node->nw, levels, ball, platform, block);
        subdivide(node->sw, levels, ball, platform, block);
        subdivide(node->se, levels, ball, platform, block);

    }

    if (levels == 0) {
        if (contain_platform(node, platform)) {
            if(debug>0)
                draw_outline(node);
                check_collision(ball, platform);
        }

            for (int i = 0; i < size;i++)
            {
                for (int j = 0; j < size;j++)
                {
                    if (contain_block(node, &(block[i][j])))
                    {
                        if(debug>0)
                            draw_outline(node);
                        if (check_collision(ball, &(block[i][j])))
                            points += 100;
                    }                    
                }
            }
    }
}

void update(struct Quad_Tree_Node** root, struct Ball* ball, struct block* platform, struct block** block)
{
    free_node(*root);
    *root = NULL;
    *root = init_node(*root, 0);
    subdivide(*root, MAX_LVL - 1, ball, platform, block);
}
void wynik(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* wyniki, FILE* scores)
{
    bool working_wyniki = true;
    al_draw_bitmap(wyniki, 0, 0, 0);
    al_flip_display();
    while (working_wyniki)
    {
        al_flip_display();
        ALLEGRO_EVENT ev;
        al_get_next_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_ENTER:
                    working_wyniki = false;
                    break;
            }
        }                
    }
}

void opcje(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* opcje1, ALLEGRO_BITMAP* opcje2, ALLEGRO_BITMAP* opcje3)
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

        al_flip_display();
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                if (choice > 1)
                    choice--;
                break;
            case ALLEGRO_KEY_DOWN:
                if (choice < 3)
                    choice++;
                break;
            case ALLEGRO_KEY_ENTER:
                switch (choice)
                {
                    case 1 :
                        debug *= (-1);
                        break;
                    case 2:
                        sound *= (-1);
                        break;
                    case 3:
                        working_opcje = 0;
                        break;
                }
                break;
            }
        }

    }
}


bool menu(ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* menu1, ALLEGRO_BITMAP* menu2, ALLEGRO_BITMAP* menu3, ALLEGRO_BITMAP* menu4,
          ALLEGRO_BITMAP* opcje1, ALLEGRO_BITMAP* opcje2, ALLEGRO_BITMAP* opcje3, ALLEGRO_BITMAP* wyniki, FILE* scores)
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

        al_flip_display();
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                if (choice > 1)
                    choice--;
                break;
            case ALLEGRO_KEY_DOWN:
                if (choice < 4)
                    choice++;
                break;
            case ALLEGRO_KEY_ENTER:
                switch (choice)
                {
                    case 1:
                        working_menu = 0;
                        return true;
                        break;
                    case 2:
                        opcje(event_queue, opcje1, opcje2, opcje3);
                        break;
                    case 3:
                        wynik(event_queue, wyniki, scores);
                        break;
                    case 4:
                        working_menu = 0;
                        return false;
                        break;

                }
                break;
            }
        }

    }
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
    ALLEGRO_BITMAP* opcje1, ALLEGRO_BITMAP* opcje2, ALLEGRO_BITMAP* opcje3, ALLEGRO_BITMAP* wyniki, ALLEGRO_BITMAP* tlo, FILE* scores, ALLEGRO_FONT* font)
{
    int i = 0;
    while (working)
    {
        Platform.state = 1;
        al_draw_textf(font, al_map_rgb(255, 255, 255), 30, 30, 0, "SCORE: %d", points);
        al_draw_rectangle(1, height * 1.0 / 9.0, width - 1, height - 1, al_map_rgb(255, 255, 255), 4);
        al_draw_filled_rectangle(Platform.x - Platform.w, Platform.y - Platform.h, Platform.x + Platform.w, Platform.y + Platform.h, al_map_rgb(255, 255, 255));
        al_draw_filled_circle(New_Ball.x, New_Ball.y, New_Ball.r, al_map_rgb(0, 0, 255));
        al_flip_display();
        al_draw_bitmap(tlo, 0, 0, 0);
        draw_block(array, size);
        ALLEGRO_EVENT ev;
        if (i == 7 && ball_move == 1) {
            move(&New_Ball, Platform);
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
                working = menu(event_queue, menu1, menu2, menu3, menu4, opcje1, opcje2, opcje3, wyniki, scores);
                break;
            }
        }
        update(&root, &New_Ball, &Platform, array);
        i++;
        if (lives == 0)
        {
            ball_move = 0;
            //al_draw_bitmap();
            al_flip_display();
            wait_for_keypress();
            working = false;
        }
    }
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
    ALLEGRO_FONT* font = NULL;
    FILE* scores;
    scores = fopen("scores.txt", "a+" );
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
    init_array(array);

    working = menu(event_queue, menu1, menu2, menu3, menu4, opcje1, opcje2, opcje3, wyniki, scores);
   
    while(working)
    game(working,array,root,Platform,New_Ball,
         event_queue, menu1, menu2, menu3, menu4,
         opcje1, opcje2, opcje3, wyniki, tlo, scores, font);

    al_uninstall_keyboard();
    al_destroy_display(display);
    free_ptr(array);

    return 0;
}