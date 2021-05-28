///@files scores.c zawiera funkcje odpowiadaj�ce za zapis, odczyt i sortowanie wynik�w
#pragma once
#include "scores.h"\

/**
* @brief Funkcja sortowanie_babelkowe() sortuje tablice przez por�wnanie dw�ch kolejnych element�w i zamianie ich kolejno�ci, je�eli zaburza ona porz�dek
* @param tab[] tablica zawieraj�ce wynik�w odczytanych z pliku
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
* @brief Funkcja sort_scores() najpierw odczytuje dane z pliku i zapisuje je do tablicy, po czym wywo�uje funkcje od sortowania tej tablicy, a nast�pnie zapisuje do pliku 5 najlepszych wynik�w z tablicy
* @param scores Wska�nik na plik zawieraj�cy najlepsze wyniki
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
* @brief Funkcja save_score() dopisuje wynik punkt�w do pliku a nast�pnie wywo�uje funkcje do posortowania wynik�w w pliku
* @param scores Wska�nik na plik zawieraj�cy najlepsze wyniki
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
* @param scores Wska�nik na plik zawieraj�cy najlepsze wyniki
* @param font Wska�nik na czcionk� u�ywan� w programie
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