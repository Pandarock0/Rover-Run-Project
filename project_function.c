//
// Created by brian on 13/11/2024.
//

#include "project_function.h"
#include "loc.h"
#include "map.h"
#include "queue.h"
#include "moves.h"

typedef struct node {
    int value;
    struct node* parent_node;
    struct node** children;
    int num_children;

    t_move* available_moves;
    int num_available_moves;

    t_move move_from_parent;

} node;



//pseudo code while waiting for tree function

node** minimal_route(tree){// This function will test each combination of routes using the 5 moves then keep the lowest wieghed one

    node** all_route[126]; // 9 among 5 is 126 each element is a route from root to leaf
    for (int a=0; a<9;a++)
    {
        all_route[a]=create_tree(tree->*children[a])
        for(int b=0; b<8;b++)
        {
            all_route[a] = add_leaf(all_route[a],
            for(int c=0; c<7; c++)
            {
                for(int c=0; c<6;c++)
                {
                    for(int d=0; d<5;d++)
                    {
                        for(int e=0;e<4;e++)
                        {
                            for(int f=0; f=3;f++)
                            {
                                for(int g=0; g<2;g++)
                                {
                                    for(int h=0;h<1;h++)
                                    {

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}