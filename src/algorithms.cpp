//
// Created by cryptic on 3/20/25.
//

#include "algorithms.h"

bool relaxDriving(Edge<int>* edge) {
    if (edge->getDriving() == -1) return false;
    Vertex<int> *u = edge->getOrig();
    Vertex<int> *v = edge->getDest();
    if (u->getDist() + edge->getDriving() < v->getDist()) {
        v->setDist(u->getDist() + edge->getDriving());
        v->setPath(edge);
        return true;
    }
    return false;
}

void dijkstraDriving(Graph<int>* g, const int& origin, const int& destination, const std::unordered_set<int>& avoidNodes) {
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
            if (avoidNodes.count(e->getDest()->getInfo())) continue;
            if (relaxDriving(e)) {
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