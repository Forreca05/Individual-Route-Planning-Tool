// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "Graph.h"

Graph<int> loadGraphFromCSV(const std::string &locationsFile, const std::string &distancesFile);

#endif // UTILS_H
