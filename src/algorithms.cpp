/**
 * @file
 * @brief Implementation of search algorithms for graph-based navigation.
 * 
 * This file contains the main functions used to perform searches in a graph.
 * It includes implementations for Dijkstra's algorithm, path retrieval,
 * edge selection, and relaxation functions for different transportation modes.
 * 
 */

#include <iostream>
#include "algorithms.h"

/**
 * @brief Relaxes an edge based on the given mode of transportation.
 * 
 * Updates the distance and path of a vertex if a shorter path is found via the given edge.
 * 
 * @param edge The edge to relax.
 * @param mode The mode of transportation.
 * @param parked Indicates of there is parking avaliable.
 * @return True if the relaxation was successful, false otherwise.
 * 
 * Complexity O(1)
 */

bool relax(Edge<int>* edge, const std::string& mode, bool& parked) {
    if ((mode == "driving" || !parked) && edge->getDriving() == -1) return false;
    Vertex<int> *u = edge->getOrig();
    Vertex<int> *v = edge->getDest();

    if (mode == "driving") {
        if (u->getDist() + edge->getDriving() < v->getDist()) {
            v->setDist(u->getDist() + edge->getDriving());
            v->setPath(edge);
            return true;
        }
    }
    else if (mode == "walking") {
        if (u->getDist() + edge->getWalking() < v->getDist()) {
            v->setDist(u->getDist() + edge->getWalking());
            v->setPath(edge);
            return true;
        }
    }
    else {
        if (parked) {
            if (u->getDist() + edge->getWalking() < v->getDist()) {
                v->setDist(u->getDist() + edge->getWalking());
                v->setPath(edge);
                return true;
            }
        }
        else {
            if (u->getDist() + edge->getDriving() < v->getDist()) {
                v->setDist(u->getDist() + edge->getDriving());
                v->setPath(edge);
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Implements Dijkstra's algorithm to find the shortest path in a graph.
 * 
 * Computes the shortest path from an origin node to a destination node, avoiding specified nodes.
 * 
 * @param g Pointer to the graph.
 * @param origin The starting node.
 * @param destination The target node.
 * @param avoidNodes Set of nodes to be avoided.
 * @param mode The mode of transportation.
 * @param parked Indicates of there is parking avaliable.
 * 
 * @complexity O((V + E) log V)
 */

void dijkstra(Graph<int>* g, const int& origin, const int& destination, const std::unordered_set<int>& avoidNodes, const std::string& mode, bool& parked) {
    MutablePriorityQueue<Vertex<int>> pq;
    for (Vertex<int> *v : g->getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }

    Vertex<int> *source = g->findVertex(origin);
    source->setDist(0);

    for (Vertex<int> *v : g->getVertexSet()) {
        if (avoidNodes.count(v->getInfo())) continue;
        pq.insert(v);
    }

    while (!pq.empty()) {
        Vertex<int> *u = pq.extractMin();
        if (u->getInfo() == destination) return;

        for (Edge<int> *e : u->getAdj()) {
            if (e->isSelected()) continue;
            if (avoidNodes.count(e->getDest()->getInfo())) continue;
            if (relax(e, mode, parked)) {
                pq.decreaseKey(e->getDest());
            }
        }
    }
}

/**
 * @brief Retrieves the path from origin to destination.
 * 
 * Constructs the shortest path found by Dijkstra's algorithm.
 * 
 * @param g Pointer to the graph.
 * @param origin The starting node.
 * @param dest The destination node.
 * 
 * @return A vector containing the path from origin to destination.
 * 
 * @complexity O(V)
 */

std::vector<int> getPath(Graph<int>* g, const int& origin, const int& dest) {
    std::vector<int> res;
    Vertex<int> *v = g->findVertex(dest);

    // Verifica se o destino é acessível
    if (!v || v->getDist() == INF) {
        return res;  // Retorna um vetor vazio se não houver caminho
    }

    while (v->getInfo() != origin) {
        if (!v->getPath()) return {};  // Se não há caminho, retorna vazio
        res.push_back(v->getInfo());
        v = v->getPath()->getOrig();
    }

    res.push_back(origin);
    std::reverse(res.begin(), res.end());
    return res;
}


void selectEdge(Graph<int>* g, const int& origin, const int& dest) {
    Vertex<int> *source = g->findVertex(origin);
    Vertex<int> *destination = g->findVertex(dest);

    if (source != nullptr && destination != nullptr) {
        for (Edge<int>* edge : source->getAdj()) {
            if (edge->getDest() == destination) {
                edge->setSelected(true);
                return;
            }
        }
    }
}
