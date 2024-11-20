//
// Created by abdel on 13/11/2024.
//

#ifndef ROVER_RUN_PROJECT_RANDOM_H
#define ROVER_RUN_PROJECT_RANDOM_H

typedef enum {
    For_10,
    For_20,
    For_30,
    Back_10,
    Turn_LEFT,
    Turn_RIGHT,
    U_Turn,
} tmove;

void resetCount();
tmove selectRandomMove();
void moveexecution ();

#endif //ROVER_RUN_PROJECT_RANDOM_H
