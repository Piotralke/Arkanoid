/// @file include_lib.c Plik include_lib.c zawiera przypisanie domyœlnych wartoœci do zmiennych globalnych u¿ywanych w programie
#include "include_lib.h"
/**
* @param ball_move Odpowiada za to, czy pi³ka siê porusza, czy stoi w miejscu
* @param size Rozmiar dynamicznej tablicy dwuwymiarowej, zawieraj¹cej informacje o bloczkach
* @param debug Parametr odpowiadaj¹cy za w³¹czanie/wy³¹czanie trybu debuggerskiego
* @param sound Parametr odpowiadaj¹cy za w³¹czanie/wy³¹czanie dŸwiêku
* @param pause Parametr ustalaj¹cy, czy aktualnie znajdujemy siê w g³ównym menu, czy w menu pauzy
* @param lifes Parametr odpowiadaj¹cy za iloœæ ¿yæ
* @param point Parametr odpowiedzialny za iloœæ zdobytych punktów
* @param block_counter Parametr zliczaj¹cy iloœæ aktualnych bloczków znajduj¹cych siê na planszy
* @param ball_speed Parametr odpowiedzialny za szybkoœæ przechodzenia pi³ki po ekranie
* @param bonus_active Parametr odpowiedzialny za iloœæ bonusów, które zosta³y utworzone na planszy
* @param bonus_speed Parametr odpowiedzialny za szybkoœæ poruszania siê bonusu
* @param g_t Parametr odpowiedzialny za aktywny bonus przechodzenia przez bloczki
* @param score_multiplier Parametr odpowiedzialny za bonus mno¿nika punktów
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