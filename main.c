#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "project_function.h"
#include "stack.h"


void menu(){
    printf("1. Choose the map of your choice for the rover\n");
    printf("2. Execute a phase of 9 random moves\n");
    printf("3. Display the tree\n");
    printf("4. Display the costs\n");
    printf("5. Complete ");




    printf(". Exit\n");
    int choice, cost;
    t_map map;
    t_tree tree;
    int* moves;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            choose_map();
            menu();
            break;

        case 2:
            moves = moveexecution();
            for (int i = 0; i < 9; i++) {
                printf("%d", moves[i]);
            }
            menu();
            break;

        case 3:
            tree = create_tree(moveexecution());
            display_tree(tree.root_node);
            menu();
            break;

        case 4:
            tree = create_tree(moveexecution());
            printf("The cost of the path is %d\n", cost = calculate_cost(tree.root_node));
            menu();
            break;
    }
}





int main() {
    menu();
    return 0;
}