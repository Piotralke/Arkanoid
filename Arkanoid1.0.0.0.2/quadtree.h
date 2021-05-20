#pragma once
#ifndef QUADTREE_H
#define QUADTREE_H
#include "include_lib.h"
#include "physic.h"
int bonus_counter;
extern struct Quad_Tree_Node* init_node(struct Quad_Tree_Node* root, int choice);
extern void draw_node(struct Quad_Tree_Node* node);
extern void draw_range(struct Ball* ball);
extern void draw_outline(struct Quad_Tree_Node* node);
extern bool contain(struct Quad_Tree_Node* node, struct Ball* ball);
extern bool contain_platform(struct Quad_Tree_Node* node, struct block* block);
extern bool contain_block(struct Quad_Tree_Node* node, struct block* block);
extern void free_node(struct Quad_Tree_Node* node);
extern void subdivide(struct Quad_Tree_Node* node, int levels, struct Ball* ball, struct block* platform, struct block** block,
                        ALLEGRO_SAMPLE* hit, ALLEGRO_SAMPLE* destroy);
extern void update(struct Quad_Tree_Node** root, struct Ball* ball, struct block* platform, struct block** block,
                         ALLEGRO_SAMPLE* hit, ALLEGRO_SAMPLE* destroy);
#endif // !QUADTREE_H
