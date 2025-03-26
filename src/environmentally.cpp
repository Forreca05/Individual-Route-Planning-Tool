#include <iostream>
#include <unordered_set>
#include <sstream>
#include <string>
#include "algorithms.h"
#include "Graph.h"

void environmentally(Graph<int> &graph) {
    std::string sourceStr, destinationStr, mode, segment;
    int node, maxWalk, avoidInit, avoidEnd;
    std::unordered_set<int> avoidNodes;
    std::unordered_set<int> avoidEdges;

    // Entrada de dados
    std::cout << "Mode: ";
    std::cin >> mode;

    if (mode != "driving-walking") {
        std::cout << "Invalid mode. Exiting function." << std::endl;
        return;
    }

    std::cout << "Source: ";
    std::cin >> sourceStr;
    std::cout << "Destination: ";
    std::cin >> destinationStr;

    int source = std::stoi(sourceStr);
    int destination = std::stoi(destinationStr);

    std::cout << "MaxWalkTime: ";
    std::cin >> maxWalk;

    // Coleta de nós a evitar
    std::cout << "AvoidNodes (enter -1 to stop): ";
    while (std::cin >> node && node != -1) {
        avoidNodes.insert(node);
    }

    // Coleta de segmentos a evitar
    std::cout << "AvoidSegments (enter -1 to stop): ";
    while (std::cin >> segment && segment != "-1") {
        size_t openParen = segment.find('(');
        size_t closeParen = segment.find(')');
        if (openParen != std::string::npos && closeParen != std::string::npos && openParen < closeParen) {
            segment = segment.substr(openParen + 1, closeParen - openParen - 1);
        } else {
            std::cerr << "Invalid segment format. Use (x,y)" << std::endl;
            continue;
        }

        std::stringstream ss(segment);
        char comma;
        if (ss >> avoidInit >> comma >> avoidEnd && comma == ',') {
            avoidEdges.insert(avoidInit);
            avoidEdges.insert(avoidEnd);
        } else {
            std::cerr << "Invalid segment input." << std::endl;
        }
    }

    // Aqui você pode chamar o algoritmo desejado, como Dijkstra, A* etc.
    // Exemplo:
    // dijkstra(&graph, source, destination, avoidNodes, avoidEdges, mode);
}

void environmentallyBatch(Graph<int> &graph, const std::string &filename) {}