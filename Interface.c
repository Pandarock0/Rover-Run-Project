#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "project_function.h"
#include "winuser.h"
#include "interface.h"

//Program to display the interface of the project (you need to add /* and */ at the beginning and end of the main)

int initial_availabilitygui[] = {22, 15, 7, 7, 21, 21, 7};


int current_availabilitygui[7];

HINSTANCE hInst; // Application instance handle
char selectedMap[256] = ""; // Store the selected map path
HWND mapDisplayArea;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;

    // Define and register the main window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MainWindow";

    RegisterClass(&wc);

    // Define and register the map selection window class
    WNDCLASS mapWc = {0};
    mapWc.lpfnWndProc = MapWindowProc;
    mapWc.hInstance = hInstance;
    mapWc.lpszClassName = "MapWindow";

    WNDCLASS treeWc = {0};
    treeWc.lpfnWndProc = TreeWindowProc;
    treeWc.hInstance = hInst;
    treeWc.lpszClassName = "TreeWindow";

    RegisterClass(&treeWc);

    RegisterClass(&mapWc);

    // Create the main application window
    HWND hwnd = CreateWindow(
            "MainWindow", "Mars Rover Menu",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            600, 400,
            NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Main Window Procedure
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND btnChooseMap, btnExecuteMoves, btnDisplayTree, btnDisplayCosts, btnExit, moveDisplayArea;
    int* moves;
    PAINTSTRUCT ps;
    HDC hdc;
    switch (uMsg) {
        case WM_CREATE:
            // Create buttons for the menu
            btnChooseMap = CreateWindow(
                    "BUTTON", "Choose Map",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    20, 20, 200, 30,
                    hwnd, (HMENU)1, hInst, NULL);

            btnExecuteMoves = CreateWindow(
                    "BUTTON", "Execute Random Moves",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    20, 60, 200, 30,
                    hwnd, (HMENU)2, hInst, NULL);

            btnDisplayTree = CreateWindow(
                    "BUTTON", "Display Tree",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    20, 100, 200, 30,
                    hwnd, (HMENU)3, hInst, NULL);


            btnExit = CreateWindow(
                    "BUTTON", "Exit",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    20, 180, 200, 30,
                    hwnd, (HMENU)4, hInst, NULL);

            // Create a static area to display the map
            mapDisplayArea = CreateWindow(
                    "STATIC", "Map will be displayed here.",
                    WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
                    250, 20, 300, 300,
                    hwnd, NULL, hInst, NULL);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1: // "Choose Map" button clicked
                    // Open the map selection window
                    CreateWindow(
                            "MapWindow", "Choose a Map",
                            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            400, 300,
                            hwnd, NULL, hInst, NULL);

                    break;

                case 2: // "Execute Random Moves"
                    moves = moveexecutiongui(); // Generate random moves
                    char moveString[256] = "Moves: ";

                    // Format moves into a single string
                    for (int i = 0; i < TOTAL_MOVES; i++) {
                        char move[4];
                        sprintf(move, "%d ", moves[i]);
                        strcat(moveString, move);
                    }

                    // Free allocated memory
                    free(moves);

                    MessageBox(hwnd, moveString, "Random Moves", MB_OK);

                    break;

                case 3: // "Display Tree"
                    // Generate random moves and create the tree
                    moves = moveexecutiongui();
                    t_tree* tree = malloc(sizeof(t_tree));
                    *tree = create_treegui(moves);
                    free(moves);

                    // Create a new window to display the tree
                    HWND treeWindow = CreateWindow(
                            "TreeWindow", "Tree Visualization",
                            WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            800, 600,
                            hwnd, NULL, hInst, tree);

                    ShowWindow(treeWindow, SW_SHOW);
                    break;
                case 4: // "Display Costs"
                    MessageBox(hwnd, "Displaying costs of the paths...", "Info", MB_OK);
                    break;

                case 5: // "Exit"
                    PostQuitMessage(0);
                    break;

                default:
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);

    }

    return 0;
}

// Map Window Procedure
LRESULT CALLBACK MapWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND btnExample1, btnTraining, btnProject, btnCustom;

    switch (uMsg) {
        case WM_CREATE:
            // Create buttons for map options
            btnExample1 = CreateWindow(
                    "BUTTON", "Example 1 Map",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    20, 20, 200, 30,
                    hwnd, (HMENU)101, hInst, NULL);

            btnTraining = CreateWindow(
                    "BUTTON", "Training Map",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    20, 60, 200, 30,
                    hwnd, (HMENU)102, hInst, NULL);

            btnProject = CreateWindow(
                    "BUTTON", "Project Map",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    20, 100, 200, 30,
                    hwnd, (HMENU)103, hInst, NULL);

            btnCustom = CreateWindow(
                    "BUTTON", "Other Map",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    20, 140, 200, 30,
                    hwnd, (HMENU)104, hInst, NULL);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 101:
                    strcpy(selectedMap, "..\\maps\\example1.map");
                    break;

                case 102:
                    strcpy(selectedMap, "..\\maps\\training.map");
                    break;

                case 103:
                    strcpy(selectedMap, "..\\maps\\test.map");
                    break;

                case 104: {
                    char customMap[100];
                    MessageBox(hwnd, "Enter the map file name in the console.", "Info", MB_OK);
                    printf("Enter map name: ");
                    scanf("%s", customMap);
                    sprintf(selectedMap, "..\\maps\\%s.map", customMap);
                    break;
                }
            }

            if (LOWORD(wParam) >= 101 && LOWORD(wParam) <= 104) {
                HWND mainWnd = GetParent(hwnd); // Get main window handle
                displayMapgui(mapDisplayArea, selectedMap); // Update the main window display
                DestroyWindow(hwnd); // Close the map window
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK TreeWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static t_tree* tree;
    static double zoomFactor = 1.0;
    int mouseX, mouseY;

    switch (uMsg) {
        case WM_CREATE:
        {
            CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
            tree = (t_tree*)cs->lpCreateParams;
            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Clear the background
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            // Apply zoom transformation
            SetGraphicsMode(hdc, GM_ADVANCED);
            XFORM xform = {0};
            xform.eM11 = (FLOAT)zoomFactor; // Scale horizontally
            xform.eM22 = (FLOAT)zoomFactor; // Scale vertically
            xform.eDx = 0.0f; // No translation
            xform.eDy = 0.0f;
            ModifyWorldTransform(hdc, &xform, MWT_LEFTMULTIPLY);

            // Render the tree
            if (tree && tree->root_node) {
                renderTreegui(hdc, tree->root_node, 400, 50, 200 * zoomFactor);
            }

            EndPaint(hwnd, &ps);
            break;
        }

        case WM_MOUSEWHEEL:
        {
            // Get the wheel delta
            int delta = GET_WHEEL_DELTA_WPARAM(wParam);

            // Update zoom factor
            if (delta > 0) {
                zoomFactor *= 1.1; // Zoom in
            } else {
                zoomFactor *= 0.9; // Zoom out
            }

            // Clamp zoom factor
            if (zoomFactor < 0.1) zoomFactor = 0.1;
            if (zoomFactor > 5.0) zoomFactor = 5.0;

            // Redraw the window
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case WM_LBUTTONDOWN: {
            // Get mouse coordinates
            mouseX = GET_X_LPARAM(lParam);
            mouseY = GET_Y_LPARAM(lParam);

            // Adjust coordinates based on zoom factor
            int adjustedX = (int) (mouseX / zoomFactor);
            int adjustedY = (int) (mouseY / zoomFactor);

            // Find the clicked node
            t_node *clickedNode = findNodeAtPositiongui(tree->root_node, adjustedX, adjustedY, 400, 50, 200);
            if (clickedNode) {
                char details[256];
                sprintf(details, "Node Details:\nDepth: %d\nCost: %d\nMove: %d", clickedNode->depth,
                        clickedNode->value_cost, clickedNode->chosen_move);
                MessageBox(hwnd, details, "Node Information", MB_OK);
            }
            break;
        }

        case WM_DESTROY:
        {
            free(tree); // Free the tree structure
            PostQuitMessage(0);
            break;
        }

        case 7: // Reset Zoom
        {
            zoomFactor = 1.0;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

t_node* findNodeAtPositiongui(t_node* node, int mouseX, int mouseY, int x, int y, int xOffset) {
    if (node == NULL) return NULL;

    // Node bounding box
    const int NODE_WIDTH = 100;
    const int NODE_HEIGHT = 20;

    // Check if the mouse click is within this node's bounding box
    if (mouseX >= x && mouseX <= x + NODE_WIDTH &&
        mouseY >= y && mouseY <= y + NODE_HEIGHT) {
        return node;
    }

    // Recursively check child nodes
    for (int i = 0; i < node->total_moves; i++) {
        if (node->list_node[i] != NULL) {
            int childX = x - xOffset + (i * xOffset * 2 / node->total_moves);
            int childY = y + 50;
            t_node* result = findNodeAtPositiongui(node->list_node[i], mouseX, mouseY, childX, childY, xOffset / 2);
            if (result != NULL) {
                return result;
            }
        }
    }

    return NULL;
}

void displayMapgui(HWND hwnd, char *mapPath) {
    t_map map = createMapFromFile(mapPath); // Load the map
    char mapContent[10240] = ""; // Large buffer to hold the entire map content
    char lineBuffer[128]; // Temporary buffer for each line

    for (int i = 0; i < map.y_max; i++) {
        for (int rep = 0; rep < 3; rep++) { // Repeat rows 3 times for visual clarity
            strcpy(lineBuffer, ""); // Reset the line buffer for each row
            for (int j = 0; j < map.x_max; j++) {
                char c[4];
                switch (map.soils[i][j]) {
                    case BASE_STATION:
                        strcpy(c, (rep == 1) ? " B " : "   ");
                        break;
                    case PLAIN:
                        strcpy(c, "---");
                        break;
                    case ERG:
                        strcpy(c, "~~~");
                        break;
                    case REG:
                        strcpy(c, "^^^");
                        break;
                    case CREVASSE:
                        strcpy(c, "XXX"); // Example symbol for crevasse
                        break;
                    default:
                        strcpy(c, "???");
                        break;
                }
                strcat(lineBuffer, c); // Add the cell content to the current line
            }
            strcat(lineBuffer, "\n"); // Add a newline at the end of the row
            strcat(mapContent, lineBuffer); // Append the line to the full map content
        }
    }

    // Display the map content in the static control
    SetWindowText(hwnd, mapContent);
}

void renderTreegui(HDC hdc, t_node* node, int x, int y, int xOffset) {
    if (node == NULL) return;

    // Draw the current node
    char buffer[128];
    sprintf(buffer, "Depth: %d, Cost: %d, Move: %d", node->depth, node->value_cost, node->chosen_move);
    TextOut(hdc, x, y, buffer, strlen(buffer));

    // Draw children recursively
    for (int i = 0; i < node->total_moves; i++) {
        if (node->list_node[i] != NULL) {
            // Calculate child position
            int childX = x - xOffset + (i * xOffset * 2 / node->total_moves);
            int childY = y + 50;

            // Draw line to child
            MoveToEx(hdc, x + 50, y + 20, NULL); // Start at the bottom of the parent node
            LineTo(hdc, childX + 50, childY);    // End at the top of the child node

            // Recursively render the child
            renderTreegui(hdc, node->list_node[i], childX, childY, xOffset / 2);
        }
    }
}
// Function to Reset Move Availability
void resetCountgui() {
    for (int i = 0; i < 7; i++) {
        current_availabilitygui[i] = initial_availabilitygui[i];
    }
}

// Function to Select a Random Move
t_move selectRandomMovegui() {
    int move;

    while (1) {
        move = rand() % 7;  // Randomly choose one of the 7 moves
        if (current_availabilitygui[move] > 0) {
            current_availabilitygui[move]--;  // Reduce the count of this move
            return move;                   // Return the selected move
        }
    }
}

// Function to Execute Moves
int* moveexecutiongui() {
    resetCountgui();  // Reset moves at the beginning of each phase
    int* moves = (int*) malloc(TOTAL_MOVES * sizeof(int));
    for (int i = 0; i < TOTAL_MOVES; i++) {
        moves[i] = selectRandomMovegui();
    }
    return moves;
}

// Function to Create a New Node
t_node* create_nodegui(int depth, int* mvmt_list, int value, int move_choose, int nb_available_mvmt, t_node* previous_node){

    t_node* new_node = (t_node*) malloc(sizeof(t_node));

    //allocation for previous node
    new_node->previous_node = previous_node;

    //allocation for available_mvmt
    new_node->available_mvmt = (int*) malloc(nb_available_mvmt * sizeof(int));
    for (int i=0; i<nb_available_mvmt; i++){
        new_node->available_mvmt[i] = mvmt_list[i];
    }

    //allocation for list_node
    new_node->list_node = (t_node**) malloc(nb_available_mvmt*sizeof(t_node*));
    for(int i=0; i<nb_available_mvmt; i++){
        new_node->list_node[i] = NULL;
    }

    //allocation for the chosen movement corresponding to the node
    new_node->chosen_move = move_choose;

    //allocation nb of available mvmts
    new_node->total_moves = nb_available_mvmt;

    //allocatuon of level correponding
    new_node->depth = depth;

    //allocation of the localisation and cost_value
    int exit = update_loc(new_node); //update map and new_localisation (not the real of the robot)
    new_node->exit_condition = exit;
    if (exit == 1) {
        new_node->value_cost = calculate_cost(new_node);
    }

    return new_node;
}

// Function to Build the Tree Recursively
void build_tree_recursivelygui(t_node* root_node, int nb_available_mvmt, int* mvmt_list, int depth) {
    if (depth >= 5) {
        return;
    }

    for (int i = 0; i < nb_available_mvmt; i++) {
        int *new_mvmt_list = (int *)malloc((nb_available_mvmt - 1) * sizeof(int));
        int k = 0;

        for (int j = 0; j < nb_available_mvmt; j++) {
            if (j != i) {
                new_mvmt_list[k++] = mvmt_list[j];
            }
        }
        t_node* new_node = create_nodegui(depth + 1, new_mvmt_list, rand() % 500, mvmt_list[i], nb_available_mvmt - 1, root_node);
        root_node->list_node[i] = new_node;
        free(new_mvmt_list);
    }

    for (int i = 0; i < nb_available_mvmt; i++) {
        if (root_node->list_node[i] != NULL) {
            build_tree_recursivelygui(root_node->list_node[i], nb_available_mvmt - 1,
                                      root_node->list_node[i]->available_mvmt, depth + 1);
        }
    }
}

// Function to Create the Tree
t_tree create_treegui(int* mvmt_list) {
    t_tree tree;
    tree.root_node = create_nodegui(0, mvmt_list, 0, -1, 7, NULL); // Root node with depth 0
    build_tree_recursivelygui(tree.root_node, 7, mvmt_list, 0);
    return tree;
}

void display_treegui(t_node* node, FILE* file) {
    if (node == NULL) {
        return;
    }

    // Node details
    fprintf(file, "Node:\n");
    fprintf(file, "  Depth          : %d\n", node->depth);
    fprintf(file, "  Value Cost     : %d\n", node->value_cost);
    fprintf(file, "  Chosen Move    : %d\n", node->chosen_move);
    fprintf(file, "  Total Moves    : %d\n", node->total_moves);
    fprintf(file, "  Available Moves: ");
    for (int i = 0; i < node->total_moves; i++) {
        fprintf(file, "%d ", node->available_mvmt[i]);
    }
    fprintf(file, "\n  Next Nodes Addresses: [");
    for (int i = 0; i < node->total_moves; i++) {
        fprintf(file, "%p ", (void*)node->list_node[i]);
    }
    fprintf(file, "]\n\n");

    // Recursive display of children
    for (int i = 0; i < node->total_moves; i++) {
        if (node->list_node[i] != NULL) {
            display_treegui(node->list_node[i], file);
        }
    }
}
