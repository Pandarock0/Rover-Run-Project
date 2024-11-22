#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "random.h"
#include "map.h"
#include "project_function.h"

void menu(){
    printf("1. Choose the map of your choice for the rover\n");
    printf("2. Execute a phase of 9 random moves\n");

    printf(". Exit\n");
    int choice;
    t_map map;
    int* moves;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            map = choose_map();
            break;

        case 2:
            moves = moveexecution();
            for (int i = 0; i < 9; i++) {
                printf("%d", moves[i]);
            }
            break;
    }
}


int main() {
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

    //Random 9 movements and display
    srand(time(NULL));  // Initialize random seed

    // Run a demonstration of one phase
    printf("Executing a phase of 9 random moves:\n");
    int* moves = moveexecution();
    for (int i = 0; i<9; i++){
        printf("%d", moves[i]);
    }

    free(moves);*/
    menu();

    return 0;
}