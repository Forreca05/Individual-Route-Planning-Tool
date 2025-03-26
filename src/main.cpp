#include <iostream>
#include <unordered_set>
#include "Graph.h"
#include "utils.h"
#include "algorithms.h"
#include <sstream>
#include "independent.cpp"
#include "restricted.cpp"
#include "environmentally.cpp"

int main() {
    Graph<int> graph = loadGraphFromCSV("../data/Locations.csv", "../data/Distances.csv");
    std::string type, batchStr;

    std::cout << "Batch or Terminal: ";
    std::cin >> batchStr;

    if (batchStr == "terminal") {
    	std::cout << "Type: ";
    	std::cin >> type;

    	if (type == "independent") {independent(graph);}
    	else if (type == "restricted") {restricted(graph);}
    	else if (type == "environmentally") {environmentally(graph);}
    	else {std::cerr << "Invalid type. Please enter 'independent', 'restricted', or 'environmentally'." << std::endl;}
    }

    else if (batchStr == "batch") {
		std::cout << "Type: ";
    	std::cin >> type;

        if (type == "independent") {independentBatch(graph, "../input.txt", "../output.txt");}
        //else if (type == "restricted") {restrictedBatch(graph, "../input.txt");}
        else if (type == "environmentally") {environmentallyBatch(graph, "../input.txt");}
        else {std::cerr << "Invalid type. Please enter 'independent', 'restricted', or 'environmentally'." << std::endl;}
    }

    return 0;
}
