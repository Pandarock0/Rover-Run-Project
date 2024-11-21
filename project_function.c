//
// Created by brian on 13/11/2024.
//

#include "project_function.h"
#include "loc.h"
#include "map.h"
#include "queue.h"
#include "moves.h"
#include <stdlib.h>
#include <stdio.h>
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
    /*for(int i=0; i<9; i++){
        printf("%d", moves[i]);
    }*/
    return moves;
}


//-------------------------------------------------------------------------------------------------------

typedef struct node{
    int value;
    int * available_mvmt;
    struct node** list_node;
    struct node* previous_node;
    int chosen_move;


}t_node;

typedef struct s_tree{
    t_node* root_node;
}t_tree;

t_node* create_node(int nb_available_mvmt, int* mvmt_list, int value, int move_choose){

    t_node* new_node = (t_node*) malloc(sizeof(t_node));

//allocation for the value
    new_node->value = value;

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

//memory alocation for previous_node
    new_node->previous_node = NULL;
    return new_node;

//allocation for the chosen movement corresponding to the node
    new_node->chosen_move = move_choose;
}


t_tree create_tree(int* mvmt_list){
    t_tree tree;
    //int* mvmt_list = moveexecution();
    tree.root_node = create_node(TOTAL_MOVES, mvmt_list, 2, 00000);
    return tree;
}


void build_tree_recursively(t_node* root_node, int nb_available_mvmt, int* mvmt_list, int move_choose, int total_moves){


    //new_mvmt list
    for(int i=0; i<total_moves; i++){
        int* new_mvmt_list = (int*) malloc((nb_available_mvmt-1)*sizeof(int));
        int k = 0; //because for the iteration j it will be to big compare to the size of the new list

        for (int j=0; j<nb_available_mvmt; j++){
            if (j != i) {
                new_mvmt_list[k++] = mvmt_list[j];
            }
        }
        if (i != total_moves) {
            t_node *new_node = create_node((total_moves - 1), new_mvmt_list, 2, mvmt_list[i]);
            root_node->list_node[i] = new_node;
        }
        free(new_mvmt_list);
    }


    //recursive part of the function
    for (int i = 0; i < total_moves; i++) {
        if (root_node->list_node[i] != NULL) {

            build_tree_recursively(root_node->list_node[i], nb_available_mvmt - 1,
                                   root_node->list_node[i]->available_mvmt,
                                   root_node->list_node[i]->chosen_move, total_moves - 1);
        }

    }
}
/*
void add_node_tree(t_tree tree_root, int* mvmt_list){
    total_moves = TOTAL_MOVES;
    int chosen_move;
    for(int i=0; i<TOTAL_MOVES; i++){
        chosen_move = mvmt_list[i];
        for (int i=0; i< total_moves; i++){
            if (total_moves[i] == chosen_move){
                total_moves--;

            }
        }
        tree_root.root_node->list_node[i] = create_node(total_moves,)
    }

}

