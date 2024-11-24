//
// Created by Carouge on 24/11/2024.
//

#ifndef UNTITLED1_FUNCTIONS_ABDOU_H
#define UNTITLED1_FUNCTIONS_ABDOU_H

#include "project_function.h"


typedef struct{
    t_tree* path;
    int length;
    int weight;

}Route;

void findMinimumRoute(t_node *node, t_tree *currentPath, int currentWeight, int currentLength, Route *bestRoute);

Route minimum_route(t_tree tree);

t_node *copy_node(t_node* );



#endif //UNTITLED1_FUNCTIONS_ABDOU_H
