#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include "algorithms.h"
#include "independent.h"

/**
 * @brief Finds and prints the nost alternative route between 2 points.
 * 
 * the algorithm uses Dijkstra to find the best route and then tries to find
 * an alternative avoiding  nodes from the original routes.
 * 
 * @param graph Graph where the search will be made. 
 * 
 * The complexity of this algotithm in O((N + E) log N), where N is the number 
 * of vertixes and E is the number of Edjes, becouse Dijkstra is called twice. 
 */

void independent(Graph<int> &graph) {
    std::string sourceStr, destinationStr, mode;
    bool parked = false;
    std::unordered_set<int> avoidNodes; // Defining the set of nodes to avoid
    std::unordered_set<int> avoidEdges; // Only stated in case you need it in the future

    // Data input
    std::cout << "Mode: ";
    std::cin >> mode;
    std::cout << "Source: ";
    std::cin >> sourceStr;
    std::cout << "Destination: ";
    std::cin >> destinationStr;

    int source = std::stoi(sourceStr);
    int destination = std::stoi(destinationStr);

    // 1st Execution of Dijkstra's Algorithm
    dijkstra(&graph, source, destination, avoidNodes, avoidEdges, mode, parked);
    std::vector<int> path = getPath(&graph, source, destination);

    // Printing the best route
    std::cout << "BestDrivingRoute: ";
    if (path.empty()) {
        std::cout << "none" << std::endl;
        return;
    }

    for (int i : path) {
        std::cout << i << " ";
        if (i != source && i != destination) {
            avoidNodes.insert(i);  // Mark nodes to avoid in next search
        }
    }
    std::cout << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;

    // 2nd Execution of the algorithm to find alternative route
    dijkstra(&graph, source, destination, avoidNodes, avoidEdges, mode, parked);
    path = getPath(&graph, source, destination);

    // Printing alternative route
    std::cout << "AlternativeDrivingRoute: ";
    if (path.empty()) {
        std::cout << "none" << std::endl;
    } else {
        for (int i : path) {
            std::cout << i << " ";
        }
        std::cout << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;
    }
}

void independentBatch(Graph<int> &graph, const std::string &filename, const std::string &outputFilename) {
    std::unordered_set<int> avoidNodes; // Defining the set of nodes to avoid
    std::unordered_set<int> avoidEdges; // Only stated in case you need it in the future
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Opens output file
    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Error: Could not open file " << outputFilename << std::endl;
        return;
    }

    std::string line, mode;
    int source, destination;
    bool parked = false;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;

        while (iss >> key >> value) {
            if (key == "Mode:") {
                mode = value;
            } else if (key == "Source:") {
                source = std::stoi(value);
            } else if (key == "Destination:") {
                destination = std::stoi(value);
            }
        }
    }

    file.close();  //  Closes the file after read

    // Writes the read values ​​to the output file
    outputFile << "Mode: " << mode << std::endl;
    outputFile << "Source: " << source << std::endl;
    outputFile << "Destination: " << destination << std::endl;

    // Call the required algorithm (Dijkstra, A*, etc.)
    dijkstra(&graph, source, destination, {}, {}, mode, parked);
    std::vector<int> path = getPath(&graph, source, destination);

    outputFile << "BestDrivingRoute: ";
    for (int i : path) {
        outputFile << i << " ";
        if (i != source && i != destination) {
            avoidNodes.insert(i);  // Mark nodes to avoid in next search
        }
    }
    outputFile << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;

    // 2nd Execution of the algorithm to find alternative route
    dijkstra(&graph, source, destination, avoidNodes, avoidEdges, mode, parked);
    path = getPath(&graph, source, destination);

    // Write the alternative route to the file
    outputFile << "AlternativeDrivingRoute: ";
    if (path.empty()) {
        outputFile << "none" << std::endl;
    } else {
        for (int i : path) {
            outputFile << i << " ";
        }
        outputFile << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;
    }
}

