#ifndef TSP_DA_2024_TRIANGULAR_H
#define TSP_DA_2024_TRIANGULAR_H

#include <vector>
#include "Graph.h"
#include "MutablePriorityQueue.h"
#include <limits>
#include <set>

#define INF std::numeric_limits<int>::max()

class Triangular {
public:
    /**
     * @brief Minimum Spanning Tree algorithm to determine the path from the root node to itself. The Prim's algorithm was
     * chosen because the it's better for dense graphs.
     * @param graph Graph to be analyzed.
     * @return The path, from the root to itself. ??
     */
    static Graph* prim(Graph graph);
    static std::unordered_map<int, std::unordered_map<int, double>> djikstra(Graph *graph, std::set<int> oddDegreeNodes);
    static Graph* minimumWeightPerfectMatching(Graph *graph, std::set<int> oddDegreeNodes);
    static std::vector<int> findEulerianCircuit(Graph *graph);
    static std::pair<double, std::vector<int>> heuristic(Graph *graph);
};


#endif //TSP_DA_2024_TRIANGULAR_H
