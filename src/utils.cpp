#include <iostream>
#include "utils.h"
#include "MutablePriorityQueue.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>

Graph<int> loadGraphFromCSV(const std::string &locationsFile, const std::string &distancesFile) {
    Graph<int> graph;
    std::unordered_map<std::string, int> code_to_id; // Mapeia código -> ID numérico

    // Ler Locations.csv
    std::ifstream locations(locationsFile);
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

        bool hasParking = (parkingStr == "1");
        int nodeId = std::stoi(nodeIdStr);
        code_to_id[code] = nodeId; // Guarda o código associado ao ID

        // Adiciona o vértice ao grafo
        graph.addVertex(nodeId);
        Vertex<int>* v = graph.findVertex(nodeId);
        if (v) {
            v->setHasParking(hasParking);
            v->setLocation(location);
            v->setCode(code);
        }
    }

    locations.close();

    // Ler Distances.csv
    std::ifstream distances(distancesFile);
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

        if (code_to_id.find(loc1Str) == code_to_id.end() || code_to_id.find(loc2Str) == code_to_id.end()) {
            std::cerr << "Erro: Código de localização não encontrado (" << loc1Str << ", " << loc2Str << ")" << std::endl;
            continue;
        }

        int id1 = code_to_id[loc1Str];
        int id2 = code_to_id[loc2Str];

        int drivingTime = (drivingStr == "X") ? -1 : std::stoi(drivingStr);
        int walkingTime = std::stoi(walkingStr);

        graph.addBidirectionalEdge(id1, id2, walkingTime, drivingTime);
    }

    distances.close();

    return graph;
}
