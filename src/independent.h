/**
 * @file independent.h
 * @brief Header file for the Independent algorithm that computes the best and alternative routes.
 *
 * This header defines the functions related to the "independent" algorithm, which computes
 * the best and alternative routes between two nodes in a graph, ensuring that the two
 * routes do not share any intermediate nodes or segments, except for the source and destination.
 * It also handles both interactive (terminal) and batch processing modes.
 *
 * @author João Pascoal Faria
 * @date March 2025
 */

#ifndef INDEPENDENT_H
#define INDEPENDENT_H

#include "Graph.h"
#include <string>
#include <unordered_set>
#include <iostream>

/**
 * @brief Runs the shortest path algorithm to compute the best and alternative routes.
 *
 * This function executes Dijkstra's algorithm to find the best or alternative route
 * between the given source and destination. If it's the first run, intermediate nodes
 * are added to the set of avoided nodes for the alternative route.
 *
 * @param graph The graph where the algorithm will search for routes.
 * @param source The starting node for the route.
 * @param destination The target node for the route.
 * @param avoidNodes A set of nodes to avoid during the second run (used in the alternative route).
 * @param avoidEdges A set of edges to avoid (not used in the current implementation).
 * @param mode The mode of transportation (e.g., "driving", "walking").
 * @param parked Indicates if there is parking available at the source or destination.
 * @param out The output stream where results are printed.
 * @param isFirstRun Flag indicating if it is the first execution (for determining best or alternative route).
 *
 * @note Complexity is O((V + E) log V), where V is the number of vertices and E is the number of edges.
 * Dijkstra's algorithm runs twice.
 */
void runAlgorithm(Graph<int> &graph, int source, int destination, std::unordered_set<int> &avoidNodes,
                  std::unordered_set<int> &avoidEdges, const std::string &mode, bool parked,
                  std::ostream &out, bool isFirstRun);

/**
 * @brief Computes the best and alternative routes interactively.
 *
 * This function prompts the user for input to specify the source, destination, and mode of transportation.
 * It computes the best route and an alternative route by avoiding the intermediate nodes during the second run.
 *
 * @param graph The graph where the routes will be computed.
 *
 * @note Complexity is O((V + E) log V), where V is the number of vertices and E is the number of edges.
 */
void independent(Graph<int>& graph);

/**
 * @brief Computes the best and alternative routes in batch mode from a file.
 *
 * This function reads route requests from an input file and writes the results to an output file.
 *
 * @param graph The graph where the routes will be computed.
 * @param inputFile The input file containing route queries.
 * @param outputFile The output file to store the results.
 *
 * @note Complexity is O((V + E) log V), where V is the number of vertices and E is the number of edges.
 */
void independentBatch(Graph<int>& graph, const std::string& inputFile, const std::string& outputFile);

#endif // INDEPENDENT_H
