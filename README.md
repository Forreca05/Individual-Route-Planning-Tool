# Individual-Route-Planning-Tool

# Routing Tool

## Project Overview

This project is an **Individual Route Planning Tool** developed as part of the **Design of Algorithms** course during the **second semester of the 2024/2025 academic year** at **FEUP (Faculty of Engineering, University of Porto)**. The project focuses on **graph-based pathfinding algorithms**, including an optimized version of **Dijkstra's Algorithm** that considers both driving and walking routes while ensuring efficient parking spot selection.

## Authors

- **Carlos André Gomes Cerqueira** (up202305021)
- **João Pedro Magalhães Marques** (up202307612)
- **João Pedro Nunes Ferreira** (up202305204)

## Features

- **Graph-Based Navigation**: Uses a graph representation of locations and distances.
- **CSV Data Processing**: Reads locations and distances from CSV files.
- **Bidirectional Graph**: Supports both walking and driving paths.
- **Custom Dijkstra’s Algorithm**: Finds shortest paths while handling parking constraints.
- **Terminal Interface**: Supports both manual and batch processing modes.
- **Independent Route Planning**: Computes the fastest route between two points and an alternative independent route that does not share intermediate nodes or segments with the main one.
- **Restricted Route Planning**: Allows defining specific constraints such as avoiding nodes or edges and including a mandatory node.
- **Environmentally Friendly Route Planning**: Combines driving and walking to create a more sustainable route while respecting a maximum walking time.

## File Structure

- **Locations.csv**: Contains location names, IDs, codes, and parking availability.
- **Distances.csv**: Stores distances between locations, including driving and walking times.
- **Graph Implementation**: Supports efficient node and edge management.
- **Algorithm Implementations**:
    - `dijkstra()`: Custom implementation of Dijkstra’s Algorithm.
    - `relax()`: Updates shortest distances based on conditions.
    - `selectEdge()`: Highlights the selected path.
    - `getPath()`: Retrieves the computed shortest path.

## Algorithms

### Dijkstra’s Algorithm

- **Goal**: Find the shortest path between two nodes in a weighted graph.
- **Complexity**: `O((V+E) log V)`, where `V` is the number of vertices and `E` is the number of edges.
- **Enhancements**:
    - Avoids specific nodes (e.g., closed roads).
    - Incorporates parking availability constraints.
    - Supports multiple transport modes (walking/driving).
    - Calculates environmentally friendly routes.

### Additional Functions

- **Relaxation Function** (`relax()`): Updates the shortest distance to a vertex.
- **Edge Selection** (`selectEdge()`): Highlights the best path.
- **Path Retrieval** (`getPath()`): Extracts the computed shortest route.
- **Batch Processing**: Allows multiple queries via input files.

## Route Planning Modes

### 1. Independent Route Planning

Computes the **fastest route** between two points and an **alternative independent route** that:
- **Does not share** segments or intermediate nodes with the main route.
- **Ensures** that the alternative is equal to or longer than the primary route.

**Input Format:**
```
Mode: driving  
Source: <id>  
Destination: <id>  
```  

**Output Format:**
```
BestDrivingRoute: <id>,<id>,<id> (<total_time>)  
AlternativeDrivingRoute: <id>,<id>,<id> (<total_time>)  
```  

If no route is possible:
```
BestDrivingRoute: none  
AlternativeDrivingRoute: none  
```  

### 2. Restricted Route Planning

Allows defining **specific constraints** on the route, such as:
- **Avoiding specific nodes** (e.g., unwanted areas).
- **Avoiding specific segments** (e.g., blocked roads).
- **Including a mandatory node** (forcing a pass-through point).

**Input Format:**
```
Mode: driving  
Source: <id>  
Destination: <id>  
AvoidNodes: <id>,<id>,...  
AvoidSegments: (<id>,<id>),(<id>,<id>),...  
IncludeNode: <id>  
```  

**Output Format:**
```
RestrictedDrivingRoute: <id>,<id>,<id> (<total_time>)  
```  

If no route is possible:
```
RestrictedDrivingRoute: none  
```  

### 3. Environmentally Friendly Route Planning

Combines **driving and walking** to create a more sustainable route:
- Drive to a **parking spot**.
- Walk to the destination.
- Respect a **maximum walking time**.

**Input Format:**
```
Mode: driving-walking  
Source: <id>  
Destination: <id>  
MaxWalkTime: <int>  
AvoidNodes: <id>,<id>,...  
AvoidSegments: (<id>,<id>),(<id>,<id>),...  
```  

**Output Format:**
```
DrivingRoute: <id>,<id>,<id> (<total_time>)  
ParkingNode: <id>  
WalkingRoute: <id>,<id>,<id> (<total_time>)  
TotalTime: <int>  
```  

If no route is possible, the message explains why:
```
DrivingRoute: none  
ParkingNode: none  
WalkingRoute: none  
TotalTime:  
Message: <reason for failure>  
```  

## Challenges & Highlights

- The most challenging part was designing an **environmentally friendly route** that ensured a parking spot along the way. Initially, the parking search led to paths that passed through the destination first, which required optimization.
- The most rewarding experience was implementing a **customized Dijkstra’s Algorithm**, incorporating constraints such as **node avoidance** and **transportation modes**.

## How to Run the Project

### Interactive Mode

To run the program interactively:
```sh  
./main ../data/LocSample.txt ../data/DisSample.txt ../input.txt  
```  

### Batch Mode

For batch processing with input/output files:
```sh  
./main ../data/LocSample.txt ../data/DisSample.txt ../input.txt ../output.txt  
```  

## License

This project was developed as an academic assignment and is intended for educational purposes.

