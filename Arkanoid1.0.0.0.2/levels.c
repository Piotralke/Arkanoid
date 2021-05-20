#include "levels.h"
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