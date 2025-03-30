#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include "algorithms.h"
#include "independent.h"

<<<<<<< HEAD
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
=======
void runAlgorithm(Graph<int> &graph, int source, int destination, std::unordered_set<int> &avoidNodes,
                  const std::string &mode, bool parked, std::ostream &out, bool isFirstRun) {

    dijkstra(&graph, source, destination, avoidNodes, mode, parked);
    std::vector<int> path = getPath(&graph, source, destination);

    out << (isFirstRun ? "BestDrivingRoute:" : "AlternativeDrivingRoute:");

    if (path.empty()) {
        out << "none" << std::endl;
>>>>>>> refs/remotes/origin/main
    } else {
        out << path.front();
        for (size_t i = 1; i < path.size(); i++) {
            out << "," << path[i];
            if (isFirstRun && static_cast<int>(i) != source && static_cast<int>(i) != destination) {
                avoidNodes.insert(i);
            }
        }
        out << "(" << graph.findVertex(destination)->getDist() << ")" << std::endl;
    }
}

<<<<<<< HEAD
void independentBatch(Graph<int> &graph, const std::string &filename, const std::string &outputFilename) {
    std::unordered_set<int> avoidNodes; // Defining the set of nodes to avoid
    std::unordered_set<int> avoidEdges; // Only stated in case you need it in the future
    std::ifstream file(filename);
=======
void independent(Graph<int> &graph) {
    std::string sourceStr, destinationStr, mode;
    std::unordered_set<int> avoidNodes, avoidEdges;
    bool parked = false;

    std::cout << "Mode: "; std::cin >> mode;
    std::cout << "Source: "; std::cin >> sourceStr;
    std::cout << "Destination: "; std::cin >> destinationStr;

    int source = std::stoi(sourceStr), destination = std::stoi(destinationStr);

    runAlgorithm(graph, source, destination, avoidNodes, mode, parked, std::cout, true);
    runAlgorithm(graph, source, destination, avoidNodes, mode, parked, std::cout, false);
}

void independentBatch(Graph<int> &graph, const std::string &inputFilename, const std::string &outputFilename) {
    std::ifstream file(inputFilename);
>>>>>>> refs/remotes/origin/main
    if (!file) {
        std::cerr << "Error: Could not open file " << inputFilename << std::endl;
        return;
    }

<<<<<<< HEAD
    // Opens output file
=======
>>>>>>> refs/remotes/origin/main
    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Error: Could not open file " << outputFilename << std::endl;
        return;
    }

    std::string mode, key, value, line;
    int source = -1, destination = -1;
    bool parked = false;
    std::unordered_set<int> avoidNodes, avoidEdges;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (std::getline(iss >> std::ws, key, ':') && std::getline(iss >> std::ws, value)) {
            if (key == "Mode") mode = value;
            else if (key == "Source") source = std::stoi(value);
            else if (key == "Destination") destination = std::stoi(value);
        }
    }

<<<<<<< HEAD
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
=======
    outputFile << "Source:" << source << "\nDestination:" << destination << std::endl;

    runAlgorithm(graph, source, destination, avoidNodes, mode, parked, outputFile, true);
    runAlgorithm(graph, source, destination, avoidNodes, mode, parked, outputFile, false);
>>>>>>> refs/remotes/origin/main
}
