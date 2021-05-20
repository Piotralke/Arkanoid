#pragma once
#ifndef LEVELS_H
#define LEVELS_H
#include "include_lib.h"

extern void init_level1(struct block** array);
extern void init_level2(struct block** array);
extern void init_level3(struct block** array);
extern void init_level4(struct block** array);
extern void draw_block1(struct block** array);
extern void draw_block2(struct block** array);
extern void draw_block3(struct block** array);
extern void draw_block4(struct block** array);
extern void free_ptr(struct block** array);

#endif // !LEVELS_H

