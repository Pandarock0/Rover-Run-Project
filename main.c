#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "project_function.h"

void menu(){
    printf("1. Choose the map of your choice for the rover\n");
    printf("2. Execute a phase of 9 random moves\n");
    printf("3. Display nodes of the tree (you need to stop the program)\n");
    printf("4. Display the costs\n");
    printf("5. Display nodes located at the base\n");
    printf("6. Display MARC displacement (test)\n");
    printf(". Complete ");




    printf(". Exit\n");
    int choice, cost;
    t_map map = createTrainingMap();
    t_tree tree;
    int* moves;
    srand(time(NULL));
    int *list_mvmt = moveexecution();
    Route route = minimum_route(tree);
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
            cost = calculate_cost(tree.root_node);
            printf("The cost of the path is %d\n", &cost);
            menu();
            break;

        case 5:
            tree = create_tree(moveexecution(), map);
            print_base_station_nodes(tree.root_node);
            break;
        case 6:
            display_best_move(test_function(), 3);
            menu();
    }
}



int main() {
    menu();

    /*t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);



    srand(time(NULL));
    int *list_mvmt = moveexecution();
    //map = createTrainingMap();

    t_tree tree = create_tree(list_mvmt, map);
    Route route = minimum_route(tree);


    while (1) {

        int val;
        printf("Testing function :");
        printf("\n1.List of random movement\n2.Display some nodes of the tree (You need to stop the program)\n3.Display nodes located at the base\n4.Display MARC displacement (test)\n5.Exit\n");
        scanf("%d", &val);
        if (val == 1){
            printf("\n[");
            for(int i=0; i<9; i++){
                printf(" %d ", list_mvmt[i]);
            }
            printf("]\n");
        }
        else if (val == 2){
            display_tree(tree.root_node);
        }
        else if (val == 3){
            print_base_station_nodes(tree.root_node);
        }
        else if (val == 4){
            displayMap_robot(map, test_function(), 3);
        }
        else if (val == 5) {
            display_best_move(test_function(), 3);
        }
        else if (val == 6){
            minimum_route(tree);
        }
    }
*/
    return 0;
}
