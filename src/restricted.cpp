/**
 * @file restricted.cpp
 * @brief Implementation of the restricted route algorithm.
 * 
 * Computes the best route with resctictions as:
 *  Avoiding specific nodes,
 *  Avoiding specific segments of the graph,
 *  Simultaniously avoiding nodes and sections,
 *  Including specific nodes the route has to visit. 
 * 
*/

#include <iostream>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <string>
#include "algorithms.h"
#include "Graph.h"
#include "restricted.h"
/**
 * @brief Runs the restricted pathfinding algorithm, considering avoidance and inclusion constraints.
 * 
 *  This function first checks if a specific node must be included in the path. If so, it calculates the shortest path
 *  to that node first and then continues from it to the final destination. If no inclusion is required, a direct shortest path is computed.
 * 
 * @param graph The graph where to search.
 * @param source The starting node.
 * @param destination The target node.
 * @param includeNode A node that must be included in the path (-1 if not applicable).
 * @param avoidNodes Set of nodes to be avoided.
 * @param mode The mode of transportation.
 * @param parked Indicates if there is parking avaliable.
 * @param out The output stream to write the result.
 * 
 * Complexity is O((V + E) log V), where V is the number of vertices and E is the number of edges in the graph.
 */
 

void runRestrictedAlgorithm(Graph<int> &graph, int source, int destination, int includeNode,
                            std::unordered_set<int> &avoidNodes, const std::string &mode, bool parked, std::ostream &out) {
    int total = 0;
    std::vector<int> path;

    if (includeNode != -1) {
        dijkstra(&graph, source, includeNode, avoidNodes, mode, parked);
        path = getPath(&graph, source, includeNode);
        total = graph.findVertex(includeNode)->getDist();

        dijkstra(&graph, includeNode, destination, avoidNodes, mode, parked);
        std::vector<int> path2 = getPath(&graph, includeNode, destination);
        total += graph.findVertex(destination)->getDist();

        path.insert(path.end(), path2.begin() + 1, path2.end());
    } else {
        dijkstra(&graph, source, destination, avoidNodes, mode, parked);
        path = getPath(&graph, source, destination);
        total = graph.findVertex(destination)->getDist();
    }

    out << "RestrictedDrivingRoute:";
    if (path.empty()) {
        out << "none" << std::endl;
    } else {
        out << path[0];
        for (size_t i = 1; i < path.size(); i++) out << "," << path[i];
        out << "(" << total << ")" << std::endl;
    }
}

/**
 * @brief Handles user input for restricted routes.
 * 
 * This function reads user input for mode, source, destination, nodes to avoid, edges to avoid,
 * and an optional node to include in the path. It then calls the restricted pathfinding algorithm.
 * 
 * @param graph The graph representing the road network.
 * 
 * Complexity is O((V + E) log V), due to calling the pathfinding algorithm.
 */

void restricted(Graph<int> &graph) {
    std::string mode, sourceStr, destinationStr;
    int source, destination, includeNode = -1;
    std::unordered_set<int> avoidNodes, avoidEdges;
    bool parked = false;

    std::cout << "Mode: "; std::cin >> mode;
    std::cout << "Source: "; std::cin >> sourceStr;
    std::cout << "Destination: "; std::cin >> destinationStr;

    source = std::stoi(sourceStr);
    destination = std::stoi(destinationStr);

    std::cout << "AvoidNodes: ";
    std::string line;
    std::cin.ignore();
    std::getline(std::cin, line);
    if (!line.empty()) {
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            try {
                avoidNodes.insert(std::stoi(token));
            } catch (...) {
                std::cerr << "Warning: Ignoring invalid AvoidNodes value: " << token << std::endl;
            }
        }
    }

    std::cout << "AvoidSegments: ";
    std::getline(std::cin, line);
    if (!line.empty()) {
        size_t pos = 0;
        while ((pos = line.find('(')) != std::string::npos) {
            size_t closeParen = line.find(')', pos);
            if (closeParen == std::string::npos) break;

            std::string edge = line.substr(pos + 1, closeParen - pos - 1);
            line = line.substr(closeParen + 1);

            std::stringstream edgeStream(edge);
            int start, end;
            char comma;
            if (edgeStream >> start >> comma >> end && comma == ',') {
                selectEdge(&graph, start, end);
            } else {
                std::cerr << "Warning: Invalid AvoidSegments format: " << edge << std::endl;
            }
        }
    }

    std::cout << "IncludeNode: ";
    std::getline(std::cin, line);
    if (!line.empty()) {includeNode = std::stoi(line);}

    runRestrictedAlgorithm(graph, source, destination, includeNode, avoidNodes, mode, parked, std::cout);
}
/**
 * @brief Processes a batch file for the restricted pathfinding.
 * 
 * Reads input parameters from a file and executes the restricted pathfinding algorithm for batch processing.
 * (Batch mode)
 * 
 * @param graph The graph representing the road network.
 * @param filename The input file name.
 * @param outputFilename The output file name.
 * 
 * @complexity O((V + E) log V) per query, as it calls the pathfinding function.
 */

void restrictedBatch(Graph<int> &graph, const std::string &filename, const std::string &outputFilename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Error: Could not open file " << outputFilename << std::endl;
        return;
    }

    std::unordered_set<int> avoidNodes, avoidEdges;
    std::string mode, key, value, line;
    int source = -1, destination = -1, includeNode = -1;
    bool parked = false;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (std::getline(iss, key, ':') && std::getline(iss >> std::ws, value)) {
            if (key == "Mode") mode = value;
            else if (key == "Source") source = std::stoi(value);
            else if (key == "Destination") destination = std::stoi(value);
            else if (key == "AvoidNodes" && !value.empty()) {
                std::stringstream ss(value);
                std::string token;
                while (std::getline(ss, token, ',')) {
                    try {
                        avoidNodes.insert(std::stoi(token));
                    } catch (...) {
                        std::cerr << "Warning: Invalid AvoidNodes value: " << token << std::endl;
                    }
                }
            }
            else if (key == "AvoidSegments" && !value.empty()) {
                size_t pos = 0;
                while ((pos = value.find('(')) != std::string::npos) {
                    size_t closeParen = value.find(')', pos);
                    if (closeParen == std::string::npos) break;

                    std::string edge = value.substr(pos + 1, closeParen - pos - 1);
                    value = value.substr(closeParen + 1);

                    std::stringstream edgeStream(edge);
                    int start, end;
                    char comma;
                    if (edgeStream >> start >> comma >> end && comma == ',') {
                        selectEdge(&graph, start, end);
                    } else {
                        std::cerr << "Warning: Invalid AvoidSegments format: " << edge << std::endl;
                    }
                }
            }
            else if (key == "IncludeNode") includeNode = std::stoi(value);
        }
    }

    outputFile << "Source:" << source << "\nDestination:" << destination << std::endl;
    runRestrictedAlgorithm(graph, source, destination, includeNode, avoidNodes, mode, parked, outputFile);
}
