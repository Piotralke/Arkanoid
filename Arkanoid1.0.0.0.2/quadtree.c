/// @file quadtree.c Zawiera implementacj� drzewa czw�rkowego
#include "quadtree.h"
/// @param bonus_counter Mno�nik punkt�w, kt�ry jest inkrementowany przy wielu zbiciach bloczk�w bez odbicia od platformy
bonus_counter = 1;
/**
* @brief Funkcja init_node() Inicjuje korze� oraz �wiartki drzewa czw�rkowego nadaj�c im odpowiednie warto�ci.
* @param root Wska�nik na korze� drzewa
* @param choice Zmienna okre�laj�ca kt�ra �wiartka ma by� zainicjowana (0-korzen,1-NE,2-NW,3-SW,4-SE)
* @return root, w przypadku kiedy inicjowany jest korzen
* @return node w przypadku kiedy inicjowana jest �wiartka
*/
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
/**
* @brief Funkcja draw_node() rysuje na planszy obszar zagnie�d�enia drzewa czw�rkowego
* @param node Wska�nik na �wiartk� drzewa czw�rkowego
*/
void draw_node(struct Quad_Tree_Node* node)
{
    al_draw_rectangle(node->x, node->y - node->h, node->x + node->w, node->y, al_map_rgb(255, 255, 255), 2); //ne
    al_draw_rectangle(node->x - node->w, node->y - node->h, node->x, node->y, al_map_rgb(255, 255, 255), 2); //nw
    al_draw_rectangle(node->x - node->w, node->y, node->x, node->y + node->h, al_map_rgb(255, 255, 255), 2); //sw
    al_draw_rectangle(node->x, node->y, node->x + node->w, node->y + node->h, al_map_rgb(255, 255, 255), 2); //se
}
/**
* @brief Funkcja draw_range() rysuje zasi�g detekcji kolizji wok� pi�ki
* @param ball Wska�nik na struktur� pi�ki
*/
void draw_range(struct Ball* ball)
{
    al_draw_rectangle(ball->x - ball->r - 25, ball->y - ball->r - 25, ball->x + ball->r + 25, ball->y + ball->r + 25, al_map_rgb(0, 255, 0), 1);
}
/**
* @brief Funkcja draw_outline() zaznacza na czerwono najmniejsze �wiartki, kt�re znajduj� si� w zasiegu detekcji kolizji pi�ki
* @param node Wska�nik na �wiartk� drzewa czw�rkowego
*/
void draw_outline(struct Quad_Tree_Node* node)
{
    al_draw_rectangle(node->x - node->w, node->y - node->h, node->x + node->w, node->y + node->h, al_map_rgb(255, 0, 0), 2);
}
/**
* @brief Funkcja contain() sprawdza, w kt�rych najmniejszych �wiartkach znajduje si� zasi�g detekcji pi�ki
* @param node Wska�nik na �wiartk� drzewa czw�rkowego
* @param ball Wska�nik na struktur� pi�ki
* @return true W przypadku, kiedy zasi�g znajduje si� w �wiartce
* @return false Je�li si� w niej nie znajduje
*/
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
/**
* @brief Funkcja contain_platform() sprawdza, czy platforma znajduje si� w danej najmniejszej �wiartce
* @param node Wska�nik na �wiartk� drzewa czw�rkowego
* @param block Wska�nik na struktur� reprezentuj�c� platform�
* @return true W przypadku, kiedy platforma znajduje si� w �wiartce
* @return false Je�li si� w niej nie znajduje
*/
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
        block->x + 0.5 * block->w > node->x - node->w &&
        block->x + 0.5 * block->w < node->x + node->w ||
        block->y > node->y - node->h &&
        block->y < node->y + node->h &&
        block->x - 0.5 * block->w > node->x - node->w &&
        block->x - 0.5 * block->w < node->x + node->w)
        return true;
    else
        return false;
}
/**
* @brief Funkcja contain_block() sprawdza, czy bloczek znajduje si� w danej najmniejszej �wiartce
* @param node Wska�nik na �wiartk� drzewa czw�rkowego
* @param block Wska�nik na struktur� bloczka
* @return true W przypadku, kiedy bloczek znajduje si� w �wiartce
* @return false Je�li si� w niej nie znajduje
*/
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
            block->x <= node->x + node->w)
            return true;
        else
            return false;
    }
    else
        return false;
}
/**
* @brief Funkcja rekurencyjna free_node() dealokuje pami�� drzewa czw�rkowego rozpoczynaj�c zwalnianie pami�ci od najmniejszych �wiartek ko�cz�c na korzeniu
* @param node Wska�nik na w�ze� drzewa czw�rkowego
*/
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
/**
* @brief Funkcja subdivide() dzieli ekran maksymalnie 5 razy (wizualnie 4, bo 1 podzia� to utworzenie korzenia, czyli w�z�a, kt�ry b�dzie mia� wymiary planszy) a� ograniczy obszar wykrywania
* kolizji wok� pi�ki do najmniejszego
* @param node Wska�nik na w�ze� drzewa czw�rkowego
* @param levels Zmienna odpowiadaj�ca za ilo�� zagnie�d�e� drzewa
* @param ball Wska�nik na struktur� pi�ki
* @param platform Wska�nik na struktur� platformy
* @param block Dynamiczna dwuwymiarowa tablica struktur reprezentuj�cych bloczki
* @param hit Wska�nik na d�wi�k, kt�ry jest wywo�ywany podczas kolizji pi�ki z elementem planszy
* @param destroy Wska�nik na d�wi�k, kt�ry jest wywo�ywany podczas zniszczenia bloczka
* @param New_bonus Wska�nik na struktur� bonusu
*/
void subdivide(struct Quad_Tree_Node* node, int levels, struct Ball* ball, struct block* platform, struct block** block,
    ALLEGRO_SAMPLE* hit, ALLEGRO_SAMPLE* destroy, struct bonus* New_bonus)
{
    if (node && levels > 0 && contain(node, ball))
    {
        node->ne = init_node(node, 1);
        node->nw = init_node(node, 2);
        node->sw = init_node(node, 3);
        node->se = init_node(node, 4);
        if (debug > 0)
        {
            draw_node(node);
            draw_range(ball);
        }

        levels--;
        subdivide(node->ne, levels, ball, platform, block, hit, destroy, New_bonus);
        subdivide(node->nw, levels, ball, platform, block, hit, destroy, New_bonus);
        subdivide(node->sw, levels, ball, platform, block, hit, destroy, New_bonus);
        subdivide(node->se, levels, ball, platform, block, hit, destroy, New_bonus);

    }

    if (levels == 0) {
        if (contain_platform(node, platform)) {
            if (debug > 0)
                draw_outline(node);
            if (check_platform(ball, platform, 0)) {
                bonus_counter = 1;
                if (sound > 0)
                    al_play_sample(hit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            }

        }

        for (int i = 0; i < size;i++)
        {
            for (int j = 0; j < size;j++)
            {
                if (contain_block(node, &(block[i][j])))
                {
                    if (debug > 0)
                        draw_outline(node);
                    if (check_block(ball, &(block[i][j])))
                    {
                        points += score_multiplier*bonus_counter*100;
                        bonus_counter++;
                        block_counter--;
                        if (bonus_active <= 0)
                        {
                            bonus_speed = 9;
                            bonus(&(block[i][j]), New_bonus);
                        }
                        if (sound > 0)
                            al_play_sample(destroy, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    }

                }
            }
        }
    }
}
/**
* @brief Funkcja update() aktualizuje nasze drzewo. Jest ona wywo�ywana w g��wnej p�tli gry przy ka�dym jej przej�ciu
* @param root Podw�jny wska�nik na korze� drzewa czw�rkowego
* @param ball Wska�nik na struktur� pi�ki
* @param platform Wska�nik na struktur� platformy
* @param New_bonus Wska�nik na struktur� bonusu
* @param block Dynamiczna dwuwymiarowa tablica struktur reprezentuj�cych bloczki
* @param hit Wska�nik na d�wi�k, kt�ry jest wywo�ywany podczas kolizji pi�ki z elementem planszy
* @param destroy Wska�nik na d�wi�k, kt�ry jest wywo�ywany podczas zniszczenia bloczka
*/
void update(struct Quad_Tree_Node** root, struct Ball* ball, struct block* platform, struct bonus* New_bonus, struct block** block, ALLEGRO_SAMPLE* hit, ALLEGRO_SAMPLE* destroy)
{
    free_node(*root);
    *root = NULL;
    *root = init_node(*root, 0);
    subdivide(*root, MAX_LVL - 1, ball, platform, block, hit, destroy, New_bonus);
}
