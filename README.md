# **Rover Run Project**

## **Description**

The **Rover Run** project involves developing a program in C to guide the rover MARC (Mars Rover Cartograph) on a Martian map. The goal is to navigate MARC to a base station while minimizing movement costs and handling terrain constraints.

---

## **Github Repository**
https://github.com/Pandarock0/Rover-Run-Project

---

## **Features**

### **1. Mapping**
- **Load maps** from `.map` files.
- Handle different terrain types:
  - **Plain**
  - **Erg**
  - **Reg**
  - **Crevasse**
  - **Slope**
- **Calculate movement costs** based on terrain type.

### **2. Rover Movement**
- Simulate MARC's movements:
  - **Forward**
  - **Backward**
  - **Turn Left**
  - **Turn Right**
  - **U-Turn**
- **Dynamically update** MARC's position and orientation.

### **3. Optimization**
- Build a **decision tree** to evaluate possible movement sequences.
- Compute the **total cost** of paths to minimize movements.

### **4. Visualization**
- Display the **graphical representation** of the map.
- Show MARC's **position and movements**.

---

## **Project Structure**

The project is organized into multiple modular files:

- **`main.c`**: Entry point of the program, used to test different functionalities.
- **`loc.c` and `loc.h`**: Handle MARC's position and orientation.
- **`map.c` and `map.h`**: Manage map loading, visualization, and cost calculations.
- **`moves.c` and `moves.h`**: Handle rover's possible movements and their selection.
- **`project_function.c` and `project_function.h`**: Implement advanced features like decision tree creation and path optimization.

### **Key Structures**
- **`t_map`**: Represents the Martian map, including terrain types and movement costs.
- **`t_node`**: Represents a node in the decision tree for movements.
- **`t_tree`**: Represents the decision tree used for optimizing paths.

---

## **Requirements**

- **Compiler**: GCC or any compatible C compiler.
- **Operating System**: Linux or Windows with a C development environment.
- **Map Files**: Maps must be provided as `.map` files (see format below).

---

## **Map File Format**

A map file should contain:
1. The first line: the **number of rows** in the map.
2. The second line: the **number of columns** in the map.
3. Subsequent lines: values representing terrain types:
   - `0`: Base station.
   - `1`: Plain.
   - `2`: Erg.
   - `3`: Reg.
   - `4`: Crevasse.



## **Credits**

- **Lead Developer**: Abdou-Samad, Brian, Leo 
- **TI301 Project**: Algorithms and Data Structures - EFREI
