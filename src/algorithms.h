//
// Created by cryptic on 3/20/25.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.h"
#include <unordered_set>

bool relaxDriving(Edge<int>* edge);

void dijkstraDriving(Graph<int>* g, const int& origin, const int& destination, const std::unordered_set<int>& avoidNodes);

std::vector<int> getPath(Graph<int>* g, const int& origin, const int& dest);

#endif //ALGORITHMS_H
