//
// Created by Carouge on 24/11/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "Functions_abdou.h"

//src for source as in original
t_node *copy_node(t_node *src) {
    if (!src) {
        return NULL;
    }
    t_node *copy = (t_node *)malloc(sizeof(t_node));

    memcpy(copy, src, sizeof(t_node));
    copy->available_mvmt = NULL;
    copy->list_node = NULL;
    copy->previous_node = NULL;
    return copy;
}

// Recursive function to find the minimum route
void findMinimumRoute(t_node *node, t_tree *currentPath, int currentWeight, int currentLength, Route *bestRoute)
{
    if (!node) {
        return;
    }

    // Add the node's value to the current weight
    currentWeight += node->value_cost;

    // add the current node to degenerate tree path
    t_node *copiedNode = copy_node(node);
    if (currentPath->root_node == NULL) {
        currentPath->root_node = copiedNode;
    } else {
        t_node *temp = currentPath->root_node;
        while (temp->list_node && temp->list_node[0]) {
            temp = temp->list_node[0];
        }
        temp->list_node = (t_node **)malloc(sizeof(t_node *));
        temp->list_node[0] = copiedNode;
    }

    currentLength++;

    // If weight exceeds the best route's weight, abort the mission soldier ! Abort the mission !
    if (currentWeight >= bestRoute->weight) {
        free(copiedNode);
        return;
    }

    // If this is a leaf node or the node has value 1, check if the path is the best
    if (node->total_moves == 0 || node->value_cost == 1) {
        if (currentWeight < bestRoute->weight) {
            // Update the best route
            bestRoute->weight = currentWeight;
            bestRoute->length = currentLength;

            // delete existing best path to search for a better one
            if (bestRoute->path) {
                free(bestRoute->path);
            }

            // Copy the current path to the best path
            bestRoute->path = (t_tree *)malloc(sizeof(t_tree));
            bestRoute->path->root_node = copy_node(currentPath->root_node);
        }
        return;
    }

    // traverse each child
    for (int i = 0; i < node->total_moves; i++) {
        findMinimumRoute(node->list_node[i], currentPath, currentWeight, currentLength, bestRoute);
    }

    // Backtrack: Remove the last node from the current patht to check for a better one
    if (currentPath->root_node) {
        t_node *temp = currentPath->root_node;
        t_node *prev = NULL;
        while (temp->list_node && temp->list_node[0]) {
            prev = temp;
            temp = temp->list_node[0];
        }
        if (prev) {
            free(temp);
            free(prev->list_node);
            prev->list_node = NULL;
        } else {
            free(currentPath->root_node);
            currentPath->root_node = NULL;
        }
    }
}

// Main function to find minimum route in tree
Route minimum_route(t_tree tree) {
    if (tree.root_node == NULL) {
        // If tree empty, return empty route
        Route emptyRoute = {NULL, 0, 0};
        return emptyRoute;
    }

    // Initialize best route
    Route bestRoute;
    bestRoute.path = NULL;
    bestRoute.weight = 100000000;
    bestRoute.length = 0;

    // Temporary path for recursion
    t_tree *currentPath = (t_tree *)malloc(sizeof(t_tree));
    currentPath->root_node = NULL;

    // Start recursive search
    findMinimumRoute(tree.root_node, currentPath, 0, 0, &bestRoute);

    // Free temporary path memory
    free(currentPath);

    return bestRoute;
}
