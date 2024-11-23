//
// Created by brian on 13/11/2024.
//

#ifndef UNTITLED1_PROJECT_FUNCTION_H
#define UNTITLED1_PROJECT_FUNCTION_H

#include "moves.h"
#include "map.h"

void resetCount();
int* moveexecution();
t_move selectRandomMove();

typedef struct node{

    int * available_mvmt;
    struct node** list_node;
    struct node* previous_node;
    int total_moves;
    int chosen_move;
    int depth;
    int exit_condition;
    //map parameters
    int value_cost;
    t_map map;
    t_localisation localisation;

} t_node;

typedef struct s_tree{
    t_node* root_node;
} t_tree;

t_node* create_node(int depth, int* mvmt_list, int value, int move_choose, int nb_available_mvmt, t_node* previous_node);

t_tree create_tree(int* mvmt_list);
/*
node** minimal_route(tree);
*/



#endif //UNTITLED1_PROJECT_FUNCTION_H