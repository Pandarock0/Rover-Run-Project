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

