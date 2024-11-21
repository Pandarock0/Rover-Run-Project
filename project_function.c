//
// Created by brian on 13/11/2024.
//

#include "project_function.h"
#include "random.h"
#include "loc.h"
#include "map.h"
#include "queue.h"
#include "moves.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>


#define TOTAL_MOVES 9




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
/*
    new_node->previous_node = NULL;
    return new_node;
*/

//allocation for the chosen movement corresponding to the node
    new_node->chosen_move = move_choose;

//allocation nb of available mvmts
    new_node->total_moves = nb_available_mvmt;

    return new_node;
}



/*void build_tree_recursively(t_node* root_node, int nb_available_mvmt, int* mvmt_list, int total_moves){


    //new_mvmt list
    for(int i=0; i<total_moves; i++){
        int* new_mvmt_list = (int*) malloc((nb_available_mvmt-1)*sizeof(int));
        int k = 0; //because for the iteration j it will be to big compare to the size of the new list

        for (int j=0; j<nb_available_mvmt; j++){
            if (j != i) {
                new_mvmt_list[k++] = mvmt_list[j];
            }
        }
        if (i != total_moves-1) {
            t_node *new_node = create_node((total_moves - 1), new_mvmt_list, 2, mvmt_list[i]);
            root_node->list_node[i] = new_node;
        }
        free(new_mvmt_list);
    }


    //recursive part of the function
    for (int i = 0; i < total_moves; i++) {
        if (root_node->list_node[i] != NULL) {

            build_tree_recursively(root_node->list_node[i], nb_available_mvmt - 1,
                                   root_node->list_node[i]->available_mvmt, total_moves - 1);
        }

    }
}
 */
void build_tree_recursively(t_node* root_node, int nb_available_mvmt, int* mvmt_list, int total_moves){


    //new_mvmt list
    for(int i=0; i<total_moves; i++){
        int* new_mvmt_list = (int*) malloc((nb_available_mvmt-1)*sizeof(int));
        int k = 0; //because for the iteration j it will be to big compare to the size of the new list

        for (int j=0; j<nb_available_mvmt; j++){
            if (j != i) {
                new_mvmt_list[k++] = mvmt_list[j];
            }
        }
        if (i != total_moves-1) {
            t_node *new_node = create_node((total_moves - 1), new_mvmt_list, 2, mvmt_list[i]);
            root_node->list_node[i] = new_node;
        }
        free(new_mvmt_list);
    }


    //recursive part of the function
    for (int i = 0; i < total_moves; i++) {
        if (root_node->list_node[i] != NULL) {
            build_tree_recursively(root_node->list_node[i], nb_available_mvmt - 1,
                                   root_node->list_node[i]->available_mvmt, total_moves - 1);
        }

    }
}


t_tree create_tree(int* mvmt_list){
    t_tree tree;

    tree.root_node = create_node(TOTAL_MOVES, mvmt_list, 999999999, 6);
    build_tree_recursively(tree.root_node, TOTAL_MOVES, mvmt_list, TOTAL_MOVES);

    return tree;
}

void display_tree(t_node* node, int depth) {

    if (node == NULL) {
        return;
    }

    printf("node --> [value:%d available_mvmt:[", node->value);
    for (int i = 0; i < node->total_moves; i++) {
        printf(" %d ", node->available_mvmt[i]);
    }
    printf("] node_list:[");
    for (int i = 0; i < node->total_moves; i++) {
        printf(" %p ", node->list_node[i]);
    }
    printf("] chosen_move:%d", node->chosen_move);

    printf("\n\n\nList of available movements for the node at level (depth): %d with chosen value %d : \n", (depth),
           node->chosen_move);

    for (int i = 0; i < node->total_moves; i++) {
        display_tree(node->list_node[i], depth + 1);

    }
}

/*
    for(int i=0; i<tree.root_node->total_moves; i++){
        printf("[");
        for(int j=0; j<tree.root_node->list_node[i]->total_moves; j++){
            printf("%d", tree.root_node->list_node[i]->available_mvmt[j]);
        }
        printf("] ");
    }
*/

