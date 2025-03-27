#include <iostream>
#include <unordered_set>
#include <sstream>
#include <string>
#include "algorithms.h"
#include "Graph.h"

void environmentally(Graph<int> &graph) {
    std::string sourceStr, destinationStr, mode, segment;
    int node, maxWalk, avoidInit, avoidEnd, middle, total = 1000;
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

    parked = true;

    for (const auto& pair : time_to_id) {
        dijkstra(&graph, pair.first, destination, avoidNodes, avoidEdges, mode, parked);
        if (graph.findVertex(destination)->getDist() <= maxWalk) {
          int distt = pair.second + graph.findVertex(destination)->getDist();
          if (distt < total) {
            total = distt;
            middle = pair.first;
          }
        }
    }
    std::cout << total << ' ' << middle << std::endl;

    dijkstra(&graph, source, middle, avoidNodes, avoidEdges, mode, parked);
    std::vector<int> path = getPath(&graph, source, middle);
    dijkstra(&graph, middle, destination, avoidNodes, avoidEdges, mode, parked);
    std::vector<int> path2 = getPath(&graph, middle, destination);
    path.insert(path.end(), path2.begin() + 1, path2.end());
    if (path.empty()) {
        std::cout << "RestrictedDrivingRoute: none" << std::endl;
    } else {
        std::cout << "RestrictedDrivingRoute: ";
        for (int i : path) {
            std::cout << i << " ";
        }
        std::cout << " (" << total << ")" << std::endl;
   }
}

void environmentallyBatch(Graph<int> &graph, const std::string &filename) {}