#pragma once
#ifndef PHYSIC_H
#define PHYSIC_H
#include "include_lib.h"

extern void move(struct Ball* ball, struct block platform, ALLEGRO_SAMPLE* hit);
extern bool check_bonus(struct block* block, struct bonus* bonus);
extern bool check_block(struct Ball* ball, struct block* block);
extern bool check_platform(struct Ball* ball, struct block* block);

#endif // !PHYSIC_H
