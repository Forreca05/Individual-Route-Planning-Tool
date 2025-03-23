#include <iostream>
#include "algorithms.h"

bool relaxDriving(Edge<int>* edge, const std::string& mode) {
    if (edge->getDriving() == -1) return false;
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
    return false;
}

void dijkstra(Graph<int>* g, const int& origin, const int& destination, const std::unordered_set<int>& avoidNodes, const std::unordered_set<int>& avoidEdges, const std::string& mode) {
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
            if (relaxDriving(e, mode)) {
                pq.decreaseKey(e->getDest());
            }
        }
    }
}

std::vector<int> getPath(Graph<int>* g, const int& origin, const int& dest) {
    std::vector<int> res;
    Vertex<int> *v = g->findVertex(dest);
    while (v->getInfo() != origin) {
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