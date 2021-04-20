#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <stdbool.h>
#define width  800
#define height  900
#define MAX_LVL 3

struct block
{
    int x1;
    int y1;
    int x2;
    int y2;
    int center_x; //  (x1 + x2) / 2;
    int center_y; //  (y1 + y2) / 2;
    bool state;
};

struct Quad_Tree_Node
{
    int h;
    int w;
    int x;
    int y;
    struct block* block_ptr;
    struct Quad_Tree_Node* ne, * nw, * sw, * se;
};

struct Quad_Tree_Node* init_node(struct Quad_Tree_Node* root, int choice)
{
    if (choice == 0)
    {
        root = (struct Quad_Tree_Node*)malloc(sizeof(struct Quad_Tree_Node));
        if (root) {
        root->x = width / 2;
        root->y = height * (8 / 9) / 2;
        root->h = height * (8 / 9) / 2;
        root->w = width / 2;
        root->ne = NULL;
        root->nw = NULL;
        root->sw = NULL;
        root->se = NULL;
    }
        return root;
    }
    else if(choice == 1){   //ne
        struct Quad_Tree_Node* node = (struct Quad_Tree_Node*)malloc(sizeof(struct Quad_Tree_Node));
        if (node){
            node->x = root->x + root->w / 2;
            node->y = root->y - root->h / 2;
            node->h = root->h / 2;
            node->w = root->w / 2;
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
            node->x = root->x - root->w / 2;
            node->y = root->y - root->h / 2;
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
            node->x = root->x - root->w / 2;
            node->y = root->y + root->h / 2;
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
            node->x = root->x + root->w / 2;
            node->y = root->y + root->h / 2;
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

void draw_node(struct Quad_Tree_Node* node)
{
    al_draw_rectangle(node->x, node->y-node->h, node->x + node->w, node->y, al_map_rgb(255, 255, 255), 2); // ne
    al_draw_rectangle(node->x - node->w, node->y - node->h, node->x, node->y, al_map_rgb(255, 255, 255), 2); //nw
    al_draw_rectangle(node->x - node->w, node->y, node->x, node->y + node->h, al_map_rgb(255, 255, 255), 2); //sw
    al_draw_rectangle(node->x, node->y, node->x + node->w, node->y + node->h, al_map_rgb(255, 255, 255), 2); //se
}

void free_node(struct Quad_Tree_Node* node)
{
    if (node!=NULL)
    {
        free_node(node->ne);
        free_node(node->nw);
        free_node(node->sw);
        free_node(node->se);
    }
    free(node);
}


void subdivide(struct Quad_Tree_Node* node, int levels)
{
    if (node && levels > 0)
    {
        levels--;
        node->ne = init_node(node,1);
        node->nw = init_node(node,2);
        node->sw = init_node(node,3);
        node->se = init_node(node,4);
        draw_node(node);
        subdivide(node->ne, levels);
        subdivide(node->nw, levels);
        subdivide(node->sw, levels);
        subdivide(node->se, levels);
    }
}


void update(struct Quad_Tree_Node* root)
{
    free_node(root);
    root = NULL;
    root = init_node(root,0);
    subdivide(root, MAX_LVL - 1);
}


struct Ball
{
    int x;
    int y;
    int r;
    int vx;
    int vy;
}ball;

struct Platform
{
    int x1;
    int y1;
    int x2;
    int y2;
};

void move(struct Ball* ball)
{
    if (ball->x < 800)
        ball->x += ball->vx;
    if (ball->y < 900)
        ball->y += ball->vy;
    if (ball->y == 900) {
        ball->x = width / 2;
        ball->y = height / 2;
    }
}

int main(int argc, char* argv[])
{
    
    bool working = true;
    bool pressed_key[ALLEGRO_KEY_MAX];

    struct block Platform = { width / 2, height - 50,Platform.x1 + 100,Platform.y1 + 20 };
    struct Ball New_Ball = { width / 2, height / 2, 10, 1, 1 };
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_BITMAP* bitmap = NULL;
    ALLEGRO_BITMAP* board = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer_FPS = NULL;

    if (!al_init()) {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return -1;
    }
    event_queue = al_create_event_queue();
    display = al_create_display(width, height);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    bitmap = al_create_bitmap(width, height);
    if (!bitmap) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }

    board = al_create_sub_bitmap(bitmap, 1, height * 1 / 9, width - 1, height - 1);
    if (!board) {
        fprintf(stderr, "Failed to create bitmap!\n");
        return -1;
    }

    timer_FPS = al_create_timer(1.0 / 60);
    if (!timer_FPS) {
        fprintf(stderr, "Failed to create FPS timer!\n");
        return -1;
    }


    al_register_event_source(event_queue, al_get_timer_event_source(timer_FPS));
    al_init_primitives_addon();
    al_install_keyboard();
    al_start_timer(timer_FPS);
    al_clear_to_color(al_map_rgb(0, 0, 0));                             //kolor tla
    al_flip_display();

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    int i = 0;

    
    struct Quad_Tree_Node* root = NULL;
    root = init_node(root, 0);
    draw_node(root);
    subdivide(root, MAX_LVL - 1);

    while (working)
    {
        update(root);
        /*al_draw_rectangle(1, height * 1 / 9, width - 1, height - 1, al_map_rgb(255, 255, 255), 4);
        al_draw_filled_rectangle(Platform.x1, Platform.y1, Platform.x2, Platform.y2, al_map_rgb(255, 255, 255));
        al_draw_filled_circle(New_Ball.x, New_Ball.y, New_Ball.r, al_map_rgb(0, 0, 255));*/
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
        
        ALLEGRO_EVENT ev;
        ALLEGRO_KEYBOARD_STATE key;
        if (i == 20) {
            move(&New_Ball);
            i = 0;
        }
        al_get_next_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            al_get_keyboard_state(&key);
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                pressed_key[ALLEGRO_KEY_LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                pressed_key[ALLEGRO_KEY_RIGHT] = true;
                break;
            case ALLEGRO_KEY_ESCAPE:
                working = false;
                break;
            }
        }
        if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            al_get_keyboard_state(&key);
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                pressed_key[ALLEGRO_KEY_LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                pressed_key[ALLEGRO_KEY_RIGHT] = false;
                break;
            }
        }
        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if(pressed_key[ALLEGRO_KEY_LEFT]&& Platform.x1 > 0)
            {
                Platform.x1 -= 1;
                Platform.x2 -= 1;
            }
            if (pressed_key[ALLEGRO_KEY_RIGHT] && Platform.x2 < width - 1)
            {
                Platform.x1 += 1;
                Platform.x2 += 1;
            }
        }
        i++;
    }
    al_uninstall_keyboard();
    al_destroy_display(display);

    return 0;
}