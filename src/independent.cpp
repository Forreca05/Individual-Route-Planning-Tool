#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include "algorithms.h"
#include "Graph.h"

void independent(Graph<int> &graph) {
    std::string sourceStr, destinationStr, mode;
    bool parked = false;
    std::unordered_set<int> avoidNodes; // Definição do conjunto de nós a evitar
    std::unordered_set<int> avoidEdges; // Apenas declarado caso precise no futuro

    // Entrada de dados
    std::cout << "Mode: ";
    std::cin >> mode;
    std::cout << "Source: ";
    std::cin >> sourceStr;
    std::cout << "Destination: ";
    std::cin >> destinationStr;

    int source = std::stoi(sourceStr);
    int destination = std::stoi(destinationStr);

    // 1ª Execução do algoritmo de Dijkstra
    dijkstra(&graph, source, destination, avoidNodes, avoidEdges, mode, parked);
    std::vector<int> path = getPath(&graph, source, destination);

    // Impressão da melhor rota
    std::cout << "BestDrivingRoute: ";
    if (path.empty()) {
        std::cout << "none" << std::endl;
        return;
    }

    for (int i : path) {
        std::cout << i << " ";
        if (i != source && i != destination) {
            avoidNodes.insert(i);  // Marcar nós para evitar na próxima busca
        }
    }
    std::cout << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;

    // 2ª Execução do algoritmo para encontrar rota alternativa
    dijkstra(&graph, source, destination, avoidNodes, avoidEdges, mode, parked);
    path = getPath(&graph, source, destination);

    // Impressão da rota alternativa
    std::cout << "AlternativeDrivingRoute: ";
    if (path.empty()) {
        std::cout << "none" << std::endl;
    } else {
        for (int i : path) {
            std::cout << i << " ";
        }
        std::cout << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;
    }
}

void independentBatch(Graph<int> &graph, const std::string &filename, const std::string &outputFilename) {
    std::unordered_set<int> avoidNodes; // Definição do conjunto de nós a evitar
    std::unordered_set<int> avoidEdges; // Apenas declarado caso precise no futuro
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Abra o arquivo de saída
    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Error: Could not open file " << outputFilename << std::endl;
        return;
    }

    std::string line, mode;
    int source, destination;
    bool parked = false;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;

        while (iss >> key >> value) {
            if (key == "Mode:") {
                mode = value;
            } else if (key == "Source:") {
                source = std::stoi(value);
            } else if (key == "Destination:") {
                destination = std::stoi(value);
            }
        }
    }

    file.close();  // Fecha o ficheiro após a leitura

    // Escreve os valores lidos no arquivo de saída
    outputFile << "Mode: " << mode << std::endl;
    outputFile << "Source: " << source << std::endl;
    outputFile << "Destination: " << destination << std::endl;

    // Chama o algoritmo necessário (Dijkstra, A*, etc.)
    dijkstra(&graph, source, destination, {}, {}, mode, parked);
    std::vector<int> path = getPath(&graph, source, destination);

    outputFile << "BestDrivingRoute: ";
    for (int i : path) {
        outputFile << i << " ";
        if (i != source && i != destination) {
            avoidNodes.insert(i);  // Marcar nós para evitar na próxima busca
        }
    }
    outputFile << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;

    // 2ª Execução do algoritmo para encontrar rota alternativa
    dijkstra(&graph, source, destination, avoidNodes, avoidEdges, mode, parked);
    path = getPath(&graph, source, destination);

    // Escreve a rota alternativa no arquivo
    outputFile << "AlternativeDrivingRoute: ";
    if (path.empty()) {
        outputFile << "none" << std::endl;
    } else {
        for (int i : path) {
            outputFile << i << " ";
        }
        outputFile << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;
    }
}

