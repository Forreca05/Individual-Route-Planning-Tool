//
// Created by forreca05 on 04-03-2025.
//

#include <iostream>
#include "Graph.h"
#include "utils.h"
#include "algorithms.h"

int main() {

    // User interface
    std::string mode, sourceStr, destinationStr;
    std::cout << "Mode: ";
    std::cin >> mode;
    std::cout << "Source: ";
    std::cin >> sourceStr;
    std::cout << "Destination: ";
    std::cin >> destinationStr;
    int source = std::stoi(sourceStr);
    int destination = std::stoi(destinationStr);

    // Carregar o grafo a partir dos CSVs
    Graph<int> graph = loadGraphFromCSV("../data/Locations.csv", "../data/Distances.csv");

    std::unordered_set<int> avoidNodes;
    dijkstraDriving(&graph, source, destination, avoidNodes);

    std::vector<int> path = getPath(&graph, source, destination);
    std::cout << "Best path: ";
    for (int i : path) {
        std::cout << i << " ";
        if (i != source && i != destination) avoidNodes.insert(i);
    }
    std::cout << "(distance = " << graph.findVertex(destination)->getDist() << ")" << std::endl;

    dijkstraDriving(&graph, source, destination, avoidNodes);
    path = getPath(&graph, source, destination);

    std::cout << "Alternative path: ";
    for (int i : path) {
        std::cout << i << " ";
    }
    std::cout << "(distance = " << graph.findVertex(destination)->getDist() << ")" << std::endl;
}