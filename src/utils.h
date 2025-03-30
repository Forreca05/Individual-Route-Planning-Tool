/**
* @file utils.h
 * @brief Header file for utility functions related to graph construction from CSV files.
 *
 * This file provides the declaration of functions to load a graph by parsing location
 * and distance data from CSV files.
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "Graph.h"

/**
 * @brief Loads a graph from CSV files containing location and distance data.
 *
 * This function reads two CSV files: one for the location data (including parking info and location codes)
 * and another for the distance data (including walking and driving times), and uses this information
 * to build a graph.
 *
 * @param locationsFile Path to the Locations.csv file.
 * @param distancesFile Path to the Distances.csv file.
 * @return A Graph<int> object that represents the graph built from the data in the files.
 */
Graph<int> loadGraphFromCSV(const std::string &locationsFile, const std::string &distancesFile);

#endif // UTILS_H
