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
     * \n Time Complexity: O(V²)
     * @param graph graph to be analyzed
     * @param oddDegreeNodes nodes with odd degree
     * @return a map with the current node and the next and the distance between them
     */
    static std::unordered_map<int, std::unordered_map<int, double>> heuristicDjikstra(Graph *graph, std::set<int> oddDegreeNodes);
    /**
     * Perfect matching algorithm to group for groups of two to minimize its distance.
     * \n Time Complexity: O(V²)
     * @param graph graph to be analyzed
     * @param oddDegreeNodes  nodes with odd degree
     * @return Modified graph
     */
    static Graph* minimumWeightPerfectMatching(Graph *graph, std::set<int> oddDegreeNodes);
    /**
     * Determines an Eulerian Circuit
     * \n Time Complexity: O(VE)
     * @param graph graph to be analyzed
     * @return Eulerian Circuit
     */
    static std::vector<int> findEulerianCircuit(Graph *graph);
    /**
     * This heuristic takes advantage of the dijkstra, prim and minimum weight perfect matching algorithm to find a solution, returning the cost and path.
     * \n Time Complexity: max(O(VE),O(V²))
     * @param graph graph to be analyzed
     * @return map of the final cost and path
     */
    static std::pair<double, std::vector<int>> heuristic(Graph *graph, int startingNode = 0);
};


#endif //TSP_DA_2024_HEURISTIC_H
