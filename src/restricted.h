#ifndef RESTRICTED_H
#define RESTRICTED_H

#include "Graph.h"

void runRestrictedAlgorithm(Graph<int> &graph, int source, int destination, int includeNode,
                            std::unordered_set<int> &avoidNodes, std::unordered_set<int> &avoidEdges,
                            const std::string &mode, bool parked, std::ostream &out);
void restricted(Graph<int>& graph);
void restrictedBatch(Graph<int>& graph, const std::string& inputFile, const std::string& outputFile);

#endif // RESTRICTED_H
