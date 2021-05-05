#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <stdbool.h>
#include <math.h>
#define width  800
#define height  900
#define MAX_LVL 5
const int platform_state = 1;
int ball_move = 0;

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
    struct block* block_ptr;
    struct Ball* ball_ptr;
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

bool contain_block(struct Quad_Tree_Node* node, struct block* block)
{
    if (block->x - block->w >= node->x - node->w &&
        block->x - block->w <= node->x + node->w &&
        block->y - block->h >= node->y - node->h &&
        block->y - block->h <= node->y + node->h ||
        block->x + block->w <= node->x + node->w &&
        block->x + block->w >= node->x - node->w &&
        block->y + block->h <= node->y + node->h &&
        block->y + block->h >= node->y - node->h ||
        block->x - block->w >= node->x - node->w &&
        block->x - block->w <= node->x + node->w &&
        block->y + block->h >= node->y - node->h &&
        block->y + block->h <= node->y + node->h ||
        block->x + block->w <= node->x + node->w &&
        block->x + block->w >= node->x - node->w &&
        block->y - block->h >= node->y - node->h &&
        block->y - block->h <= node->y + node->h ||
        block->y >= node->y - node->h &&
        block->y <= node->y + node->h &&
        block->x >= node->x - node->w &&
        block->x <= node->x + node->w ||
        block->y >= node->y - node->h &&
        block->y <= node->y + node->h &&
        block->x + 0.5*block->w >= node->x - node->w &&
        block->x + 0.5 * block->w <= node->x + node->w ||
        block->y >= node->y - node->h &&
        block->y <= node->y + node->h &&
        block->x - 0.5 * block->w >= node->x - node->w &&
        block->x - 0.5 * block->w <= node->x + node->w)
        return true;
    else
        return false;
}

void check_collision(struct Ball* ball, struct block* block)    //funkcja do poprawy, nie dziala.
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

    if (distance <= 0)
    {
        ball->y -= 1;
        ball->vy = (-1)*ball->vy;
    }
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

draw_outline(struct Quad_Tree_Node* node)
{
    al_draw_rectangle(node->x - node->w, node->y - node->h, node->x + node->w, node->y + node->h, al_map_rgb(255, 0, 0), 2);
}

void subdivide(struct Quad_Tree_Node* node, int levels, struct Ball* ball, struct block* block)
{
    if (node && levels > 0 && contain(node, ball))
    {
        node->ne = init_node(node, 1);
        node->nw = init_node(node, 2);
        node->sw = init_node(node, 3);
        node->se = init_node(node, 4);
        draw_node(node);
        draw_range(ball);
        levels--;
        subdivide(node->ne, levels, ball, block);
        subdivide(node->nw, levels, ball, block);
        subdivide(node->sw, levels, ball, block);
        subdivide(node->se, levels, ball, block);

    }

    if (levels == 0) {
        if (contain_block(node, block)) {
            draw_outline(node);
            check_collision(ball, block);
        }
    }
    
}

void update(struct Quad_Tree_Node** root, struct Ball* ball, struct block* block)
{
    free_node(*root);
    *root = NULL;
    *root = init_node(*root, 0);
    subdivide(*root, MAX_LVL - 1, ball, block);
}

int main(int argc, char* argv[])
{
    bool working = true;
    int i = 0;
    struct block Platform = { (width / 2), height - 30,75,10, platform_state };
    struct Ball New_Ball = { Platform.x , Platform.y - Platform.h - 5, 10, 1, 1 };
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

    timer_FPS = al_create_timer(1.0 / 160);
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


    struct Quad_Tree_Node* root = NULL;
    root = init_node(root, 0);

    while (working)
    {

        al_draw_rectangle(1, height * 1.0 / 9.0, width - 1, height - 1, al_map_rgb(255, 255, 255), 4);
        al_draw_filled_rectangle(Platform.x - Platform.w, Platform.y - Platform.h + New_Ball.r, Platform.x + Platform.w, Platform.y + Platform.h, al_map_rgb(255, 255, 255));
        al_draw_filled_circle(New_Ball.x, New_Ball.y, New_Ball.r, al_map_rgb(0, 0, 255));
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));

        ALLEGRO_EVENT ev;
        if (i == 8 && ball_move == 1) {
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
                i = 7;
                break;
            case ALLEGRO_KEY_ESCAPE:
                working = false;
                break;
            }
        }
        update(&root, &New_Ball, &Platform);

        i++;
    }
    al_uninstall_keyboard();
    al_destroy_display(display);

    return 0;
}