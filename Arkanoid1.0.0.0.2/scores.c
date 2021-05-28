///@files scores.c zawiera funkcje odpowiadaj¹ce za zapis, odczyt i sortowanie wyników
#pragma once
#include "scores.h"\

/**
* @brief Funkcja sortowanie_babelkowe() sortuje tablice przez porównanie dwóch kolejnych elementów i zamianie ich kolejnoœci, je¿eli zaburza ona porz¹dek
* @param tab[] tablica zawieraj¹ce wyników odczytanych z pliku
*/
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

/**
* @brief Funkcja sort_scores() najpierw odczytuje dane z pliku i zapisuje je do tablicy, po czym wywo³uje funkcje od sortowania tej tablicy, a nastêpnie zapisuje do pliku 5 najlepszych wyników z tablicy
* @param scores WskaŸnik na plik zawieraj¹cy najlepsze wyniki
*/
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

/**
* @brief Funkcja save_score() dopisuje wynik punktów do pliku a nastêpnie wywo³uje funkcje do posortowania wyników w pliku
* @param scores WskaŸnik na plik zawieraj¹cy najlepsze wyniki
*/
void save_score(FILE* scores)
{
    fclose(scores);
    scores = fopen("scores.txt", "a");
    if (scores)
        fprintf(scores, "%d\n", points);
    sort_scores(scores);
}

/**
* @brief Funkcja read_scores() wypisuje na ekran najlepsze wyniki odczytane z pliku
* @param scores WskaŸnik na plik zawieraj¹cy najlepsze wyniki
* @param font WskaŸnik na czcionkê u¿ywan¹ w programie
*/
void read_scores(FILE* scores, ALLEGRO_FONT* font)
{
    int number;
    fclose(scores);
    scores = fopen("scores.txt", "r");
    if (scores)
        for (int i = 0; fscanf(scores, "%d", &number) != EOF && i < 5;i++)
        {
            al_draw_textf(font, al_map_rgb(0, 0, 0), 195, 495 + i * 50, 0, "%d. %d", i + 1, number);
        }
    fclose(scores);
}