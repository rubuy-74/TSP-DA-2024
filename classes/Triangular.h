#ifndef TSP_DA_2024_TRIANGULAR_H
#define TSP_DA_2024_TRIANGULAR_H

#include <vector>
#include "Graph.h"
#include "MutablePriorityQueue.h"
#include <limits>
#include <set>


class Triangular {
    /**
     * @brief Create a circuit from the MST tree and the distances on the original graph.
     * @param node first node to be analyzed (root)
     * @param graph MST tree of the original graph
     * @param oldGraph Graph before the MST (original graph)
     * @param result Path of the circuit
     * @param sumDist Final sum of Distances
     */
    static void preOrderGraph(Node* node, Graph graph, Graph oldGraph, std::vector<int> &result, int &sumDist);
public:
    /**
     * @brief Algorithm that determines an approximation to the optimal solution on the TSP algorithm
     * Based on the triangular inequality (the smallest distance between two nodes is a line), it is possible to determine a good approximation to the optimal solution for the TSP problem.
     * @param graph Graph to be analyzed
     * @param result Path of the circuit
     * @return Final sum of Distances (cost of the path)
     */
    static double tspTriangular(Graph graph,std::vector<int> &result);
};


#endif //TSP_DA_2024_TRIANGULAR_H
