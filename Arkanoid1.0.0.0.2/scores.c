#pragma once
#include "scores.h"
void sortowanie_babelkowe(int tab[])
{
    for (int i = 1; i < 7; ++i)
        for (int j = 7 - 1; j > 0; --j) {
            if (tab[j] > tab[j - 1]) {
                int tmp = tab[j - 1];
                tab[j - 1] = tab[j];
                tab[j] = tmp;
            }
        }
}

void sort_scores(FILE* scores)
{
    fclose(scores);
    int scores_table[7] = { 0, 0, 0, 0, 0, 0, 0 };
    int number;
    scores = fopen("scores.txt", "r");
    if (scores)
        for (int i = 0; fscanf(scores, "%d", &number) != EOF && i < 7; i++)
            scores_table[i] = number;

    fclose(scores);
    sortowanie_babelkowe(scores_table);

    scores = fopen("scores.txt", "w");
    if (scores)
        for (int i = 0; i < 5; i++)
            fprintf(scores, "%d\n", (int)scores_table[i]);
    fclose(scores);
}

void save_score(FILE* scores)
{
    fclose(scores);
    scores = fopen("scores.txt", "a");
    if (scores)
        fprintf(scores, "%d\n", points);
    sort_scores(scores);
}