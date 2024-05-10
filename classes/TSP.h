#ifndef TSP_DA_2024_TSP_H
#define TSP_DA_2024_TSP_H

#include <vector>
#include <limits>

unsigned int tspBT(std::vector<std::vector<double>> dists,unsigned int n, std::vector<double> &path);
void tspRec(std::vector<std::vector<double>> dists, int n, int curI,int curDist, std::vector<double> curPath, int &minDist, std::vector<double> &path);

#endif //TSP_DA_2024_TSP_H
