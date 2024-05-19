#ifndef TSP_DA_2024_TSP_H
#define TSP_DA_2024_TSP_H

#include <vector>
#include <limits>

class TSP {
    /**
     * @brief Recursive function that determines the most effective path to get the minimum cost of a Hamiltonian cycle
     * \n Time Complexity: O(2^(V*E))
     * @param dists Matrix containing the distances between nodes
     * @param n Number of nodes in the graph
     * @param curI Current Iteration
     * @param curDist Distance of the current Iteration
     * @param curPath Current path
     * @param minDist Current minimum distance
     * @param path Current path to the end
     */
    static void
    tspRec(std::vector<std::vector<double>> dists, unsigned int n, int curI, double curDist, std::vector<int> curPath,
           double &minDist, std::vector<int> &path);
public:
    /**
     * @brief Travelling Sales-Person Problem solution using backtracking
     * \n Time Complexity: O(2^(V+E))
     * @param dists Matrix containing the distances between nodes
     * @param n Number of nodes in the graph
     * @param path Final path
     * @return
     */
    static double tspBT(std::vector<std::vector<double>> dists,unsigned int n, std::vector<int> &path);
};


#endif //TSP_DA_2024_TSP_H
