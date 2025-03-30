/**
 * @file environmentally.cpp. 
 * @brief Implentation of the algorithm that computes the best route with both walking and driving.
 * 
 * Computes routes that combine driving and walking, allowing users to:
 * Drive the first section of the route and then park the vehicle.
 * Walk the remaining distance to the destination.
 * There is also a max walking time. ( Time the user is willing to walk after parking.)
 * 
 */

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <string>
#include "algorithms.h"
#include "Graph.h"
#include "environmentally.h"

/**
 * @brief Runs the environmentally friendly route algorithm.
 * 
 * This function calculates a route that minimizes driving distance while ensuring the walking distance
 * from a parking node to the destination does not exceed a given maximum.
 *
 * @param graph The graph where to search.
 * @param source The starting node.
 * @param destination The target node.
 * @param maxWalk The maximum walking distance the user is willing to walk.
 * @param avoidNodes Set of nodes to be avoided.
 * @param time_to_id Map of parking nodes to their respective driving times.
 * @param mode The mode of transportation (only "driving-walking" is valid).
 * @param parked Indicates of there is parking avaliable.
 * @param out The output stream to write the result.
 * 
 * Complexity is O((V + E) log V), where V is the number of vertices and E is the number of edges, 
 * since Dijkstra's algorithm is used multiple times. [O(n log(n))]
 */

void runEnvironmentallyAlgorithm(Graph<int>& graph, int source, int destination, int maxWalk,
                                  std::unordered_set<int>& avoidNodes, std::unordered_map<int,
                                  double>& time_to_id, const std::string &mode, bool parked, std::ostream &out) {

    int total = 100000, middle = -1;
    double prevWalkDist = 0;
    bool route = false;

    parked = true;
    for (const auto& pair : time_to_id) {
        if (pair.second == INF) continue;
        dijkstra(&graph, pair.first, destination, avoidNodes, mode, parked);
        if (graph.findVertex(destination)->getDist() <= maxWalk) {
            route = true;
            int distt = pair.second + graph.findVertex(destination)->getDist();
            if (distt < total || (distt == total && graph.findVertex(destination)->getDist() > prevWalkDist)) {
                total = distt;
                middle = pair.first;
                prevWalkDist = graph.findVertex(destination)->getDist();
            }
        }
    }
    
    if (!route) {
        // out << "Source:" << source << "\nDestination:" << destination << std::endl;
        // out << "DrivingRoute:" << std::endl;
        // out << "ParkingNode:" << std::endl;
        // out << "WalkingRoute:" << std::endl;
        // out << "TotalTime:" << std::endl;
        // out << "Message:No possible route with max. walking time of " << maxWalk << " minutes." << std::endl;
        // return;

        while (!route) {
            maxWalk++;
            // Arbitrary high value to avoid infinite loops, could be anything
            if (maxWalk > 100000) {
                break;
            }
            for (const auto& pair : time_to_id) {
                if (pair.second == INF) continue;
                dijkstra(&graph, pair.first, destination, avoidNodes, mode, parked);
                if (graph.findVertex(destination)->getDist() <= maxWalk) {
                    route = true;
                    int distt = pair.second + graph.findVertex(destination)->getDist();
                    if (distt < total || (distt == total && graph.findVertex(destination)->getDist() > prevWalkDist)) {
                        total = distt;
                        middle = pair.first;
                        prevWalkDist = graph.findVertex(destination)->getDist();
                    }
                }
            }
        }

        if (route){parked = false;
        dijkstra(&graph, source, middle, avoidNodes, mode, parked);
        std::vector<int> path = getPath(&graph, source, middle);
        int meioDist = graph.findVertex(middle)->getDist();
        out << "Source:" << source << std::endl << "Destination:" << destination << std::endl;
        out << "DrivingRoute1:" << path[0];
        for (unsigned i = 1; i < path.size(); i++) {
            out << ',' << path[i];
        }
        out << "(" << meioDist << ")" << std::endl;

        out << "ParkingNode1:" << middle << std::endl;

        parked = true;
        dijkstra(&graph, middle, destination, avoidNodes, mode, parked);
        std::vector<int> path2 = getPath(&graph, middle, destination);
        out << "WalkingRoute1:" << path2[0];
        for (unsigned i = 1; i < path2.size(); i++) {
            out << ',' << path2[i];
        }
        int fimDist = graph.findVertex(destination)->getDist();
        out << "(" << fimDist << ")" << std::endl;

        out << "TotalTime1:" << total << std::endl;

        int prevMiddle = middle;
        avoidNodes.insert(destination);
        for (Vertex<int>* v : graph.getVertexSet()) {
            if (v->hasParking()) {
                dijkstra(&graph, source, v->getInfo(), avoidNodes, "driving", parked);
                time_to_id[v->getInfo()] = graph.findVertex(v->getInfo())->getDist();
            }
        }
        avoidNodes.erase(destination);

        time_to_id[prevMiddle] = 1000000;
        total = 100000, middle = -1;
        prevWalkDist = 0;
        route = false;
        parked = true;
        while (!route) {
            for (const auto& pair : time_to_id) {
                if (pair.second == INF) continue;
                dijkstra(&graph, pair.first, destination, avoidNodes, mode, parked);
                if (graph.findVertex(destination)->getDist() <= maxWalk) {
                    int distt = pair.second + graph.findVertex(destination)->getDist();
                    if (pair.second != INF && (distt < total || (distt == total && graph.findVertex(destination)->getDist() > prevWalkDist))) {
                        route = true;
                        total = distt;
                        middle = pair.first;
                        prevWalkDist = graph.findVertex(destination)->getDist();
                    }
                }
            }
            maxWalk++;
        }
        
        parked = false;
        avoidNodes.insert(destination);
        dijkstra(&graph, source, middle, avoidNodes, mode, parked);
        avoidNodes.erase(destination);
        path = getPath(&graph, source, middle);
        meioDist = graph.findVertex(middle)->getDist();
        out << "DrivingRoute2:" << path[0];
        for (unsigned i = 1; i < path.size(); i++) {
            out << ',' << path[i];
        }
        out << "(" << meioDist << ")" << std::endl;

        out << "ParkingNode2:" << middle << std::endl;

        parked = true;
        dijkstra(&graph, middle, destination, avoidNodes, mode, parked);
        path2 = getPath(&graph, middle, destination);
        out << "WalkingRoute2:" << path2[0];
        for (unsigned i = 1; i < path2.size(); i++) {
            out << ',' << path2[i];
        }
        fimDist = graph.findVertex(destination)->getDist();
        out << "(" << fimDist << ")" << std::endl;

        out << "TotalTime2:" << total << std::endl;
        return;}
    }

    if (!route) {
        out << "There is no possible route" << std::endl;
        return;
    }
    parked = false;
    avoidNodes.insert(destination);
    dijkstra(&graph, source, middle, avoidNodes, mode, parked);
    avoidNodes.erase(destination);
    std::vector<int> path = getPath(&graph, source, middle);
    int meioDist = graph.findVertex(middle)->getDist();
    std::cout << meioDist << std::endl;
    out << "Source:" << source << std::endl << "Destination:" << destination << std::endl;
    out << "DrivingRoute:" << path[0];
    for (unsigned i = 1; i < path.size(); i++) {
        out << ',' << path[i];
    }
    out << "(" << meioDist << ")" << std::endl;

    out << "ParkingNode:" << middle << std::endl;

    parked = true;
    dijkstra(&graph, middle, destination, avoidNodes, mode, parked);
    std::vector<int> path2 = getPath(&graph, middle, destination);
    out << "WalkingRoute:" << path2[0];
    for (unsigned i = 1; i < path2.size(); i++) {
        out << ',' << path2[i];
    }
    int fimDist = graph.findVertex(destination)->getDist();
    out << "(" << fimDist << ")" << std::endl;

    out << "TotalTime:" << total << std::endl;

    path.insert(path.end(), path2.begin() + 1, path2.end());  // Junta as duas rotas
}

/**
 * @brief Processes a batch file for the environemental pathfinding.
 * 
 * This function reads user inputs for mode(must be "driving-walking"), processes them, and calls the environmentally friendly route algorithm.
 * 
 * @param graph The graph where to search.
 * 
 * Complexity is O(V log V + E), due to multiple executions of Dijkstra's algorithm.
 */

void environmentally(Graph<int>& graph) {
    std::string sourceStr, destinationStr, mode, segment;
    int maxWalk;
    bool parked = false;
    std::unordered_set<int> avoidNodes;
    std::unordered_set<int> avoidEdges;
    std::unordered_map<int, double> time_to_id;

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

    std::cout << "AvoidNodes: ";
    std::string line;
    std::cin.ignore();
    std::getline(std::cin, line);
    if (!line.empty()) {
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            try {
                avoidNodes.insert(std::stoi(token));
            } catch (...) {
                std::cerr << "Warning: Ignoring invalid AvoidNodes value: " << token << std::endl;
            }
        }
    }

    std::cout << "AvoidSegments: ";
    std::getline(std::cin, line);
    if (!line.empty()) {
        size_t pos = 0;
        while ((pos = line.find('(')) != std::string::npos) {
            size_t closeParen = line.find(')', pos);
            if (closeParen == std::string::npos) break;

            std::string edge = line.substr(pos + 1, closeParen - pos - 1);
            line = line.substr(closeParen + 1);

            std::stringstream edgeStream(edge);
            int start, end;
            char comma;
            if (edgeStream >> start >> comma >> end && comma == ',') {
                selectEdge(&graph, start, end);
            } else {
                std::cerr << "Warning: Invalid AvoidSegments format: " << edge << std::endl;
            }
        }
    }

    avoidNodes.insert(destination);
    for (Vertex<int>* v : graph.getVertexSet()) {
        if (v->hasParking()) {
            dijkstra(&graph, source, v->getInfo(), avoidNodes, "driving", parked);
            time_to_id[v->getInfo()] = graph.findVertex(v->getInfo())->getDist();
        }
    }
    avoidNodes.erase(destination);

    runEnvironmentallyAlgorithm(graph, source, destination, maxWalk, avoidNodes, time_to_id, mode, parked, std::cout);
}

/**
 * @brief Reads input from a file and computes the environmental routes to an output file.
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

void environmentallyBatch(Graph<int>& graph, const std::string& filename, const std::string& outputFilename) {
    std::unordered_set<int> avoidNodes;
    std::unordered_set<int> avoidEdges;
    std::unordered_map<int, double> time_to_id;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Error: Could not open file " << outputFilename << std::endl;
        return;
    }

    std::string line, mode;
    int source, destination, maxWalk;
    bool parked = false;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, ':') && std::getline(iss >> std::ws, value)) {
            if (key == "Mode") mode = value;
            else if (key == "Source") source = std::stoi(value);
            else if (key == "Destination") destination = std::stoi(value);
            else if (key == "MaxWalkTime") maxWalk = std::stoi(value);
            else if (key == "AvoidNodes" && !value.empty()) {
                std::stringstream ss(value);
                std::string token;
                while (std::getline(ss, token, ',')) {
                    try {
                        avoidNodes.insert(std::stoi(token));
                    } catch (...) {
                        std::cerr << "Warning: Ignoring invalid AvoidNodes value: " << token << std::endl;
                    }
                }
            } else if (key == "AvoidSegments" && !value.empty()) {
                size_t pos = 0;
                while ((pos = value.find('(')) != std::string::npos) {
                    size_t closeParen = value.find(')', pos);
                    if (closeParen == std::string::npos) break;

                    std::string edge = value.substr(pos + 1, closeParen - pos - 1);
                    value = value.substr(closeParen + 1);

                    std::stringstream edgeStream(edge);
                    int start, end;
                    char comma;
                    if (edgeStream >> start >> comma >> end && comma == ',') {
                        selectEdge(&graph, start, end);
                    } else {
                        std::cerr << "Warning: Invalid AvoidSegments format: " << edge << std::endl;
                    }
                }
            }
        }
    }

    file.close();

    avoidNodes.insert(destination);
    for (Vertex<int>* v : graph.getVertexSet()) {
        if (v->hasParking()) {
            dijkstra(&graph, source, v->getInfo(), avoidNodes, mode, parked);
            time_to_id[v->getInfo()] = graph.findVertex(v->getInfo())->getDist();
        }
    }
    avoidNodes.erase(destination);

    runEnvironmentallyAlgorithm(graph, source, destination, maxWalk, avoidNodes, time_to_id, mode, parked, outputFile);
    outputFile.close();
}