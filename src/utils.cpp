/**
 * @file utils.cpp 
 * @brief Implementation of utilitary functions to load a graph parsing from a CSV file.
 * 
 * This file contains the implementation of the function that parses the CSV files keeping 
 * the information about locations and distances and loads them into a graph.
 * 
 * 
 * 
 *  */
#include <iostream>
#include "utils.h"
#include "MutablePriorityQueue.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>

/**
 * @brief load a graph from CSV files. 
 * 
 * Reads two CSV files with the information about locations and distances 
 * and biuld the corresponding graph.
 * 
 * @param locationsFile Path to the Locations.csv file.
 * @param distanceSFile Path to the Distances.csv file.
 * @return A Graph<int> object containing the data form both files.
 * 
 * complexity is O(L + E), where L is the number of locations and E the umber of edges [O(n)]
 */

Graph<int> loadGraphFromCSV(const std::string &locationsFile, const std::string &distancesFile) {
    Graph<int> graph;
    std::unordered_map<std::string, int> code_to_id; ///<Maps the locations code to a numeric id

    // Locations.csv
    std::ifstream locations(locationsFile);
    if (!locations.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << locationsFile << std::endl;
        return graph;
    }

    std::string line;
    std::getline(locations, line);  // Skip header

    while (std::getline(locations, line)) {
        std::istringstream stream(line);
        std::string location, nodeIdStr, code, parkingStr;
        std::getline(stream, location, ',');
        std::getline(stream, nodeIdStr, ',');
        std::getline(stream, code, ',');
        std::getline(stream, parkingStr, ',');


        bool hasParking = (std::stoi(parkingStr) == 1);
        int nodeId = std::stoi(nodeIdStr);
        code_to_id[code] = nodeId; ///< Assocciates location code to its id 

        // Adds vertex to the graph
        graph.addVertex(nodeId);
        Vertex<int>* v = graph.findVertex(nodeId);
        if (v) {
            v->setHasParking(hasParking);
            v->setLocation(location);
            v->setCode(code);
        }
    }

    locations.close();

    // Read Distances.csv
    std::ifstream distances(distancesFile);
    if (!distances.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << distancesFile << std::endl;
        return graph;
    }

    std::getline(distances, line);  // Skip header

    while (std::getline(distances, line)) {
        std::istringstream stream(line);
        std::string loc1Str, loc2Str, drivingStr, walkingStr;
        std::getline(stream, loc1Str, ',');
        std::getline(stream, loc2Str, ',');
        std::getline(stream, drivingStr, ',');
        std::getline(stream, walkingStr, ',');

        //Verifies if locations exist in the map
        if (code_to_id.find(loc1Str) == code_to_id.end() || code_to_id.find(loc2Str) == code_to_id.end()) {
            std::cerr << "Erro: Código de localização não encontrado (" << loc1Str << ", " << loc2Str << ")" << std::endl;
            continue;
        }

        int id1 = code_to_id[loc1Str];
        int id2 = code_to_id[loc2Str];

        int drivingTime = (drivingStr == "X") ? -1 : std::stoi(drivingStr); ///< Driving time. (-1 when not appliable)
        int walkingTime = std::stoi(walkingStr);///< Walking time.

        //Adds bidirectional edjes to the graph
        graph.addBidirectionalEdge(id1, id2, walkingTime, drivingTime);
    }

    distances.close();

    return graph;
}
