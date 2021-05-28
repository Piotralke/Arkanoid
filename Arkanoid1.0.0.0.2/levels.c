///@file levels.c zawiera funkcje odpowiedzialne za odpowiedni¹ inicjacjê tablicy dwuwymiarowej dla danego poziomu, funkcje rysuj¹ce bloki w odpowiednim kolorze dla danego poziomu, oraz funkcjê zwalniaj¹c¹ tablicê
#include "levels.h"

/**
* @brief Funkcja init_level1() generuje sposób u³o¿enia klocków na danym poziomie
* @param array To Dynamiczna dwuwymiarowa tablica, która zawiera informacje o bloczkach po³o¿onych na planszy
*/
void init_level1(struct block** array)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((i < 4 && (j > size - i - 1 && j < size + i - 1)) || i < 4 && (j > 0 - i && j < 0 + i));
            else if (i < 4)
            {
                array[i][j].x = 50 + j * 100;
                array[i][j].y = 125 + i * 50;
                array[i][j].h = 25;
                array[i][j].w = 50;
                array[i][j].state = 1;
                block_counter++;
            }

        }
    }
}

/**
* @brief Funkcja init_level2() generuje sposób u³o¿enia klocków na danym poziomie
* @param array To Dynamiczna dwuwymiarowa tablica, która zawiera informacje o bloczkach po³o¿onych na planszy
*/
void init_level2(struct block** array)
{
    for (int i = 0; i < size; i += 2)
    {
        for (int j = 0; j < size; j++)
        {
            array[i][j].x = 50 + j * 100;
            array[i][j].y = 125 + i * 50;
            array[i][j].h = 25;
            array[i][j].w = 50;
            array[i][j].state = 1;
            block_counter++;
        }
    }
}

/**
* @brief Funkcja init_level3() generuje sposób u³o¿enia klocków na danym poziomie
* @param array To Dynamiczna dwuwymiarowa tablica, która zawiera informacje o bloczkach po³o¿onych na planszy
*/
void init_level3(struct block** array)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j || j + i == size - 1)
            {
                array[i][j].x = 50 + j * 100;
                array[i][j].y = 125 + i * 50;
                array[i][j].h = 25;
                array[i][j].w = 50;
                array[i][j].state = 1;
                block_counter++;
            }

        }
    }
}

/**
* @brief Funkcja init_level4() generuje sposób u³o¿enia klocków na danym poziomie
* @param array To Dynamiczna dwuwymiarowa tablica, która zawiera informacje o bloczkach po³o¿onych na planszy
*/
void init_level4(struct block** array)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            array[i][j].x = 50 + j * 100;
            array[i][j].y = 125 + i * 50;
            array[i][j].h = 25;
            array[i][j].w = 50;
            array[i][j].state = 1;
            block_counter++;
        }
    }
}

/**
* @brief Funkcja draw_block1() rysuje na ekranie bloczki z tablicy z kolorem zale¿nym od poziomu
* @param array To Dynamiczna dwuwymiarowa tablica, która zawiera informacje o bloczkach po³o¿onych na planszy
*/
void draw_block1(struct block** array)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array[i][j].state == 1)
            {
                al_draw_filled_rectangle(array[i][j].x - array[i][j].w,
                    array[i][j].y - array[i][j].h,
                    array[i][j].x + array[i][j].w,
                    array[i][j].y + array[i][j].h,
                    al_map_rgb(255, 255, 0));
                al_draw_rectangle(array[i][j].x - array[i][j].w,
                    array[i][j].y - array[i][j].h,
                    array[i][j].x + array[i][j].w,
                    array[i][j].y + array[i][j].h,
                    al_map_rgb(0, 0, 0), 2);
            }

        }
    }
}

/**
* @brief Funkcja draw_block2() rysuje na ekranie bloczki z tablicy z kolorem zale¿nym od poziomu
* @param array To Dynamiczna dwuwymiarowa tablica, która zawiera informacje o bloczkach po³o¿onych na planszy
*/
void draw_block2(struct block** array)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array[i][j].state == 1)
            {
                al_draw_filled_rectangle(array[i][j].x - array[i][j].w,
                    array[i][j].y - array[i][j].h,
                    array[i][j].x + array[i][j].w,
                    array[i][j].y + array[i][j].h,
                    al_map_rgb(0, 255 - i * 15, i * 15));
                al_draw_rectangle(array[i][j].x - array[i][j].w,
                    array[i][j].y - array[i][j].h,
                    array[i][j].x + array[i][j].w,
                    array[i][j].y + array[i][j].h,
                    al_map_rgb(0, 0, 0), 2);
            }

        }
    }
}

/**
* @brief Funkcja draw_block3() rysuje na ekranie bloczki z tablicy z kolorem zale¿nym od poziomu
* @param array To Dynamiczna dwuwymiarowa tablica, która zawiera informacje o bloczkach po³o¿onych na planszy
*/
void draw_block3(struct block** array)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array[i][j].state == 1)
            {
                al_draw_filled_rectangle(array[i][j].x - array[i][j].w,
                    array[i][j].y - array[i][j].h,
                    array[i][j].x + array[i][j].w,
                    array[i][j].y + array[i][j].h,
                    al_map_rgb(230, 0, 0));
                al_draw_rectangle(array[i][j].x - array[i][j].w,
                    array[i][j].y - array[i][j].h,
                    array[i][j].x + array[i][j].w,
                    array[i][j].y + array[i][j].h,
                    al_map_rgb(0, 0, 0), 2);
            }

        }
    }
}

/**
* @brief Funkcja draw_block4() rysuje na ekranie bloczki z tablicy z kolorem zale¿nym od poziomu
* @param array To Dynamiczna dwuwymiarowa tablica, która zawiera informacje o bloczkach po³o¿onych na planszy
*/
void draw_block4(struct block** array)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (array[i][j].state == 1)
            {
                al_draw_filled_rectangle(array[i][j].x - array[i][j].w,
                    array[i][j].y - array[i][j].h,
                    array[i][j].x + array[i][j].w,
                    array[i][j].y + array[i][j].h,
                    al_map_rgb(0, i * 15, 255 - i * 15));
                al_draw_rectangle(array[i][j].x - array[i][j].w,
                    array[i][j].y - array[i][j].h,
                    array[i][j].x + array[i][j].w,
                    array[i][j].y + array[i][j].h,
                    al_map_rgb(0, 0, 0), 2);
            }

        }
    }
}

/**
* @brief Funkcja free+ptr() zwalnia pamiêæ dwuwymiarowej tablicy bloczków
* @param array To Dynamiczna dwuwymiarowa tablica, która zawiera informacje o bloczkach po³o¿onych na planszy
*/
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