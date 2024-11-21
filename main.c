#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "random.h"
#include "map.h"

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

    //Random 9 movements and display
    srand(time(NULL));  // Initialize random seed

    // Run a demonstration of one phase
    printf("Executing a phase of 9 random moves:\n");
    int* moves = moveexecution();
    for (int i = 0; i<9; i++){
        printf("%d", moves[i]);
    }

    free(moves);
    return 0;
}