//
// Created by Carouge on 23/11/2024.
//

#ifndef UNTITLED1_INTERFACE_H
#define UNTITLED1_INTERFACE_H

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "project_function.h"
#include "winuser.h"
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam) ((int)(short)LOWORD(lParam))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam) ((int)(short)HIWORD(lParam))
#endif
#include "stack.h"

#define TOTAL_MOVES 9
 // Handle for the map display area


// Function prototypes
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MapWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK TreeWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

t_node* findNodeAtPositiongui(t_node* node, int mouseX, int mouseY, int x, int y, int xOffset);
void displayMapgui(HWND hwnd, char *mapPath);
void renderTreegui(HDC hdc, t_node* node, int x, int y, int xOffset);
t_node* create_nodegui(int depth, int* mvmt_list, int value_cost, int chosen_move, int total_moves, t_node* parent);
t_tree create_treegui(int* mvmt_list);
void build_tree_recursivelygui(t_node* root_node, int nb_available_mvmt, int* mvmt_list, int depth);
void resetCountgui();
t_move selectRandomMovegui();
void display_treegui(t_node*, FILE*);
int* moveexecutiongui();



#endif //UNTITLED1_INTERFACE_H

