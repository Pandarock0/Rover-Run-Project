//
// Created by Carouge on 01/11/2024.
//


#ifndef MARC_MASTER__1__RANDOM_H
#define MARC_MASTER__1__RANDOM_H

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



#endif //MARC_MASTER__1__RANDOM_H
