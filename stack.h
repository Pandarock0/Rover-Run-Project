//
// Created by brian on 24/11/2024.
//

#ifndef STACK_H
#define STACK_H
//#include "project_function.h"

/**
 * @brief Structure for the stack of integers
 */
typedef struct s_stack
{
    int *values;
    int size;
    int nbElts;
} t_stack;

/*typedef struct {
    int size;
    int nbElts;
    t_node** nodes;
} t_stack;*/

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(int);

/**
 * @brief Function to push a value in the stack
 * @param pointer to the stack
 * @param value : the value to push
 * @return none
 */
void push(t_stack *, int);
//void push(t_stack* p_stack, t_node* node);


/**
 * @brief Function to pop a value from the stack
 * @param : pointer to the stack
 * @return the value popped
 */
int pop(t_stack *);
//t_node* pop(t_stack* p_stack);

/**
 * @brief Function to get the top value of the stack
 * @param stack : the stack
 * @return the top value
 */
int top(t_stack);
//t_node* top(t_stack stack);

#endif //STACK_H
