//
// Created by brian on 13/11/2024.
//

#ifndef UNTITLED1_PROJECT_FUNCTION_H
#define UNTITLED1_PROJECT_FUNCTION_H


#include "loc.h"
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

    //map parameters
    int value_cost;
    int exit_condition;
    t_map map;
    t_localisation localisation;
    int base_station;

} t_node;

typedef struct s_tree{
    t_node* root_node;
} t_tree;

typedef struct{
    t_tree* path;
    int length;
    int weight;

}Route;

void findMinimumRoute(t_node *node, t_tree *currentPath, int currentWeight, int currentLength, Route *bestRoute);

Route minimum_route(t_tree tree);

t_node *copy_node(t_node* );


t_node* create_node(int depth, int* mvmt_list, int move_choose, int nb_available_mvmt, t_node* previous_node);

t_tree create_tree(int* mvmt_list, t_map);

void build_tree_recursively(t_node* root_node, int nb_available_mvmt, int* mvmt_list, int total_moves);

void display_tree(t_node* node); //test function

int update_loc(t_node* current_node);

int calculate_cost(t_node*);

void print_base_station_nodes(t_node* node);

int at_the_base_station(t_node* current_node);

t_node** test_function();

//create by Brian DON'T put in map.c
void displayMap_robot(t_map, t_node**, int);

void display_best_move(t_node**, int);
t_node** tree_to_node_array(t_tree* tree);

//t_queue list_position(t_node* node);
//t_stack node_stack_list(t_node* node);

#endif //UNTITLED1_PROJECT_FUNCTION_H
