#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <string>
#include "algorithms.h"
#include "Graph.h"
#include "environmentally.h"

void environmentally(Graph<int> &graph) {
    std::string sourceStr, destinationStr, mode, segment;
    int node, maxWalk, avoidInit, avoidEnd, middle, total = 100000;
    bool parked = false, route = false;
    std::unordered_set<int> avoidNodes;
    std::unordered_set<int> avoidEdges;
    std::unordered_map<int, double> time_to_id;

    // Entrada de dados
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

    // Coleta de nós a evitar
    std::cout << "AvoidNodes (enter -1 to stop): ";
    while (std::cin >> node && node != -1) {
        avoidNodes.insert(node);
    }

    // Coleta de segmentos a evitar
    std::cout << "AvoidSegments (enter -1 to stop): ";
    while (std::cin >> segment && segment != "-1") {
        segment = segment.substr(segment.find('(') + 1, segment.find(')') - segment.find('(') - 1);
        std::stringstream ss(segment);
        char comma;
        ss >> avoidInit >> comma >> avoidEnd;
        selectEdge(&graph, avoidInit, avoidEnd);
    }

    for (Vertex<int>* v : graph.getVertexSet()) {
        if (v->hasParking()) {  // Certifique-se de que `hasParking()` existe
            dijkstra(&graph, source, v->getInfo(), avoidNodes, avoidEdges, mode, parked);
            time_to_id[v->getInfo()] = graph.findVertex(v->getInfo())->getDist();  // Armazena a distância do nó de origem até o estacionamento
        }
    }

    parked = true;

	for (const auto& pair : time_to_id) {
		dijkstra(&graph, pair.first, destination, avoidNodes, avoidEdges, mode, parked);
		if (graph.findVertex(destination)->getDist() <= maxWalk) {
            route = true;
			int distt = pair.second + graph.findVertex(destination)->getDist();
			if (distt < total) {
				total = distt;
				middle = pair.first;
			}
		}
	}
	if (route == false) {
		std::cout << "DrivingRoute:" << std::endl;
		std::cout << "ParkingNode:" << std::endl;
		std::cout << "WalkingRoute:" << std::endl;
		std::cout << "TotalTime:" << std::endl;
		std::cout << "Message: No possible route with max. walking time of " << maxWalk << " minutes." << std::endl;
		return;
	}

	parked = false;
	dijkstra(&graph, source, middle, avoidNodes, avoidEdges, mode, parked);
	std::vector<int> path = getPath(&graph, source, middle);
	int meioDist = graph.findVertex(middle)->getDist();
	std::cout << "DrivingRoute:";
	std::cout << path[0];
	for (int i = 1; i < path.size(); i++) {
		std::cout << ',' << path[i];
	}
	std::cout << " (" << meioDist << ")" << std::endl;

	std::cout << "ParkingNode:" << middle << std::endl;
	parked = true;

	dijkstra(&graph, middle, destination, avoidNodes, avoidEdges, mode, parked);
	std::vector<int> path2 = getPath(&graph, middle, destination);
	std::cout << "WalkingRoute:";
	std::cout << path2[0];
	for (int i = 1; i < path.size(); i++) {
		std::cout << ',' << path2[i];
	}
	int fimDist = graph.findVertex(destination)->getDist();
	std::cout << " (" << fimDist << ")" << std::endl;
	std::cout << "TotalTime:" << total << std::endl;
	path.insert(path.end(), path2.begin() + 1, path2.end());
}

void environmentallyBatch(Graph<int> &graph, const std::string &filename, const std::string &outputFilename) {
    std::unordered_set<int> avoidNodes; // Definição do conjunto de nós a evitar
	std::unordered_set<int> avoidEdges; // Apenas declarado caso precise no futuro
    std::unordered_map<int, double> time_to_id;
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
	int source, destination, includeNode = -1, avoidInit, avoidEnd, maxWalk, total = 1000, middle;
    bool parked = false, route=false;

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
            } else if (key == "MaxWalkTime:") {
                maxWalk = std::stoi(value);
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

    for (Vertex<int>* v : graph.getVertexSet()) {
        if (v->hasParking()) {  // Certifique-se de que `hasParking()` existe
        	std::cout << v->getInfo() << std::endl;
            dijkstra(&graph, source, v->getInfo(), avoidNodes, avoidEdges, mode, parked);
            time_to_id[v->getInfo()] = graph.findVertex(v->getInfo())->getDist();  // Armazena a distância do nó de origem até o estacionamento
        }
    }

    parked = true;

    for (const auto& pair : time_to_id) {
        dijkstra(&graph, pair.first, destination, avoidNodes, avoidEdges, mode, parked);
        if (graph.findVertex(destination)->getDist() <= maxWalk) {
          route = true;
          int distt = pair.second + graph.findVertex(destination)->getDist();
          if (distt < total) {
            total = distt;
            middle = pair.first;
          }
        }
    }
	if (route == false) {
		outputFile << "DrivingRoute:" << std::endl;
		outputFile << "ParkingNode:" << std::endl;
		outputFile << "WalkingRoute:" << std::endl;
		outputFile << "TotalTime:" << std::endl;
		outputFile << "Message: No possible route with max. walking time of " << maxWalk << " minutes." << std::endl;
		return;
	}

    outputFile << "Source: " << source << std::endl;
    outputFile << "Destination: " << destination << std::endl;

	parked = false;
	dijkstra(&graph, source, middle, avoidNodes, avoidEdges, mode, parked);
	std::vector<int> path = getPath(&graph, source, middle);
	int meioDist = graph.findVertex(middle)->getDist();
	outputFile << "DrivingRoute:";
	outputFile << path[0];
	for (int i = 1; i < path.size(); i++) {
		outputFile << ',' << path[i];
	}
	outputFile << " (" << meioDist << ")" << std::endl;

	outputFile << "ParkingNode:" << middle << std::endl;
	parked = true;

	dijkstra(&graph, middle, destination, avoidNodes, avoidEdges, mode, parked);
	std::vector<int> path2 = getPath(&graph, middle, destination);
	outputFile << "WalkingRoute:";
	outputFile << path2[0];
	for (int i = 1; i < path2.size(); i++) {
		outputFile << ',' << path2[i];
	}
	int fimDist = graph.findVertex(destination)->getDist();
	outputFile << " (" << fimDist << ")" << std::endl;
	outputFile << "TotalTime:" << total << std::endl;
	path.insert(path.end(), path2.begin() + 1, path2.end());
}