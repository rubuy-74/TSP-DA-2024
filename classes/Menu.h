#ifndef TSP_DA_2024_MENU_H
#define TSP_DA_2024_MENU_H

#include <iostream>
#include <chrono>
#include "Dataset.h"

class Menu {
public:
    Menu();

    Dataset dataset;
    std::string file;
    std::string path;
   
    void MainMenu();
    void DatasetMenu();

    void backToMainMenu();
};

void TSPBacktracking(Dataset dataset, std::string filePath, std::string file);
void TSPTriangular(Dataset dataset, std::string filePath, std::string file);
void TSPHeuristic(Dataset dataset, std::string path, std::string file);
void printPath(std::vector<int> path, double sumDist);


#endif 