#include <stdio.h>
#include "map.h"
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

    //function test part


    srand(time(NULL));
    int* list_mvmt = moveexecution();

    t_tree tree = create_tree(list_mvmt);

    display_tree(tree.root_node);

    /*
    for(int i=0; i<9;i++){
        printf("%d", list_mvmt[i]);
    }
    */ // Test for random mouvements list

    return 0;
}
