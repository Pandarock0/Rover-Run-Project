#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "project_function.h"



int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
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

    t_node** best_route_node = (t_node**)malloc(sizeof(t_node*));
    int size_temp = 0;
    t_node** best_route = Best_route_node(tree.root_node, &size_temp, NULL, best_route_node);
    int node_count = best_route[0]->depth;



    while (1) {

        int val;
        printf("Testing function :");
        printf("\n1.List of random movement\n2.Display some nodes of the tree (You need to stop the program)\n3.Display nodes located at the base\n4.Display all the movement to go to the base\n5.Display MARC displacement (test)\n6.Exit\n");
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

            t_node** best_route_node_list =  Best_route_node_list(best_route);
            display_best_move(best_route_node_list, node_count);

        }
        else if (val == 5) {
            displayMap_robot(map, test_function(), node_count);
        }
        else if (val == 6 || val != 1 || val != 2 || val != 3 || val !=4 || val != 5){
            break;
        }
    }

    return 0;
}

//comment test
