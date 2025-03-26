#include <iostream>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <string>
#include "algorithms.h"
#include "Graph.h"

void restricted(Graph<int> &graph) {
    int node, includeNode, avoidinit, avoidend, total;
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
    	total = graph.findVertex(includeNode)->getDist();
        dijkstra(&graph, includeNode, destination, avoidNodes, avoidEdges, mode);
        std::vector<int> path2 = getPath(&graph, includeNode, destination);
        total += graph.findVertex(destination)->getDist();
        path.insert(path.end(), path2.begin() + 1, path2.end());
        if (path.empty()) {
        	std::cout << "RestrictedDrivingRoute: none" << std::endl;
        } else {
        	std::cout << "RestrictedDrivingRoute: ";
        	for (int i : path) {
        		std::cout << i << " ";
        	}
        	std::cout << " (" << total << ")" << std::endl;
        }
    	return;
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
	int source, destination, includeNode = -1, avoidInit, avoidEnd, total;

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
			} else if (key == "AvoidNodes:") {
                if (value != "-1") {
                	std::stringstream ss(value);
                	std::string token;
                	while (std::getline(ss, token, ',')) {
                		avoidNodes.insert(std::stoi(token));
                	}
				}
			} else if (key == "AvoidSegments:") {
				if (value != "-1") {
					// O valor contém uma string com as arestas a evitar (ex: (1,2) (3,4))
					// Usamos um loop para dividir a string em cada par de nós
					std::stringstream ss(value);
					std::string edge;

					while (ss >> edge) {
						// Remover os parênteses ao redor da aresta
						size_t openParen = edge.find('(');
						size_t closeParen = edge.find(')');

						if (openParen != std::string::npos && closeParen != std::string::npos) {
							edge = edge.substr(openParen + 1, closeParen - openParen - 1);
							std::stringstream edgeStream(edge);
							int start, end;
							char comma;

							// Tenta converter os números da aresta no formato (x,y)
							if (edgeStream >> start >> comma >> end && comma == ',') {
								// Se conseguiu, então seleciona a aresta para ser evitada
								selectEdge(&graph, start, end);  // Chama a função selectEdge
							} else {
								std::cerr << "Erro: Formato inválido na aresta " << edge << std::endl;
							}
						} else {
							std::cerr << "Erro: Aresta mal formatada. Use (x,y)" << std::endl;
						}
					}
				}
			} else if (key == "IncludeNode:") {
                if (value != "-1") {
					includeNode = std::stoi(value);
                }
			}
		}
    }

	file.close();  // Fecha o ficheiro após a leitura

	// Escreve os valores lidos no arquivo de saída
	outputFile << "Mode: " << mode << std::endl;
	outputFile << "Source: " << source << std::endl;
	outputFile << "Destination: " << destination << std::endl;

	if (includeNode != -1) {
		// Primeira execução do Dijkstra (da origem até o nó de inclusão)
		dijkstra(&graph, source, includeNode, avoidNodes, avoidEdges, mode);
		std::vector<int> path = getPath(&graph, source, includeNode);
		total = graph.findVertex(includeNode)->getDist();  // Distância até o nó de inclusão

		// Segunda execução do Dijkstra (do nó de inclusão até o destino)
		dijkstra(&graph, includeNode, destination, avoidNodes, avoidEdges, mode);
		std::vector<int> path2 = getPath(&graph, includeNode, destination);
		total += graph.findVertex(destination)->getDist();  // Distância do nó de inclusão até o destino

		// Concatenar os caminhos (ignorando o nó de inclusão duplicado)
		path.insert(path.end(), path2.begin() + 1, path2.end());  // Ignorar o nó de inclusão no segundo caminho

		// Escrever o resultado no arquivo
		if (path.empty()) {
			outputFile << "RestrictedDrivingRoute: none" << std::endl;
		} else {
			outputFile << "RestrictedDrivingRoute: ";
			for (int i : path) {
				outputFile << i << " ";
			}
			outputFile << " (" << total << ")" << std::endl;  // Distância total corretamente calculada
		}

		return;
	}


	dijkstra(&graph, source, destination, avoidNodes, avoidEdges, mode);
	std::vector<int> path = getPath(&graph, source, destination);

	if (path.empty()) {
		outputFile << "RestrictedDrivingRoute: none" << std::endl;
	} else {
		outputFile << "RestrictedDrivingRoute: ";
		for (int i : path) {
			outputFile << i << " ";
		}
		outputFile << " (" << graph.findVertex(destination)->getDist() << ")" << std::endl;
	}
}
