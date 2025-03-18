//
// Created by forreca05 on 04-03-2025.
//

#include <iostream>
#include "Graph.h"
#include "utils.h"
#include "MutablePriorityQueue.h"

template <class T>
bool relaxDriving(Edge<T>* edge) { // d[u] + w(u,v) < d[v]
    Vertex<T> *u = edge->getOrig();
    Vertex<T> *v = edge->getDest();
    if (u->getDist() + edge->getDriving() < v->getDist()) {
        v->setDist(u->getDist() + edge->getDriving());
        v->setPath(edge);
        return true;
    }
    return false;
}

template <class T>
void dijkstraDriving(Graph<T>* g, const T& origin) {
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
            if (relaxDriving(e)) {
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

int main() {

    // User interface
    std::string mode, source, destination;
    std::cout << "Mode: ";
    std::cin >> mode;
    std::cout << "Source: ";
    std::cin >> source;
    std::cout << "Destination: ";
    std::cin >> destination;

    // Carregar o grafo a partir dos CSVs
    Graph<std::string> graph = loadGraphFromCSV("../data/Locations.csv", "../data/Distances.csv");

    dijkstraDriving(&graph, source);

    for (Vertex<std::string>* v : graph.getVertexSet()) {
        std::cout << v->getInfo() << ": " << v->getDist() << std::endl;
    }

}