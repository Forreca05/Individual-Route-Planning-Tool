/**
 * @file
 * @brief Header file for search algorithms used in graph-based navigation.
 *
 * This header file contains function declarations for various search algorithms
 * that are used to find the shortest path in a graph, including Dijkstra's algorithm,
 * edge relaxation, and path retrieval. It also includes functions for selecting specific edges
 * in a graph.
 *
 * @note This file interacts with the Graph class to perform graph-based searches.
 */

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include "Graph.h"
#include <unordered_set>

/**
 * @brief Relaxes an edge based on the given mode of transportation.
 *
 * This function attempts to relax an edge between two vertices in the graph
 * depending on the specified mode of transportation (e.g., "driving" or "walking").
 * It updates the distance and path of a vertex if a shorter path is found via the edge.
 *
 * @param edge The edge to relax.
 * @param mode The mode of transportation (e.g., "driving", "walking").
 * @param parked Indicates if parking is available.
 * @return True if the relaxation was successful, false otherwise.
 *
 * @complexity O(1)
 */
bool relax(Edge<int>* edge, const std::string& mode, bool& parked);

/**
 * @brief Implements Dijkstra's algorithm to find the shortest path in a graph.
 *
 * Dijkstra's algorithm is used to find the shortest path from the origin vertex
 * to the destination vertex in the graph. The algorithm considers specified nodes to avoid
 * and can adapt to different modes of transportation.
 *
 * @param g Pointer to the graph object.
 * @param origin The starting node.
 * @param destination The target node.
 * @param avoidNodes Set of nodes to be avoided in the path.
 * @param mode The mode of transportation to be used in the search (e.g., "driving", "walking").
 * @param parked Indicates if parking is available during the search.
 *
 * @complexity O((V + E) log V)
 */
void dijkstra(Graph<int>* g, const int& origin, const int& destination, const std::unordered_set<int>& avoidNodes, const std::string& mode, bool& parked);

/**
 * @brief Retrieves the path from origin to destination.
 *
 * Constructs and returns the shortest path from the origin node to the destination node,
 * based on the result of Dijkstra's algorithm.
 *
 * @param g Pointer to the graph object.
 * @param origin The starting node.
 * @param dest The destination node.
 * @return A vector containing the path from origin to destination, or an empty vector if no path exists.
 *
 * @complexity O(V)
 */
std::vector<int> getPath(Graph<int>* g, const int& origin, const int& dest);

/**
 * @brief Selects an edge between two vertices.
 *
 * This function marks an edge between two vertices as "selected". The edge selection
 * process is performed by iterating over the adjacency list of the source vertex and
 * setting the corresponding edge to be selected.
 *
 * @param g Pointer to the graph object.
 * @param origin The starting node.
 * @param destination The target node.
 */
void selectEdge(Graph<int>* g, const int& origin, const int& destination);

#endif //ALGORITHMS_H
