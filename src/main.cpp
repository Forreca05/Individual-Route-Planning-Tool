/**
 * @file main.cpp
 * @brief Main program for loading a graph and performing various algorithms.
 *
 * This file contains the main logic for reading a graph from CSV files and
 * running different algorithms based on the user input. The program supports
 * both terminal-based interaction and batch processing modes. It performs
 * operations based on the specified type: independent, restricted, or environmentally.
 *
 * @author João Pascoal Faria
 * @date March 2025
 */

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

/**
 * @brief Entry point of the program.
 *
 * The main function initializes the graph and performs the corresponding
 * algorithm based on user input. The program supports two modes: terminal
 * and batch. In terminal mode, the user provides input interactively. In
 * batch mode, the program reads input from a file.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The array of arguments passed to the program.
 * @return int Return code indicating success or failure of execution.
 */
int main(int argc, char* argv[]) {
    std::string type, batchStr;

    // Check for the number of arguments to determine batch or terminal mode
    if (argc == 3) batchStr = "terminal"; // Terminal mode
    else if (argc == 5) batchStr = "batch"; // Batch mode
    else {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1; // Error: Invalid number of arguments
    }

    // Load the graph from the CSV files
    Graph<int> graph = loadGraphFromCSV(argv[1], argv[2]);

    if (batchStr == "terminal") {
        // Terminal interaction mode
        std::cout << "Type: ";
        std::cin >> type; // Get algorithm type from user

        if (type == "independent") {
            independent(graph); // Run the independent algorithm
        }
        else if (type == "restricted") {
            restricted(graph); // Run the restricted algorithm
        }
        else if (type == "environmentally") {
            environmentally(graph); // Run the environmentally-friendly algorithm
        }
        else {
            std::cerr << "Invalid type. Please enter 'independent', 'restricted', or 'environmentally'." << std::endl;
        }
    }

    else if (batchStr == "batch") {
        // Batch processing mode
        std::ifstream file(argv[3]);
        if (!file) {
            std::cerr << "Error: Could not open file " << argv[3] << std::endl;
            return 1; // Error: Could not open batch file
        }

        std::string line;
        std::getline(file, line); // Read first line
        std::istringstream iss(line);
        std::string key, value;

        // Process the line, dividing by ':' to extract key-value pairs
        if (std::getline(iss, key, ':') && std::getline(iss >> std::ws, value)) {
            if (key != "Type") {  // Ensure the key is "Type"
                std::cout << "Invalid input file" << std::endl;
                return 1; // Error: Invalid input file format
            }
            type = value; // Store the value for the type
        } else {
            std::cout << "Invalid input format" << std::endl;
            return 1; // Error: Invalid file format
        }

        file.close();

        // Call appropriate batch function based on type
        if (type == "independent") {
            independentBatch(graph, argv[3], argv[4]);
        }
        else if (type == "restricted") {
            restrictedBatch(graph, argv[3], argv[4]);
        }
        else if (type == "environmentally") {
            environmentallyBatch(graph, argv[3], argv[4]);
        }
        else {
            std::cerr << "Invalid type. Please enter 'independent', 'restricted', or 'environmentally'." << std::endl;
        }
    }

    return 0; // Successful execution
}
