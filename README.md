Rover Run Project
Description
The Rover Run project involves developing a software in C to guide the rover MARC (Mars Rover Cartograph) on a Martian map. The goal is to navigate MARC to a base station while minimizing movement costs and adhering to terrain constraints.

Features
Mapping:

Load Mars maps from files.
Handle terrain types (plain, erg, reg, crevasse, slope).
Calculate the cost of each tile based on terrain type.
Rover Movement:

Simulate MARC's movements (forward, backward, turn, U-turn).
Choose movements using a decision tree to find the optimal path.
Update coordinates and orientation dynamically.
Optimization:

Build a decision tree to evaluate possible movement sequences.
Compute total path cost to minimize movements.
Visualization:

Display a graphical representation of the map and MARC's positions.
Show movements performed in the simulation.
Project Structure
The project is organized into multiple files for better modularity:

Main Files
main.c: Entry point of the program, used for testing different functionalities.
loc.c and loc.h: Handle MARC's position and orientation.
map.c and map.h: Manage map loading, display, and cost calculations.
moves.c and moves.h: Manage available movements and random selection.
project_function.c and project_function.h: Implement advanced functionalities such as decision tree creation and route optimization.
Key Structures
t_map: Represents the Martian map, including terrain types and costs.
t_node: Represents a node in the decision tree for movements.
t_tree: Represents the decision tree used to optimize movements.
Requirements
Compiler: GCC or any C-compatible compiler.
Operating System: Linux or Windows with a C development environment.
Map Files: Maps must be provided as .map files (see the format below).
Map File Format
A map file contains:

The first line: the number of rows in the map.
The second line: the number of columns in the map.
Subsequent lines: values representing terrain types.
0: Base station.
1: Plain.
2: Erg.
3: Reg.
4: Crevasse.
Example map:

Copier le code
5
5
0 1 1 3 4
1 1 2 3 1
1 1 1 2 1
3 1 0 1 1
4 1 1 1 1
Compilation and Execution
Compilation
To compile the project, use the following command:

bash
Copier le code
gcc -o rover_run main.c loc.c map.c moves.c project_function.c -lm
Execution
To run the program:

bash
Copier le code
./rover_run
Dependencies
No external dependencies are required.

Key Functionalities
Load a Map:
Load a map from a file and display the terrain grid.
Execute Movements:
Simulate a phase of MARC's movements with random choices.
Optimize Movements:
Build a decision tree to minimize the total path cost.
Display:
Visualize the map with MARC's movements.
Future Enhancements
Add slope management on the map.
Create a graphical interface for better visualization.
Introduce new terrain types for more complex scenarios.
Credits
Lead Developer: [Your Name]
TI301 Project: Algorithms and Data Structures - EFREI Space Task Force (ESTF)