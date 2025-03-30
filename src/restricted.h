/**
 * @file restricted.h
 * @brief Header file for the Restricted route algorithm.
 *
 * This header defines the functions related to the "restricted" algorithm, which computes
 * the best route considering specific restrictions. These restrictions may include:
 * - Avoiding specific nodes.
 * - Avoiding specific segments of the graph (edges).
 * - Simultaneously avoiding nodes and edges.
 * - Including specific nodes that the route must visit.
 *
 * @author João Pascoal Faria
 * @date March 2025
 */

#ifndef RESTRICTED_H
#define RESTRICTED_H

#include "Graph.h"
#include <string>
#include <unordered_set>
#include <iostream>

/**
 * @brief Runs the restricted pathfinding algorithm, considering avoidance and inclusion constraints.
 *
 * This function computes the shortest path between two nodes in the graph, taking into account
 * the avoidance of specific nodes and segments, and including a specific node if required. If
 * an inclusion node is specified, the algorithm first finds the shortest path to this node and then
 * proceeds from that node to the destination.
 *
 * @param graph The graph where the algorithm will search for the best route.
 * @param source The starting node of the route.
 * @param destination The target node of the route.
 * @param includeNode A node that must be included in the path (-1 if not applicable).
 * @param avoidNodes A set of nodes to avoid during pathfinding.
 * @param avoidEdges A set of edges to avoid during pathfinding.
 * @param mode The mode of transportation (e.g., "driving", "walking").
 * @param parked A boolean indicating if parking is available at source or destination.
 * @param out The output stream to write the result (either std::cout or a file).
 *
 * @note Complexity is O((V + E) log V), where V is the number of vertices and E is the number of edges.
 */
void runRestrictedAlgorithm(Graph<int> &graph, int source, int destination, int includeNode,
                            std::unordered_set<int> &avoidNodes, std::unordered_set<int> &avoidEdges,
                            const std::string &mode, bool parked, std::ostream &out);

/**
 * @brief Handles user input for restricted routes in interactive mode.
 *
 * This function reads user input for the source, destination, mode of transportation,
 * nodes to avoid, edges to avoid, and an optional node to include in the route. It then
 * calls the restricted pathfinding algorithm to compute the best route based on the user's input.
 *
 * @param graph The graph representing the road network where the algorithm will search for the route.
 *
 * @note Complexity is O((V + E) log V), as it calls the restricted pathfinding algorithm.
 */
void restricted(Graph<int>& graph);

/**
 * @brief Processes a batch file for the restricted pathfinding algorithm.
 *
 * This function reads input parameters from a file and executes the restricted pathfinding
 * algorithm for each query in the file. It then writes the results to an output file.
 *
 * @param graph The graph representing the road network where the algorithm will search for the route.
 * @param filename The name of the input file containing route queries.
 * @param outputFilename The name of the output file to store the results.
 *
 * @note Complexity is O((V + E) log V) per query, as it calls the restricted pathfinding algorithm.
 */
void restrictedBatch(Graph<int>& graph, const std::string& inputFile, const std::string& outputFile);

#endif // RESTRICTED_H
