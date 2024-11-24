#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "project_function.h"
#include "map.h"



void menu(){
    printf("1. Choose the map of your choice for the rover\n");
    printf("2. Execute a phase of 9 random moves\n");
    printf("3. Display nodes of the tree (you need to stop the program)\n");
    printf("4. Display nodes located at the base\n");
    printf("5. Display MARC displacement (test)\n");
    printf("Else: Exit\n");
    int choice, cost;
    t_map map = createTrainingMap();
    t_tree tree;
    int* moves;
    srand(time(NULL));
    int *list_mvmt = moveexecution();
    Route route;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            choose_map();
            menu();
            break;

        case 2:
            printf("\n[");
            moves = moveexecution();
            for (int i = 0; i < 9; i++) {
                printf("%d", moves[i]);
            }
            printf("]\n");
            menu();
            break;

        case 3:
            tree = create_tree(moveexecution(), map);
            display_tree(tree.root_node);
            menu();
            break;


        case 4:
            tree = create_tree(moveexecution(), map);
            print_base_station_nodes(tree.root_node);
            menu();
            break;
        case 5:
            displayMap_robot(map, test_function(), 3);
            menu();
            break;

        case 6:
            // how can we display the best route?
            tree = create_tree(list_mvmt, map);
            route = minimum_route(tree);
            printf("The best route is %d", route.length);
            menu();
            break;
        default:
            break;

    }
}



int main() {
    menu();
    return 0;
}