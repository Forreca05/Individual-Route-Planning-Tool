/**
 * @file independant.cpp 
 * @brief Implentation of the algorithm that computes the 2 best alternative routes. 
 * 
 * Identifies a best alternative independent route, ensuring the two routes share no intermediate
 * nodes or segments, except for the source and destination, and that the alternative route is equal
 * to or greater in travel time than the primary route. 
 * 
 * 
 * 
 *  */

#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include "algorithms.h"
#include "independent.h"

/**
 * @brief Runs the shortest path algorithm in order to output the result.
 *
 * This function executes Dijkstra's algorithm to find the best or alternative route
 * between the given source and destination. If it's the first run, intermediate nodes
 * are added to the set of avoided nodes for the alternative route.
 *
 * @param graph The graph where to search.
 * @param source The starting node.
 * @param destination The target node.
 * @param avoidNodes Set of nodes to be avoided (used in the second run).
 * @param mode The mode of transportation 
 * @param parked Indicates of there is parking avaliable.
 * @param out The output stream.
 * @param isFirstRun Indicates if it is the first execution.
 *
 * Complexity is O((V + E) log V), where V is the number of vertices and E is the number of edges. [O(n log(n))]
 * Dijkstra's algorithm runs twice.
 */

void runAlgorithm(Graph<int> &graph, int source, int destination, std::unordered_set<int> &avoidNodes,
                  const std::string &mode, bool parked, std::ostream &out, bool isFirstRun) {

    dijkstra(&graph, source, destination, avoidNodes, mode, parked);
    std::vector<int> path = getPath(&graph, source, destination);

    out << (isFirstRun ? "BestDrivingRoute:" : "AlternativeDrivingRoute:");

    if (path.empty()) {
        out << "none" << std::endl;
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
/**
 * @brief Reads user input and computes the best and alternative routes.
 *
 * The function reads the user for the source, destination, and mode of transport.
 * Then computes the best route and an alternative route by avoiding the intermediate nodes.
 *
 * @param graph The graph where to search.
 *
 * Complexity O((V + E) log V).
 */

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
/**
 * @brief Reads input from a file and computes the best and alternative routes to an output file.
 *
 * This function reads the route request from an input file and writes the results to an output file.
 * (Batch mode)
 *
 * @param graph The graph where to search.
 * @param inputFilename Input file containing route queries.
 * @param outputFilename Output file to store the results.
 *
 * Complexity O((V + E) log V).
 */

void independentBatch(Graph<int> &graph, const std::string &inputFilename, const std::string &outputFilename) {
    std::ifstream file(inputFilename);
    if (!file) {
        std::cerr << "Error: Could not open file " << inputFilename << std::endl;
        return;
    }

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

    outputFile << "Source:" << source << "\nDestination:" << destination << std::endl;

    runAlgorithm(graph, source, destination, avoidNodes, mode, parked, outputFile, true);
    runAlgorithm(graph, source, destination, avoidNodes, mode, parked, outputFile, false);
}

