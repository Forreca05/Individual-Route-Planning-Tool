#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include "algorithms.h"
#include "independent.h"

void runAlgorithm(Graph<int> &graph, int source, int destination, std::unordered_set<int> &avoidNodes,
                  std::unordered_set<int> &avoidEdges, const std::string &mode, bool parked,
                  std::ostream &out, bool isFirstRun) {
    dijkstra(&graph, source, destination, avoidNodes, avoidEdges, mode, parked);
    std::vector<int> path = getPath(&graph, source, destination);

    out << (isFirstRun ? "BestDrivingRoute:" : "AlternativeDrivingRoute:");

    if (path.empty()) {
        out << "none" << std::endl;
    } else {
        out << path.front();
        for (int i = 0; i < path.size(); i++) {
            out << "," << i;
            if (isFirstRun && i != source && i != destination) {
                avoidNodes.insert(i);
            }
        }
        out << "(" << graph.findVertex(destination)->getDist() << ")" << std::endl;
    }
}

void independent(Graph<int> &graph) {
    std::string sourceStr, destinationStr, mode;
    std::unordered_set<int> avoidNodes, avoidEdges;
    bool parked = false;

    std::cout << "Mode: "; std::cin >> mode;
    std::cout << "Source: "; std::cin >> sourceStr;
    std::cout << "Destination: "; std::cin >> destinationStr;

    int source = std::stoi(sourceStr), destination = std::stoi(destinationStr);

    runAlgorithm(graph, source, destination, avoidNodes, avoidEdges, mode, parked, std::cout, true);
    runAlgorithm(graph, source, destination, avoidNodes, avoidEdges, mode, parked, std::cout, false);
}

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

    if (source == -1 || destination == -1) {
        std::cerr << "Error: Invalid input data" << std::endl;
        return;
    }

    outputFile << "Source:" << source << "\nDestination:" << destination << std::endl;

    runAlgorithm(graph, source, destination, avoidNodes, avoidEdges, mode, parked, outputFile, true);
    runAlgorithm(graph, source, destination, avoidNodes, avoidEdges, mode, parked, outputFile, false);
}
