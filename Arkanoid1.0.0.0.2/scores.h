#pragma once
#ifndef SCORES_H
#define SCORES_H
#include "include_lib.h"

extern void sortowanie_babelkowe(int tab[]);
extern void sort_scores(FILE* scores);
extern void save_score(FILE* scores);
extern void read_scores(FILE* scores, ALLEGRO_FONT* font);
#endif // !SCORES_H

