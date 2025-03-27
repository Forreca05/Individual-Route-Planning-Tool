#ifndef INDEPENDENT_H
#define INDEPENDENT_H

#include "Graph.h"
#include <string>

void independent(Graph<int>& graph);
void independentBatch(Graph<int>& graph, const std::string& inputFile, const std::string& outputFile);

#endif // INDEPENDENT_H
