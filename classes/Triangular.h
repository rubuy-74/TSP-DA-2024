#ifndef TSP_DA_2024_TRIANGULAR_H
#define TSP_DA_2024_TRIANGULAR_H

#include <vector>
#include "Graph.h"
#include "MutablePriorityQueue.h"
#include <limits>
#include <set>


class Triangular {
    static void preOrderGraph(Node* node, Graph graph, Graph oldGraph, std::vector<int> &result, int &sumDist);
public:
    static double tspTriangular(Graph graph,std::vector<int> &result);
};


#endif //TSP_DA_2024_TRIANGULAR_H
