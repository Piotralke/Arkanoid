#pragma once
#ifndef PHYSIC_H
#define PHYSIC_H
#include "include_lib.h"

extern void move(struct Ball* ball, struct block platform, ALLEGRO_SAMPLE* hit);
extern bool check_collision(struct Ball* ball, struct block* block);

#endif // !PHYSIC_H
