#include <iostream>
#include <unordered_set>
#include <sstream>
#include <string>
#include "algorithms.h"
#include "Graph.h"

void environmentally(Graph<int> &graph) {
    std::string sourceStr, destinationStr, mode, segment;
    int node, maxWalk, avoidInit, avoidEnd;
    bool parked = false;
    std::unordered_set<int> avoidNodes;
    std::unordered_set<int> avoidEdges;
    std::unordered_map<int, double> time_to_id;

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
        segment = segment.substr(segment.find('(') + 1, segment.find(')') - segment.find('(') - 1);
        std::stringstream ss(segment);
        char comma;
        ss >> avoidInit >> comma >> avoidEnd;
        selectEdge(&graph, avoidInit, avoidEnd);
    }

    for (Vertex<int>* v : graph.getVertexSet()) {
        if (v->hasParking()) {  // Certifique-se de que `hasParking()` existe
            dijkstra(&graph, source, v->getInfo(), avoidNodes, avoidEdges, mode, parked);
            time_to_id[v->getInfo()] = graph.findVertex(v->getInfo())->getDist();  // Armazena a distância do nó de origem até o estacionamento
        }
    }
    // Imprimir os nós de estacionamento com suas distâncias
      std::cout << "\nParking Nodes and Distances:\n";
      for (const auto& pair : time_to_id) {
            std::cout << "Parking Node: " << pair.first << ", Distance: " << pair.second << std::endl;
      }
}

void environmentallyBatch(Graph<int> &graph, const std::string &filename) {}