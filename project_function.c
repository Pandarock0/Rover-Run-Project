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
#include <string.h>


#define TOTAL_MOVES 9




//-------------------------------------------------------------------------------------------------------

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

t_node* create_node(int depth, int* mvmt_list, int value, int move_choose, int nb_available_mvmt, t_node* previous_node){

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

t_map choose_map (){
    printf("Choose a map to load:\n");
    printf("1. example1.map\n");
    printf("2. training.map\n");
    printf("3. projectmap.map\n");
    printf("4. Other map\n");
    int mapchoice;
    t_map map;
    scanf("%d", &mapchoice);
    switch (mapchoice){
        case 1:
            map = createMapFromFile("..\\maps\\example1.map");
            displayMap(map);
            break;
        case 2:
            map = createMapFromFile("..\\maps\\training.map");
            displayMap(map);
            break;
        case 3:
            map = createMapFromFile("..\\maps\\projectmap.map");
            displayMap(map);
            break;
        case 4:
            printf("Enter the exact name of the map you want to load:\n");
            char name[100];
            scanf("%s", name);
            char path[100] = "..\\\\maps\\\\";
            strcat(path, name);
            char finalpath[100] = ".map";
            strcat(path, finalpath);
            printf ("%s", path);
            break;
    }
    return map;
}

//pseudo code while waiting for tree function
/*
node** minimal_route(tree){// This function will test each combination of routes using the 5 moves then keep the lowest wieghed one

    node** all_route[126]; // 9 among 5 is 126 each element is a route from root to leaf
    for (int a=0; a<9;a++)
    {
        all_route[a]=create_tree(tree->*children[a])
        for(int b=0; b<8;b++)
        {
            all_route[a] = add_leaf(all_route[a],
            for(int c=0; c<7; c++)
            {
                for(int c=0; c<6;c++)
                {
                    for(int d=0; d<5;d++)
                    {
                        for(int e=0;e<4;e++)
                        {
                            for(int f=0; f=3;f++)
                            {
                                for(int g=0; g<2;g++)
                                {
                                    for(int h=0;h<1;h++)
                                    {

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}*/
