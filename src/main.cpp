#include <iostream>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include "Graph.h"
#include "utils.h"
#include "algorithms.h"
#include "independent.h"
#include "restricted.h"
#include "environmentally.h"

int main(int argc, char* argv[]) {
    std::string type, batchStr;
    if (argc == 3) batchStr = "terminal";
    else if (argc == 5) batchStr = "batch";
    else {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }
    Graph<int> graph = loadGraphFromCSV(argv[1], argv[2]);

    if (batchStr == "terminal") {
    	std::cout << "Type: ";
    	std::cin >> type;

    	if (type == "independent") {independent(graph);}
    	else if (type == "restricted") {restricted(graph);}
    	else if (type == "environmentally") {environmentally(graph);}
    	else {std::cerr << "Invalid type. Please enter 'independent', 'restricted', or 'environmentally'." << std::endl;}
    }

    else if (batchStr == "batch") {

        std::ifstream file(argv[3]);
        if (!file) {
            std::cerr << "Error: Could not open file " << argv[3] << std::endl;
            return 1;
        }

        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);
        std::string key, value;

        // Divide a string pelo ':'
        if (std::getline(iss, key, ':') && std::getline(iss >> std::ws, value)) {
            if (key != "Type") {  // Agora, "Type:" será lido como "Type"
                std::cout << "Invalid input file" << std::endl;
                return 1;
            }
            type = value; // Armazena o valor corretamente
        } else {
            std::cout << "Invalid input format" << std::endl;
            return 1;
        }

        file.close();

        if (type == "independent") {independentBatch(graph, argv[3], argv[4]);}
        else if (type == "restricted") {restrictedBatch(graph, argv[3], argv[4]);}
        else if (type == "environmentally") {environmentallyBatch(graph, argv[3], argv[4]);}
        else {std::cerr << "Invalid type. Please enter 'independent', 'restricted', or 'environmentally'." << std::endl;}
    }

    return 0;
}
