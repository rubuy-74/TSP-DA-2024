#include <iostream>
#include "Dataset.h"
#include "Parser.h"
#include "TSP.h"

void testTSPBacktracking(Dataset dataset, std::string file);

int main() {
    Dataset dataset = Dataset();
    testTSPBacktracking(dataset,"shipping.csv");
    testTSPBacktracking(dataset,"stadiums.csv");
    testTSPBacktracking(dataset,"tourism.csv");
    return 0;
}

void testTSPBacktracking(Dataset dataset,std::string file) {
    Parser parser;

    auto e = parser.readFile("../toy-graphs/" + file,true);
    dataset.loadEdges(e);
    dataset.loadMatrix(e);

    int sum = 0;

    std::vector<double> path(dataset.getGraph().getNodeSize(),0);
    tspBT(dataset.getAdjMatrix(),dataset.getGraph().getNodeSize(),path);
    for(int i = 0; i < path.size(); i++) {
        sum += path[i];
    }
    std::cout << file << ": " << sum << '\n';
}