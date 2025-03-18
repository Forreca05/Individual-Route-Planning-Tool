#include "Graph.h"
#include "utils.h"
#include "MutablePriorityQueue.h"
#include <fstream>
#include <sstream>
#include <iostream>

Graph<std::string> loadGraphFromCSV(const std::string &locationsFile, const std::string &distancesFile) {
    Graph<std::string> graph;

    // Ler Locations.csv
    std::ifstream locations(locationsFile);  // Caminho para o arquivo de locais
    if (!locations.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << locationsFile << std::endl;
        return graph;
    }

    std::string line;
    std::getline(locations, line);  // Pular cabeçalho

    while (std::getline(locations, line)) {
        std::istringstream stream(line);
        std::string location, nodeIdStr, code, parkingStr;
        std::getline(stream, location, ',');
        std::getline(stream, nodeIdStr, ',');
        std::getline(stream, code, ',');
        std::getline(stream, parkingStr, ',');

        bool hasParking = (parkingStr == "1");

        graph.addVertex(nodeIdStr);  // Adiciona vértice
    }

    // Ler Distances.csv
    std::ifstream distances(distancesFile);  // Caminho para o arquivo de distâncias
    if (!distances.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << distancesFile << std::endl;
        return graph;
    }

    std::getline(distances, line);  // Pular cabeçalho

    while (std::getline(distances, line)) {
        std::istringstream stream(line);
        std::string loc1Str, loc2Str, drivingStr, walkingStr;
        std::getline(stream, loc1Str, ',');
        std::getline(stream, loc2Str, ',');
        std::getline(stream, drivingStr, ',');
        std::getline(stream, walkingStr, ',');

        int drivingTime = (drivingStr == "X") ? INF : std::stoi(drivingStr);
        int walkingTime = std::stoi(walkingStr);

        // Adiciona as arestas
        graph.addBidirectionalEdge(loc1Str, loc2Str, walkingTime, drivingTime);
        graph.addBidirectionalEdge(loc2Str, loc1Str, walkingTime, drivingTime);  // Se for bidirecional
    }

    return graph;
}

template <class T>
bool relax(Edge<T>* edge) { // d[u] + w(u,v) < d[v]
    Vertex<T> *u = edge->getOrig();
    Vertex<T> *v = edge->getDest();
    if (u->getDist() + edge->getWeight() < v->getDist()) {
        v->setDist(u->getDist() + edge->getWeight());
        v->setPath(edge);
        return true;
    }
    return false;
}

template <class T>
void dijkstra(Graph<T>* g, const T& origin) {
    MutablePriorityQueue<Vertex<T>> pq;
    for (Vertex<T> *v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }
    Vertex<T> *source = g->findVertex(origin);
    source->setDist(0);
    for (Vertex<T> *v : g->getVertexSet()) {
        pq.insert(v);
    }
    while (!pq.empty()) {
        Vertex<T> *u = pq.extractMin();
        for (Edge<T> *e : u->getAdj()) {
            if (relax(e)) {
                pq.decreaseKey(e->getDest());
            }
        }
    }
}

template <class T>
static std::vector<T> getPath(Graph<T>* g, const T& origin, const T& dest) {
    std::vector<T> res;
    Vertex<T> *v = g->findVertex(dest);
    while (v->getInfo() != origin) {
        res.push_back(v->getInfo());
        v = v->getPath()->getOrig();
    }
    res.push_back(origin);
    std::reverse(res.begin(), res.end());
    return res;
}