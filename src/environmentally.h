/**
 * @file environmentally.h
 * @brief Header file for environmentally friendly route algorithm.
 *
 * This file contains function declarations for calculating and processing environmentally friendly routes
 * that combine both driving and walking. The routes aim to minimize driving while ensuring that walking distances
 * from parking nodes to the destination are within the user's maximum walking time.
 */

#ifndef ENVIRONMENTALLY_H
#define ENVIRONMENTALLY_H

#include "Graph.h"
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Runs the environmentally friendly route algorithm.
 *
 * This function calculates a route that minimizes the driving distance, ensuring that the walking distance
 * from a parking node to the destination does not exceed a given maximum walking time.
 * It computes the best route with both driving and walking and prints the result to the specified output stream.
 *
 * @param graph The graph representing the transportation network.
 * @param source The starting node of the route.
 * @param destination The target destination node.
 * @param maxWalk The maximum walking distance the user is willing to walk after parking.
 * @param avoidNodes A set of nodes to be avoided during the search.
 * @param time_to_id A map that contains parking nodes and their respective driving times.
 * @param mode The mode of transportation, should be "driving-walking".
 * @param parked A boolean indicating if parking is available.
 * @param out The output stream where the results will be written.
 *
 * @complexity O((V + E) log V), due to the repeated execution of Dijkstra's algorithm.
 */
void runEnvironmentallyAlgorithm(Graph<int>& graph, int source, int destination, int maxWalk,
                                  std::unordered_set<int>& avoidNodes, std::unordered_map<int,
                                  double>& time_to_id, const std::string &mode, bool parked, std::ostream &out);

/**
 * @brief Interactively computes environmentally friendly routes for a user.
 *
 * This function prompts the user for input regarding source, destination, maximum walking time,
 * avoid nodes, and avoid segments. It then calls the `runEnvironmentallyAlgorithm` to compute the best
 * driving-walking route and outputs the results to the console.
 *
 * @param graph The graph representing the transportation network.
 *
 * @complexity O(V log V + E), due to the execution of Dijkstra's algorithm.
 */
void environmentally(Graph<int>& graph);

/**
 * @brief Processes a batch of route requests and computes environmentally friendly routes.
 *
 * This function reads the batch route requests from an input file, processes them, and writes the results
 * to an output file. Each route request includes details such as the source, destination, maximum walk time,
 * and any nodes or segments to avoid.
 *
 * @param graph The graph representing the transportation network.
 * @param inputFile The input file containing route requests.
 * @param outputFile The output file to write the results.
 *
 * @complexity O((V + E) log V), due to the repeated execution of Dijkstra's algorithm.
 */
void environmentallyBatch(Graph<int>& graph, const std::string& inputFile, const std::string& outputFile);

#endif // ENVIRONMENTALLY_H
