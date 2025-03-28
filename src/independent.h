#ifndef INDEPENDENT_H
#define INDEPENDENT_H

#include "Graph.h"
#include <string>

void runAlgorithm(Graph<int> &graph, int source, int destination, std::unordered_set<int> &avoidNodes,
                  std::unordered_set<int> &avoidEdges, const std::string &mode, bool parked,
                  std::ostream &out, bool isFirstRun);
void independent(Graph<int>& graph);
void independentBatch(Graph<int>& graph, const std::string& inputFile, const std::string& outputFile);

#endif // INDEPENDENT_H
