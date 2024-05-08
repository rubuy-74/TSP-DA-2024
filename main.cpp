#include "Dataset.h"
#include "Parser.h"
#include <iostream>

int main() {
    Dataset dataset = Dataset();
    Parser parser;
    auto e = parser.readFile("../toy-graphs/shipping.csv",true);
    dataset.loadEdges(e);
    dataset.initializeAdjacencyMatrix();
    return 0;
}