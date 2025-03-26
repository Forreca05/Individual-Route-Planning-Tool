#include <iostream>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <string>
#include "algorithms.h"
#include "Graph.h"

void restricted(Graph<int> &graph) {
    int node, includeNode, avoidinit, avoidend;
    std::string mode, sourceStr, destinationStr;
	std::unordered_set<int> avoidNodes; // Definição do conjunto de nós a evitar
	std::unordered_set<int> avoidEdges; // Apenas declarado caso precise no futuro
    std::string segment;

    std::cout << "Mode: ";
    std::cin >> mode;
    std::cout << "Source: ";
    std::cin >> sourceStr;
    std::cout << "Destination: ";
    std::cin >> destinationStr;

    int source = std::stoi(sourceStr);
    int destination = std::stoi(destinationStr);

    std::cout << "AvoidNodes (enter -1 to stop): ";
    while (std::cin >> node && node != -1) {
        avoidNodes.insert(node);
    }

    std::cout << "AvoidSegments (enter -1 to stop): ";
    while (std::cin >> segment && segment != "-1") {
        segment = segment.substr(segment.find('(') + 1, segment.find(')') - segment.find('(') - 1);
	    std::stringstream ss(segment);
    	char comma;
    	ss >> avoidinit >> comma >> avoidend;
		selectEdge(&graph, avoidinit, avoidend);
    }

    std::cout << "IncludeNode: ";
    std::cin >> includeNode;

    if (includeNode != -1) {
        dijkstra(&graph, source, includeNode, avoidNodes, avoidEdges, mode);
        std::vector<int> path = getPath(&graph, source, includeNode);
        dijkstra(&graph, includeNode, destination, avoidNodes, avoidEdges, mode);
        std::vector<int> path2 = getPath(&graph, includeNode, destination);
        path.insert(path.end(), path2.begin() + 1, path2.end());
        if (path.empty()) {
        	std::cout << "RestrictedDrivingRoute: none" << std::endl;
        } else {
        	std::cout << "RestrictedDrivingRoute: ";
        	for (int i : path) {
        		std::cout << i << " ";
        	}
        	std::cout << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;
        }
    }

    dijkstra(&graph, source, destination, avoidNodes, avoidEdges, mode);
    std::vector<int> path = getPath(&graph, source, destination);

    if (path.empty()) {
       std::cout << "RestrictedDrivingRoute: none" << std::endl;
    } else {
		std::cout << "RestrictedDrivingRoute: ";
        for (int i : path) {
            std::cout << i << " ";
        }
        std::cout << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;
    }
}

void restrictedBatch(Graph<int> &graph, const std::string &filename, const std::string &outputFilename) {

}
