#include <stdio.h>
#include <stdlib.h>
#include "moves.h"
#include "random.h"

#define TOTAL_MOVES 9



int initial_availability[] = {22, 15, 7, 7, 21, 21, 7};

int current_availability[7];

void resetCount() {
    for (int i = 0; i < 7; i++) {
        current_availability[i] = initial_availability[i];
    }
}

tmove selectRandomMove() {
    int move;
    while (1) {
        move = rand() % 7;  // Randomly choose one of the 7 moves
        if (current_availability[move] > 0) {
            current_availability[move]--;  // Reduce the count of this move
            return (t_move)move;           // Return the selected move
        }
    }
}

void moveexecution (){
    resetCount();  // Reset moves at the beginning of each phase

    for (int i = 0; i < TOTAL_MOVES; i++) {
        tmove chosen_move = selectRandomMove();

        // Display the chosen move for demonstration purposes
        switch (chosen_move) {
            case For_10:   printf("Move forward 10 m\n"); break;
            case For_20:   printf("Move forward 20 m\n"); break;
            case For_30:   printf("Move forward 30 m\n"); break;
            case Back_10:   printf("Reverse 10 m\n"); break;
            case Turn_LEFT: printf("Turn left 90 degrees\n"); break;
            case Turn_RIGHT:printf("Turn right 90 degrees\n"); break;
            case U_Turn: printf("Turn back 180 degrees\n"); break;
        }
    }
}