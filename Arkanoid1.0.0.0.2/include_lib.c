/// @file include_lib.c Plik include_lib.c zawiera przypisanie domy�lnych warto�ci do zmiennych globalnych u�ywanych w programie
#include "include_lib.h"
/**
* @param ball_move Odpowiada za to, czy pi�ka si� porusza, czy stoi w miejscu
* @param size Rozmiar dynamicznej tablicy dwuwymiarowej, zawieraj�cej informacje o bloczkach
* @param debug Parametr odpowiadaj�cy za w��czanie/wy��czanie trybu debuggerskiego
* @param sound Parametr odpowiadaj�cy za w��czanie/wy��czanie d�wi�ku
* @param pause Parametr ustalaj�cy, czy aktualnie znajdujemy si� w g��wnym menu, czy w menu pauzy
* @param lifes Parametr odpowiadaj�cy za ilo�� �y�
* @param point Parametr odpowiedzialny za ilo�� zdobytych punkt�w
* @param block_counter Parametr zliczaj�cy ilo�� aktualnych bloczk�w znajduj�cych si� na planszy
* @param ball_speed Parametr odpowiedzialny za szybko�� przechodzenia pi�ki po ekranie
* @param bonus_active Parametr odpowiedzialny za ilo�� bonus�w, kt�re zosta�y utworzone na planszy
* @param bonus_speed Parametr odpowiedzialny za szybko�� poruszania si� bonusu
* @param g_t Parametr odpowiedzialny za aktywny bonus przechodzenia przez bloczki
* @param score_multiplier Parametr odpowiedzialny za bonus mno�nika punkt�w
*/
ball_move = 0;
size = 8;
debug = -1;
sound = -1;
pause = 1;
lifes = 3;
points = 0;
block_counter = 0;
ball_speed = 6;
bonus_active = 0;
bonus_speed = 0;
g_t = 0;
score_multiplier = 1;