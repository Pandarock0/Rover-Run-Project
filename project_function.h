//
// Created by brian on 13/11/2024.
//

#ifndef UNTITLED1_PROJECT_FUNCTION_H
#define UNTITLED1_PROJECT_FUNCTION_H

#include "moves.h"

void resetCount();
int* moveexecution();
t_move selectRandomMove();

typedef struct node{
    int value;
    int * available_mvmt;
    struct node** list_node;
    // struct node* previous_node;
    int total_moves;
    int chosen_move;
    int depth;

    //map parameters
    int cost;
    t_localisation localisation;

} t_node;

typedef struct s_tree{
    t_node* root_node;
} t_tree;

t_node* create_node(int depth, int* mvmt_list, int value, int move_choose, int nb_available_mvmt);

t_tree create_tree(int* mvmt_list);

void build_tree_recursively(t_node* root_node, int nb_available_mvmt, int* mvmt_list, int total_moves);

void display_tree(t_node* node); //test function




#endif //UNTITLED1_PROJECT_FUNCTION_H
