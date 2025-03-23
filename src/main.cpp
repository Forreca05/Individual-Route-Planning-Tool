#include <iostream>
#include <unordered_set>
#include "Graph.h"
#include "utils.h"
#include "algorithms.h"
#include <sstream>

int main() {
    Graph<int> graph = loadGraphFromCSV("../data/Locations.csv", "../data/Distances.csv");
    std::string type, mode, sourceStr, destinationStr;
    std::unordered_set<int> avoidNodes;
    std::unordered_set<int> avoidEdges;

    std::cout << "Type: ";
    std::cin >> type;

    if (type == "independent") {
        std::cout << "Mode: ";
        std::cin >> mode;
        if (mode != "driving") {return 0;}
        std::cout << "Source: ";
        std::cin >> sourceStr;
        std::cout << "Destination: ";
        std::cin >> destinationStr;

        int source = std::stoi(sourceStr);
        int destination = std::stoi(destinationStr);

        dijkstraDriving(&graph, source, destination, avoidNodes, avoidEdges);
        std::vector<int> path = getPath(&graph, source, destination);

        std::cout << "BestDrivingRoute: ";
        for (int i : path) {
            std::cout << i << " ";
            if (i != source && i != destination) avoidNodes.insert(i);
        }
        std::cout << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;

        dijkstraDriving(&graph, source, destination, avoidNodes, avoidEdges);
        path = getPath(&graph, source, destination);

        if (path.empty()) {
    		std::cout << "AlternativeDrivingRoute: none" << std::endl;
		} else {
    		std::cout << "AlternativeDrivingRoute: ";
    		for (int i : path) {
        		std::cout << i << " ";
    		}
    	std::cout << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;
		}
    }

    else if (type == "restricted") {
        int node, includeNode, avoidinit, avoidend;
        std::string segment;

        std::cout << "Mode: ";
        std::cin >> mode;
        if (mode != "driving") {return 0;}
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

        dijkstraDriving(&graph, source, destination, avoidNodes, avoidEdges);
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

    else if (type == "environmentaly") {
        int node, segment, maxWalk;

        std::cout << "Mode: ";
        std::cin >> mode;
        if (mode != "driving-walking") {return 0;}
        std::cout << "Source: ";
        std::cin >> sourceStr;
        std::cout << "Destination: ";
        std::cin >> destinationStr;

        int source = std::stoi(sourceStr);
        int destination = std::stoi(destinationStr);

        std::cout << "MaxWalkTime:";
        std::cin >> maxWalk;

        std::cout << "AvoidNodes (enter -1 to stop): ";
        while (std::cin >> node && node != -1) {
            avoidNodes.insert(node);
        }

        std::cout << "AvoidSegments (enter -1 to stop): ";
        while (std::cin >> segment && segment != -1) {
        }
    }

    else {
        std::cerr << "Invalid type. Please enter 'independent', 'restricted', or 'environmentaly'." << std::endl;
    }

    return 0;
}
