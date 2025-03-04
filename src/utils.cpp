#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

Graph<int> loadGraphFromCSV(const std::string &locationsFile, const std::string &distancesFile) {
    Graph<int> graph;

    // Ler Locations.csv
    std::ifstream locations(locationsFile);  // Caminho para o arquivo de locais
    if (!locations.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << locationsFile << std::endl;
        return graph;
    }

    std::string line;
    std::getline(locations, line);  // Pular cabeçalho

    while (std::getline(locations, line)) {
        std::istringstream stream(line);
        std::string location, nodeIdStr, code, parkingStr;
        std::getline(stream, location, ',');
        std::getline(stream, nodeIdStr, ',');
        std::getline(stream, code, ',');
        std::getline(stream, parkingStr, ',');

        int nodeId = std::stoi(nodeIdStr);
        bool hasParking = (parkingStr == "1");

        graph.addVertex(nodeId);  // Adiciona vértice
    }

    // Ler Distances.csv
    std::ifstream distances(distancesFile);  // Caminho para o arquivo de distâncias
    if (!distances.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << distancesFile << std::endl;
        return graph;
    }

    std::getline(distances, line);  // Pular cabeçalho

    while (std::getline(distances, line)) {
        std::istringstream stream(line);
        std::string loc1Str, loc2Str, drivingStr, walkingStr;
        std::getline(stream, loc1Str, ',');
        std::getline(stream, loc2Str, ',');
        std::getline(stream, drivingStr, ',');
        std::getline(stream, walkingStr, ',');

        int loc1 = std::stoi(loc1Str);
        int loc2 = std::stoi(loc2Str);
        int drivingTime = (drivingStr == "X") ? -1 : std::stoi(drivingStr);  // Use -1 para "X"
        int walkingTime = std::stoi(walkingStr);

        // Adiciona as arestas
        graph.addEdge(loc1, loc2, drivingTime);
        graph.addEdge(loc2, loc1, drivingTime);  // Se for bidirecional
    }

    return graph;
}
