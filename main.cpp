#include <iostream>
#include "classes/Dataset.h"
#include "classes/Parser.h"
#include "classes/TSP.h"
#include "classes/Triangular.h"
#include "classes/Heuristic.h"
#include "classes/Menu.h"

int main() {
    Menu menu;
    menu.DatasetMenu();
    menu.MainMenu();
    
    return 0;
}


void testTSPBacktracking(Dataset dataset,std::string path, std::string file);
void testTSPTriangular(Dataset dataset,std::string path ,std::string file);
void testFunctions(Dataset dataset, std::string path ,std::string file);
void printPath(std::vector<int> path,double sumDist);
void testConnecter(Dataset dataset, std::string path, std::string file);

int main() {
    Dataset dataset;
    std::string file = "edges.csv";
    std::string path = "../real-world/graph2/";

    //testTSPBacktracking(dataset, path, file);
    testTSPTriangular(dataset, path, file);
    //testFunctions(dataset, path, file);

    //testConnecter(dataset, path, file);

    return 0;
}

void testConnecter(Dataset dataset, std::string path, std::string file){
    Parser parser;
    auto start = std::chrono::high_resolution_clock::now();
    auto e = parser.readFile(path + file,true);
    dataset.loadEdges(e);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
    Graph g = dataset.getGraph();
    bool possible = g.connectGraphThroughDjikstra();
    std::cout << "connecting the graph is " << possible << '\n';
}

void testFunctions(Dataset dataset,std::string path, std::string file) {
    Parser parser;

    auto e = parser.readFile(path + file,true);
    dataset.loadEdges(e);
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

    auto start = std::chrono::high_resolution_clock::now();

    auto e = parser.readFile(filePath + file,true);
    dataset.loadEdges(e);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();

    Graph graph = dataset.getGraph();
    graph.makeGraphFullyConnected();

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;

    double sumDist = Triangular::tspTriangular(graph,result);
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
