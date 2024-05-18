#ifndef TSP_DA_2024_PRIM_H
#define TSP_DA_2024_PRIM_H

#include "Graph.h"
#include <limits>

#define INF std::numeric_limits<int>::max()

class Prim {
public:
    /**
     * @brief Minimum Spanning Tree algorithm to determine the path from the root node. The Prim's algorithm was
     * chosen because the it's better for dense graphs.
     * @param graph Graph to be analyzed.
     * @return The path from the root node.
    */
    static Graph* prim(Graph graph,int firstIndex = 2);
};


#endif //TSP_DA_2024_PRIM_H
