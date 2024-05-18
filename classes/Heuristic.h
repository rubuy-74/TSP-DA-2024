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
    /**
     * Dijkstra algorithm to determine the smallest distance between all the nodes
     * @param graph graph to be analyzed
     * @param oddDegreeNodes nodes with odd degree
     * @return a map with the current node and the next and the distance between them
     */
    static std::unordered_map<int, std::unordered_map<int, double>> djikstra(Graph *graph, std::set<int> oddDegreeNodes);
    /**
     * Perfect matching algorithm to group for groups of two to minimize its distance.
     * @param graph graph to be analyzed
     * @param oddDegreeNodes  nodes with odd degree
     * @return Modified graph
     */
    static Graph* minimumWeightPerfectMatching(Graph *graph, std::set<int> oddDegreeNodes);
    /**
     * Determines an Eulerian Circuit
     * @param graph graph to be analyzed
     * @return Eulerian Circuit
     */
    static std::vector<int> findEulerianCircuit(Graph *graph);
    /**
     * Returns the final cost and path
     * @param graph graph to be analyzed
     * @return map of the final cost and path
     */
    static std::pair<double, std::vector<int>> heuristic(Graph *graph);
};


#endif //TSP_DA_2024_HEURISTIC_H
