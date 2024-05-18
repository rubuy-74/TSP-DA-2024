#include <iostream>
#include "Dataset.h"
#include "Parser.h"
#include "TSP.h"
#include "Triangular.h"

void testTSPBacktracking(Dataset dataset, std::string file);
void testTSPTriangular(Dataset dataset, std::string file);
void displayGraph(Graph graph);
void testFunctions(Dataset dataset, std::string file);

int main() {
    Dataset dataset = Dataset();
    //testTSPBacktracking(dataset,"edges_25.csv");
    //testTSPTriangular(dataset,"stadiums.csv");
    testFunctions(dataset, "edges.csv");
    return 0;
}

void testFunctions(Dataset dataset, std::string file) {
    Parser parser;

    auto e = parser.readFile("../real-world/graph2/" + file,true);
    dataset.loadEdges(e);
    dataset.loadMatrix(e);
    Graph g = dataset.getGraph();
    std::pair<double, std::vector<int>> tsp = Triangular::heuristic(&g);
    std::cout << "total cost: " << tsp.first << '\n';
    for(int i = 0; i < tsp.second.size(); i++) {
        std::cout << tsp.second[i] << ", ";
    }
}

void testTSPBacktracking(Dataset dataset,std::string file) {
    Parser parser;

    auto e = parser.readFile("../toy-graphs/" + file,true);
    dataset.loadEdges(e);
    dataset.loadMatrix(e);

    double sum = 0;

    std::vector<double> path(dataset.getGraph().getNodeSize(),0);
    std::cout << TSP::tspBT(dataset.getAdjMatrix(),dataset.getGraph().getNodeSize(),path)<< "\n";
    std::cout << "path:" << '\n';
    for(int i = 0; i < path.size(); i++) {
        std::cout << path[i] << ", ";
    }
    std::cout << "0 \n";
}

void testTSPTriangular(Dataset dataset, std::string file) {
    Parser parser;
    Node *end;
    std::vector<int> resultPath;

    auto e = parser.readFile("../toy-graphs/" + file,true);
    dataset.loadEdges(e);
    dataset.loadMatrix(e);
    Graph* newGraph = Triangular::prim(dataset.getGraph());
    for(auto n : newGraph->getVertexSet()) {
        if(n->getPath() != nullptr && n->getPath()->getDest() == nullptr)
            end = n;
    } // why??

    displayGraph(dataset.getGraph());
    std::cout << "----------------------------------------" << '\n';
    displayGraph(*newGraph);
}

void displayGraph(Graph graph) {
    for(auto n : graph.getVertexSet()) {
        std::cout << n->getID() << "\n";
        for(auto e : n->getEdges()) {
            std::cout << "  " << e->getDest()->getID() << ": " << e->getDistance() << '\n';
        }
    }
}