#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include "Graph.h"
#include <unordered_set>

bool relaxDriving(Edge<int>* edge, const std::string& mode, bool& parked); ;

void dijkstra(Graph<int>* g, const int& origin, const int& destination, const std::unordered_set<int>& avoidNodes, const std::string& mode, bool& parked);

std::vector<int> getPath(Graph<int>* g, const int& origin, const int& dest);

void selectEdge(Graph<int>* g, const int& origin, const int& destination);

#endif //ALGORITHMS_H
