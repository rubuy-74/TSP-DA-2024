#include <iostream>
#include "Dataset.h"
#include "Parser.h"
#include "TSP.h"
#include "Triangular.h"
#include "Heuristic.h"

void testTSPBacktracking(Dataset dataset,std::string path, std::string file);
void testTSPTriangular(Dataset dataset,std::string path ,std::string file);
void testFunctions(Dataset dataset, std::string path ,std::string file);
void printPath(std::vector<int> path,double sumDist);

int main() {
    Dataset dataset = Dataset();
    std::string file = "tourism.csv";
    std::string path = "../toy-graphs/";
    testTSPBacktracking(dataset,path,file);
    testTSPTriangular(dataset,path,file);
    testFunctions(dataset,path, "tourism.csv");
    return 0;
}

void testFunctions(Dataset dataset,std::string path, std::string file) {
    Parser parser;

    auto e = parser.readFile(path + file,true);
    dataset.loadEdges(e);
    dataset.loadMatrix(e);
    Graph g = dataset.getGraph();
    std::pair<double, std::vector<int>> tsp = Heuristic::heuristic(&g);
    printPath(tsp.second,tsp.first);
}

void testTSPBacktracking(Dataset dataset,std::string filePath, std::string file) {
    Parser parser;

    auto e = parser.readFile(filePath + file,true);
    dataset.loadEdges(e);
    dataset.loadMatrix(e);

    double sum = 0;

    std::vector<int> path(dataset.getGraph().getNodeSize(),0);
    double sumDist = TSP::tspBT(dataset.getAdjMatrix(),dataset.getGraph().getNodeSize(),path);
    path.push_back(0);
    printPath(path,sumDist);
}

void testTSPTriangular(Dataset dataset,std::string filePath, std::string file) {
    Parser parser;
    std::vector<int> result;

    auto e = parser.readFile(filePath + file,true);
    dataset.loadEdges(e);
    dataset.loadMatrix(e);

    double sumDist = Triangular::tspTriangular(dataset.getGraph(),result);
    printPath(result,sumDist);
}

void printPath(std::vector<int> path,double sumDist) {
    std::cout << "distance: " << sumDist << '\n';
    std::cout << "path:" << '\n';
    for(int i = 0; i < path.size(); i++) {
        std::cout << path[i] << ", ";
    }
    std::cout << '\n';
}
