#ifndef TSP_DA_2024_HEURISTIC_H
#define TSP_DA_2024_HEURISTIC_H

#include <vector>
#include "Graph.h"
#include <limits>
#include <set>
#include "Prim.h"

#define INF std::numeric_limits<int>::max()


class Heuristic {
public:
    static std::unordered_map<int, std::unordered_map<int, double>> djikstra(Graph *graph, std::set<int> oddDegreeNodes);
    static Graph* minimumWeightPerfectMatching(Graph *graph, std::set<int> oddDegreeNodes);
    static std::vector<int> findEulerianCircuit(Graph *graph);
    static std::pair<double, std::vector<int>> heuristic(Graph *graph);
};


#endif //TSP_DA_2024_HEURISTIC_H
