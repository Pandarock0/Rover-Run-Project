//
// Created by brian on 24/11/2024.
//

#ifndef PROJECT_FUNCTION_H
#define PROJECT_FUNCTION_H

#include "loc.h"
#include "moves.h"
#include "map.h"


t_map choose_map();

typedef struct node{

    int * available_mvmt;
    struct node** list_node;
    struct node* previous_node;
    int total_moves;
    int chosen_move;
    int depth;

    //map parameters
    int value_cost;
    int exit_condition;
    t_map map;
    t_localisation localisation;
    int base_station;

} t_node;

typedef struct s_tree{
    t_node* root_node;
} t_tree;

//Structure from Abdou Samad
typedef struct{
    t_tree* path;
    int length;
    int weight;

}Route;

/**
 * @brief Resets the availability of all movements to their initial values.
 * This is called at the beginning of each phase to ensure all moves can be used again.
 */
void resetCount();

/**
 * @brief Selects a random movement based on the current availability.
 * Decreases the availability count of the selected movement.
 * @return A random movement of type `t_move`.
 */
t_move selectRandomMove();

/**
 * @brief Generates a list of random movements for a phase.
 * Resets the availability of moves at the start and fills an array with random moves.
 * @return Pointer to an array of movements.
 */
int* moveexecution();

/**
 * @brief Creates a new node in the decision tree.
 * Initializes all node parameters such as depth, previous node, available movements, etc.
 * Updates the robot's location and calculates its cost if valid.
 * @param depth The current depth of the node in the tree.
 * @param mvmt_list The list of available movements for the node.
 * @param move_choose The movement chosen at this node.
 * @param nb_available_mvmt The number of available movements.
 * @param previous_node Pointer to the parent node.
 * @return Pointer to the created node.
 */
t_node* create_node(int depth, int* mvmt_list, int move_choose, int nb_available_mvmt, t_node* previous_node);

/**
 * @brief Updates the robot's location in the map after a movement.
 * Ensures the new location is valid within the map boundaries.
 * @param current_node Pointer to the node containing the movement and map information.
 * @return 1 if the location is valid, 0 otherwise.
 */
int update_loc(t_node* current_node);

/**
 * @brief Calculates the cost of a node's location based on its position and parent node cost.
 * @param current_node Pointer to the current node.
 * @return The cost of the location.
 */
int calculate_cost(t_node* current_node);

/**
 * @brief Checks if the robot is at the base station.
 * Validates the robot's position within map bounds and compares it to the base station location.
 * @param current_node Pointer to the current node.
 * @return 1 if at the base station, 0 otherwise.
 */
int at_the_base_station(t_node* current_node);

/**
 * @brief Recursively builds the decision tree for the robot's movements.
 * Generates child nodes for each available movement until a specified depth is reached.
 * @param root_node Pointer to the root node of the tree.
 * @param nb_available_mvmt The number of movements available at this level.
 * @param mvmt_list List of movements available to the current node.
 * @param depth Current depth of the tree.
 */
void build_tree_recursively(t_node* root_node, int nb_available_mvmt, int* mvmt_list, int depth);

/**
 * @brief Creates the decision tree for robot movements starting from a root node.
 * Initializes the root node and calls the recursive tree builder.
 * @param mvmt_list List of available movements.
 * @param map The map data used for navigation and costs.
 * @return The created tree structure.
 */
t_tree create_tree(int* mvmt_list, t_map map);

/**
 * @brief Displays detailed information about a tree node.
 * Recursively prints all child nodes of the given node.
 * @param node Pointer to the node to display.
 */
void display_tree(t_node* node);

/**
 * @brief Displays nodes that are located at the base station.
 * Recursively checks and prints all nodes that meet the base station condition.
 * @param node Pointer to the root node for the check.
 */
void print_base_station_nodes(t_node* node);

/**
 * @brief A test function that creates a list of nodes with predefined locations and orientations.
 * @return Array of pointers to created nodes.
 */
t_node** test_function();

/**
 * @brief Displays the map with robot positions and orientations.
 * Overlay the robot's position on the map's visual representation.
 * @param map The map structure.
 * @param nodes List of nodes representing the robot's positions.
 * @param node_count Number of nodes to display.
 */
void displayMap_robot(t_map map, t_node** nodes, int node_count);

/**
 * @brief Displays the best moves based on the nodes provided.
 * Iterates over the list of nodes and prints their associated moves.
 * @param node_list List of nodes to evaluate.
 * @param node_count Number of nodes in the list.
 */
void display_best_move(t_node** node_list, int node_count);

/**
 * @brief Recursively finds the minimum route in the decision tree.
 * Updates the best route if a better one is found during traversal.
 * @param node Pointer to the current node.
 * @param currentPath Pointer to the temporary path being evaluated.
 * @param currentWeight Current weight (cost) of the path.
 * @param currentLength Current length of the path.
 * @param bestRoute Pointer to the structure storing the best route found.
 */
void findMinimumRoute(t_node *node, t_tree *currentPath, int currentWeight, int currentLength, Route *bestRoute);

/**
 * @brief Finds the minimum route in the decision tree.
 * Initializes the search for the best route using the root node.
 * @param tree The decision tree.
 * @return The best route found in the tree.
 */
Route minimum_route(t_tree tree);

/**
 * @brief Creates a copy of a tree node without its children or previous node.
 * Allocates memory and duplicates the node's data.
 * @param src Pointer to the node to copy.
 * @return Pointer to the copied node.
 */
t_node* deep_copy_node(t_node* src);

void free_tree(t_node*);


//t_queue list_position(t_node* node);
//t_stack node_stack_list(t_node* node);

#endif //PROJECT_FUNCTION_H
