//
// Created by brian on 13/11/2024.
//

#include "project_function.h"
#include "loc.h"
#include "map.h"
#include "queue.h"
#include "moves.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


#define TOTAL_MOVES 9


int initial_availability[] = {22, 15, 7, 7, 21, 21, 7};

int current_availability[7];

void resetCount() {
    for (int i = 0; i < 7; i++) {
        current_availability[i] = initial_availability[i];
    }
}

t_move selectRandomMove() {
    int move;

    while (1) {
        move = rand() % 7;  // Randomly choose one of the 7 moves
        if (current_availability[move] > 0) {
            current_availability[move]--;  // Reduce the count of this move
            return (t_move)move;           // Return the selected move
        }
    }
}

int* moveexecution() {

    resetCount();  // Reset moves at the beginning of each phase
    int* moves = (int*) malloc(TOTAL_MOVES*sizeof(int));
    for (int i = 0; i < TOTAL_MOVES; i++) {
        t_move chosen_move = selectRandomMove();

        // Display the chosen move for demonstration purposes
        switch (chosen_move) {
            case F_10: moves[i]=0;
                break;
            case F_20: moves[i]=1;
                break;
            case F_30: moves[i]=2;
                break;
            case B_10:   moves[i]=3;
                break;
            case T_LEFT: moves[i]=4;
                break;
            case T_RIGHT: moves[i]=5;
                break;
            case U_TURN: moves[i]=6;
                break;
        }
    }

    return moves;
}


//-------------------------------------------------------------------------------------------------------


t_node* create_node(int depth, int* mvmt_list, int move_choose, int nb_available_mvmt, t_node* previous_node){

    t_node* new_node = (t_node*) malloc(sizeof(t_node));

//allocation for previous node
    new_node->previous_node = previous_node;

//allocation for available_mvmt
    new_node->available_mvmt = (int*) malloc(nb_available_mvmt * sizeof(int));
    for (int i=0; i<nb_available_mvmt; i++){
        new_node->available_mvmt[i] = mvmt_list[i];
    }

//allocation for list_node
    new_node->list_node = (t_node**) malloc(nb_available_mvmt*sizeof(t_node*));
    for(int i=0; i<nb_available_mvmt; i++){
        new_node->list_node[i] = NULL;
    }

//allocation for the chosen movement corresponding to the node
    new_node->chosen_move = move_choose;

//allocation nb of available mvmts
    new_node->total_moves = nb_available_mvmt;

//allocation of the corresponding level
    new_node->depth = depth;

//allocation of the localisation and cost_value
    int exit = update_loc(new_node); //update map and new_localisation (not the real of the robot)
    new_node->exit_condition = exit;
    if (exit == 1) {
        new_node->value_cost = calculate_cost(new_node);
    }
    new_node->base_station = at_the_base_station(new_node);
    return new_node;
}

int update_loc(t_node* current_node){
   int approve;
   t_move chosen_move = (t_move)current_node->chosen_move;


   if (current_node->previous_node != NULL) {

       current_node->localisation = move(current_node->previous_node->localisation, chosen_move); //update localisation
       current_node->map = current_node->previous_node->map;

   } //for the root node, updated in the create tree function
   int y_max = current_node->map.y_max, x_max = current_node->map.y_max; //Border of the map
   approve = isValidLocalisation(current_node->localisation.pos, x_max, y_max);

   return approve;

}

int calculate_cost(t_node* current_node){
    int cost;
    int x = current_node->localisation.pos.x, y = current_node->localisation.pos.y;
    cost = current_node->map.costs[x][y]+(current_node->previous_node->value_cost);

    return cost;
}

int at_the_base_station(t_node* current_node) {
    int x = current_node->localisation.pos.x;
    int y = current_node->localisation.pos.y;

    //Ensure that MARC is not out of the map
    if (x >= 0 && x < current_node->map.x_max && y >= 0 && y < current_node->map.y_max) {
        if (current_node->map.soils[x][y] == BASE_STATION) {
            return 1;
        }
    }
    return 0;
}

//function work like a postfix tree allocation
void build_tree_recursively(t_node* root_node, int nb_available_mvmt, int* mvmt_list, int depth){
    if (depth >= 5) {
        return;
    }

    if (depth <= 5) {
        //new_mvmt list
        for (int i = 0; i < nb_available_mvmt; i++) {
            int *new_mvmt_list = (int *) malloc((nb_available_mvmt - 1) * sizeof(int));
            int k = 0; //because for the iteration j it will be to big compare to the size of the new list

            for (int j = 0; j < nb_available_mvmt; j++) {
                if (j != i) {
                    new_mvmt_list[k++] = mvmt_list[j];
                }
            }
            t_node *new_node = create_node(depth + 1, new_mvmt_list, mvmt_list[i], nb_available_mvmt - 1, root_node);
            if (new_node->value_cost >= 10000 || new_node->exit_condition == 0 /*|| new_node->base_station == 1*/) {
                root_node->list_node[i] = NULL;
            }
            /*else if (new_node->base_station == 1) {

                new_node->list_node = NULL;
                root_node->list_node[i] = new_node;

            }*/
            else {
                root_node->list_node[i] = new_node;
            }
            free(new_mvmt_list);
        }
    }
    else {
        return;
    }

    //recursive part of the function
    for (int i = 0; i < nb_available_mvmt; i++) {
        if (root_node->list_node[i] != NULL) {
            build_tree_recursively(root_node->list_node[i], nb_available_mvmt - 1,
                                   root_node->list_node[i]->available_mvmt, depth + 1);
        }

    }
}


t_tree create_tree(int* mvmt_list, t_map map){
    t_tree tree;
    //initialisation of the root
    tree.root_node = create_node(0, mvmt_list, 9999999, TOTAL_MOVES, NULL);
    tree.root_node->localisation = loc_init(3, 3, NORTH);
    tree.root_node->value_cost = 0;
    tree.root_node->map = map; //temporary map


    build_tree_recursively(tree.root_node, TOTAL_MOVES, mvmt_list, 0);

    return tree;
}

void display_tree(t_node* node) {
    if (node == NULL) {
        return;
    }

    //informations of the nodes
    printf("Node:\n");
    printf("  Depth        : %d\n", node->depth);
    printf("  Chosen Move  : %d\n", node->chosen_move);
    printf("  Total Moves  : %d\n", node->total_moves);
    printf("  Cost of the pixel : %d\n", node->value_cost);
    printf("  At the base station ? : ");
    if (node->base_station == 1) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    printf("  Available Mvmt: ");
    for (int i = 0; i < node->total_moves; i++) {
        printf("%d ", node->available_mvmt[i]);
    }
    printf("\n");
    printf("  Next nodes addresses : [");
    for (int i=0; i< node->total_moves; i++){
        printf("%p ", node->list_node[i]);
    }
    printf("]\n\n\n");

    //address of children node
    for (int i = 0; i < node->total_moves; i++) {
        if (node->list_node[i] != NULL) {
            display_tree(node->list_node[i]);
        }
    }
}



void print_base_station_nodes(t_node* node) {
    if (node == NULL) {
        return;
    }

    // Check if the current node is at the base station
    if (node->base_station == 1) {
        printf("Node at base station:\n");
        printf("  Depth        : %d\n", node->depth);
        printf("  Chosen Move  : %d\n", node->chosen_move);
        printf("  Total Moves  : %d\n", node->total_moves);
        printf("  Cost of the pixel : %d\n", node->value_cost);
        printf("  Available Mvmt: ");
        for (int i = 0; i < node->total_moves; i++) {
            printf("%d ", node->available_mvmt[i]);
        }
        printf("\n");
    }

    // Recursively check children nodes
    for (int i = 0; i < node->total_moves; i++) {
        if (node->list_node[i] != NULL) {
            print_base_station_nodes(node->list_node[i]);
        }
    }
}
/*
//give all the position from the last to the first node
t_queue list_position(t_node* node){
    int iteration = node->depth;
    t_node* curr = node;
    t_queue queue = createQueue(iteration);

    for (int i=0; i<iteration; i++){
        enqueue(&queue, curr->localisation.pos);
        curr = curr->previous_node;
    }
    return queue;
}
*/

/*
//give the list of nodes before a node in a stack to have the localisation in order
t_stack node_stack_list(t_node* node){
    t_stack stack_list = createStack(node->depth);
    t_node* temp = node;

    for(int i=0; i<node->depth; i++){
        push(&stack_list, temp);
        temp = temp->previous_node;
    }
}
*/


