//
// Created by brian on 13/11/2024.
//

#include "project_function.h"
#include "loc.h"
#include "map.h"
#include "moves.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



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

t_map choose_map() {
    printf("Choose a map to load:\n");
    printf("1. example1.map\n");
    printf("2. training.map\n");
    printf("3. projectmap.map\n");
    printf("4. Other map\n");
    int mapchoice;
    t_map map;
    scanf("%d", &mapchoice);
    switch (mapchoice) {
        case 1: {
            map = createMapFromFile("..\\maps\\example1.map");
            printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
            for (int i = 0; i < map.y_max; i++) {
                for (int j = 0; j < map.x_max; j++) {
                    printf("%d ", map.soils[i][j]);
                }
                printf("\n");
            }
            // printf the costs, aligned left 5 digits
            for (int i = 0; i < map.y_max; i++) {
                for (int j = 0; j < map.x_max; j++) {
                    printf("%-5d ", map.costs[i][j]);
                }
                printf("\n");
            }
            displayMap(map);
            break;
        }

        case 2: {
            map = createMapFromFile("..\\maps\\training.map");
            printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
            for (int i = 0; i < map.y_max; i++) {
                for (int j = 0; j < map.x_max; j++) {
                    printf("%d ", map.soils[i][j]);
                }
                printf("\n");
            }
            // printf the costs, aligned left 5 digits
            for (int i = 0; i < map.y_max; i++) {
                for (int j = 0; j < map.x_max; j++) {
                    printf("%-5d ", map.costs[i][j]);
                }
                printf("\n");
            }
            displayMap(map);
            break;
        }

        case 3: {
            map = createMapFromFile("..\\maps\\test.map");
            printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
            for (int i = 0; i < map.y_max; i++) {
                for (int j = 0; j < map.x_max; j++) {
                    printf("%d ", map.soils[i][j]);
                }
                printf("\n");
            }
            // printf the costs, aligned left 5 digits
            for (int i = 0; i < map.y_max; i++) {
                for (int j = 0; j < map.x_max; j++) {
                    printf("%-5d ", map.costs[i][j]);
                }
                printf("\n");
            }
            displayMap(map);
            break;
        }

        case 4: {
            printf("Enter the exact name of the map you want to load:\n");
            char name[100];
            scanf("%s", name);
            char path[100] = "..\\\\maps\\\\";
            strcat(path, name);
            char finalpath[100] = ".map";
            strcat(path, finalpath);
            printf("%s \n", path);
            map = createMapFromFile(path);
            printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
            for (int i = 0; i < map.y_max; i++) {
                for (int j = 0; j < map.x_max; j++) {
                    printf("%d ", map.soils[i][j]);
                }
                printf("\n");
            }
            // printf the costs, aligned left 5 digits
            for (int i = 0; i < map.y_max; i++) {
                for (int j = 0; j < map.x_max; j++) {
                    printf("%-5d ", map.costs[i][j]);
                }
                printf("\n");
            }
            displayMap(map);
        }
            break;

    }
    return map;
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
    cost = current_node->map.costs[y][x]+(current_node->previous_node->value_cost); //Don't do a mistake with x and y

    return cost;
}

int at_the_base_station(t_node* current_node) {
    int x = current_node->localisation.pos.x;
    int y = current_node->localisation.pos.y;

    //Ensure that MARC is not out of the map
    if (x >= 0 && x < current_node->map.x_max && y >= 0 && y < current_node->map.y_max) {
        if (current_node->map.soils[y][x] == BASE_STATION) { //Don't do a mistake with x and y
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
            int *new_mvmt_list = (int*) malloc((nb_available_mvmt - 1) * sizeof(int));
            int k = 0; //because for the iteration j it will be to big compare to the size of the new list

            for (int j = 0; j < nb_available_mvmt; j++) {
                if (j != i) {
                    new_mvmt_list[k++] = mvmt_list[j];
                }
            }
            t_node *new_node = create_node(depth + 1, new_mvmt_list, mvmt_list[i], nb_available_mvmt - 1, root_node);
            if ((new_node->value_cost >= 10000) || (new_node->exit_condition == 0) /*|| new_node->base_station == 1*/) {
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

t_node** test_function(){
    t_node** list_node = (t_node**) malloc(sizeof(t_node*));
    list_node[0] = (t_node*) malloc(sizeof(t_node));
    list_node[1] = (t_node*) malloc(sizeof(t_node));
    list_node[2] = (t_node*) malloc(sizeof(t_node));

    list_node[0]->localisation = loc_init(3, 3, NORTH);
    list_node[1]->localisation = loc_init(3, 4, WEST);
    list_node[2]->localisation = loc_init(3, 5, SOUTH);
    return list_node;
}

void displayMap_robot(t_map map, t_node** nodes, int node_count) {

    //display the map with robot node_count times
    for (int i = 0; i < node_count; i++) {
        for (int j=0; j<map.y_max; j++) {
            for (int k=0; k<map.x_max; k++) {
                if (nodes[i]->localisation.pos.x == k && nodes[i]->localisation.pos.y == j) {
                    switch (nodes[i]->localisation.ori) {
                        case NORTH:
                            printf(" ^ ");
                            break;
                        case EAST:
                            printf(" > ");
                            break;
                        case SOUTH:
                            printf(" v ");
                            break;
                        case WEST:
                            printf(" < ");
                            break;
                        default:
                            printf(" ? ");
                            break;
                    }
                }

                else {
                    switch (map.soils[j][k]) {
                        case BASE_STATION:
                            printf(" X ");
                        break;
                        case PLAIN :
                            printf(" . ");
                        break;
                        case ERG :
                            printf(" ~ ");
                        break;
                        case REG :
                            printf(" * ");
                        break;
                        case CREVASSE :
                            printf("   ");
                        break;
                        default:
                            printf(" ? ");
                        break;
                    }
                }
            }
            printf("\n");
        }
        printf("\n\n\n");
    }
}

void display_best_move(t_node** node_list, int node_count) {
    for (int i = 0; i < node_count; i++) {
        switch ((t_move)node_list[i]->chosen_move) {
            case F_10:
                printf("Forward 10m\n");
                break;
            case F_20:
                printf("Forward 20m\n");
                break;
            case F_30:
                printf("Forward 30m\n");
                break;
            case B_10:
                printf("Back 10m\n");
                break;
            case T_LEFT:
                printf("Turn left\n");
                break;
            case T_RIGHT:
                printf("Turn right\n");
                break;
            case U_TURN:
                printf("Turn back\n");
                break;
            default:
                printf("No existing movement\n");
                break;
        }
    }
}


//Abdou Part-----------------------------------------------------------------------------------------------------
t_node *copy_node(t_node *src) {
    if (!src) {
        return NULL;
    }
    t_node *copy = (t_node *)malloc(sizeof(t_node));

    memcpy(copy, src, sizeof(t_node));
    copy->available_mvmt = NULL;
    copy->list_node = NULL;
    copy->previous_node = NULL;
    return copy;
}

// Recursive function to find the minimum route
void findMinimumRoute(t_node *node, t_tree *currentPath, int currentWeight, int currentLength, Route *bestRoute)
{
    if (!node) {
        return;
    }

    // Add the node's value to the current weight
    currentWeight += node->value_cost;

    // add the current node to degenerate tree path
    t_node *copiedNode = copy_node(node);
    if (currentPath->root_node == NULL) {
        currentPath->root_node = copiedNode;
    } else {
        t_node *temp = currentPath->root_node;
        while (temp->list_node && temp->list_node[0]) {
            temp = temp->list_node[0];
        }
        temp->list_node = (t_node **)malloc(sizeof(t_node *));
        temp->list_node[0] = copiedNode;
    }

    currentLength++;

    // If weight exceeds the best route's weight, abort the mission soldier ! Abort the mission !
    if (currentWeight >= bestRoute->weight) {
        free(copiedNode);
        return;
    }

    // If this is a leaf node or the node has value 1, check if the path is the best
    if ((node->total_moves == 0 || node->value_cost == 1) && node!=currentPath->root_node) {
        if (currentWeight < bestRoute->weight) {
            // Update the best route
            bestRoute->weight = currentWeight;
            bestRoute->length = currentLength;

            // delete existing best path to search for a better one
            if (bestRoute->path) {
                free(bestRoute->path);
            }

            // Copy the current path to the best path
            bestRoute->path = (t_tree *)malloc(sizeof(t_tree));
            bestRoute->path->root_node = copy_node(currentPath->root_node);
        }
        return;
    }

    // traverse each child
    for (int i = 0; i < node->total_moves; i++) {
        findMinimumRoute(node->list_node[i], currentPath, currentWeight, currentLength, bestRoute);
    }

    // Backtrack: Remove the last node from the current patht to check for a better one
    if (currentPath->root_node) {
        t_node *temp = currentPath->root_node;
        t_node *prev = NULL;
        while (temp->list_node && temp->list_node[0]) {
            prev = temp;
            temp = temp->list_node[0];
        }
        if (prev) {
            free(temp);
            free(prev->list_node);
            prev->list_node = NULL;
        } else {
            free(currentPath->root_node);
            currentPath->root_node = NULL;
        }
    }
}

// Main function to find minimum route in tree
Route minimum_route(t_tree tree) {
    if (tree.root_node == NULL) {
        // If tree empty, return empty route
        Route emptyRoute = {NULL, 0, 0};
        return emptyRoute;
    }

    // Initialize best route
    Route bestRoute;
    bestRoute.path = NULL;
    bestRoute.weight = 100000000;
    bestRoute.length = 0;

    // Temporary path for recursion
    t_tree *currentPath = (t_tree *)malloc(sizeof(t_tree));
    currentPath->root_node = NULL;

    // Start recursive search
    findMinimumRoute(tree.root_node, currentPath, 0, 0, &bestRoute);

    // Free temporary path memory
    free(currentPath);

    return bestRoute;
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


