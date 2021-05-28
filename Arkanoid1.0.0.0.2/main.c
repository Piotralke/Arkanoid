/// @file main.c G³ówny plik z funkcj¹ main.
#include "quadtree.h"
#include "menu.h"
#include "scores.h"
#include "init.h"
#include "game.h"
#include "uninstall.h"
/// @brief Funkcja main to g³ówna funkcja programu. Na pocz¹tku ustawiane s¹ wartoœci domyœlne struktur oraz zmiennych. Alokowana jest równie¿ pamiêæ dla dwuwymiarowej tablicy dynamicznej
int main()
{
    struct block Platform = { (width / 2), height - 30,75,10, 1 };
    struct Ball New_Ball = { Platform.x , Platform.y - Platform.h - 5, 10, 1, 1 };
    struct bonus New_bonus = {0,0,0,0,0,NULL};
    init_arkanoid();
    do
    {
        lifes = 3;
        points = 0;
        ball_move = 0;
        choice_lvl = 0;
        block_counter = 0;
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
        game(working, array, root, Platform, New_Ball, New_bonus,
            event_queue, menu1, menu2, menu3, menu4,
            opcje1, opcje2, opcje3, wyniki, tlo, zycie, gameover, youwin, scores, font,
            ruch, klik, check, hit, destroy, gameover_m, youwin_m, musicInstance);
        al_stop_sample_instance(musicInstance);
        free_ptr(array);
        save_score(scores);
    } while (working);
    uninstall_arkanoid();
    return 0;
}