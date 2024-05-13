#ifndef TSP_DA_2024_TSP_H
#define TSP_DA_2024_TSP_H

#include <vector>
#include <limits>

class TSP {
    /**
     * @brief Recursive function that determines the most effective path to get the minimum cost of a Hamiltonian
     * @param dists Matrix containing the distances between nodes
     * @param n Number of nodes in the graph
     * @param curI Current Iteration
     * @param curDist Distance of the current Iteration
     * @param curPath Current path
     * @param minDist Current minimum distance
     * @param path Current path to the end
     */
    static void
    tspRec(std::vector<std::vector<double>> dists, unsigned int n, int curI, int curDist, std::vector<double> curPath,
           int &minDist, std::vector<double> &path);
public:
    /**
     * @brief Travelling Sales-Person Problem solution using backtracking
     * @param dists Matrix containing the distances between nodes
     * @param n Number of nodes in the graph
     * @param path Final path
     * @return
     */
    static unsigned int tspBT(std::vector<std::vector<double>> dists,unsigned int n, std::vector<double> &path);
};


#endif //TSP_DA_2024_TSP_H
