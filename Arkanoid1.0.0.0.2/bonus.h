#ifndef BONUS_H
#define BONUS_H
#include "include_lib.h"
#include "init.h"

extern void give_bonus(struct bonus* New_bonus, struct block* platform, ALLEGRO_SAMPLE* bonus);
extern void make_bonus(int bonus_type, struct block* block, struct bonus* New_bonus);
extern void bonus(struct block* block, struct bonus* New_bonus);

#endif // !BONUS_H
