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
    menu();
    return 0;
}