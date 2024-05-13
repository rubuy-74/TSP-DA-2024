#include <iostream>
#include "Dataset.h"
#include "Parser.h"
#include "TSP.h"
#include "Triangular.h"

void testTSPBacktracking(Dataset dataset, std::string file);
void testTSPTriangular(Dataset dataset, std::string file);
void displayGraph(Graph graph);

int main() {
    Dataset dataset = Dataset();
    testTSPBacktracking(dataset,"tourism.csv");
    testTSPTriangular(dataset,"tourism.csv");
    return 0;
}

void testTSPBacktracking(Dataset dataset,std::string file) {
    Parser parser;

    auto e = parser.readFile("../toy-graphs/" + file,true);
    dataset.loadEdges(e);
    dataset.loadMatrix(e);

    int sum = 0;

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
    Graph newGraph = Triangular::prim(dataset.getGraph());
    for(auto n : newGraph.getVertexSet()) {
        if(n->getPath() != nullptr && n->getPath()->getDest() == nullptr)
            end = n;
    }
    for(auto n : newGraph.getVertexSet()) {
        std::cout << n->getID() << '\n';
        std::cout << "  " << n->getPath()->getOrig()->getID() << '\n';
        std::cout << "  " << n->getPath()->getDistance() << '\n';
    }
}

void displayGraph(Graph graph) {
    for(auto n : graph.getVertexSet()) {
        std::cout << n->getID() << "\n";
        for(auto e : n->getEdges()) {
            std::cout << "  " << e->getDest()->getID() << ": " << e->getDistance() << '\n';
        }
    }
}