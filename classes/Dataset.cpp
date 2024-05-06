#include <string>
#include "Dataset.h"
#include "Graph.h"

Dataset::Dataset() {
   this->routes = Graph();
}

Dataset::Dataset(std::list<std::vector<std::string>> nodes, std::list<std::vector<std::string>> edges) {
   loadNodes(nodes);
   loadEdges(edges);
}

void Dataset::loadNodes(std::list<std::vector<std::string>> nodes) {
   for(std::vector<std::string> n : nodes) {
      Node* node = new Node(stoi(n[0]), stod(n[1]), stod(n[2]));
      routes.addNode(node);
   }
}

void Dataset::loadEdges(std::list<std::vector<std::string>> edges) {
   for(std::vector<std::string> e : edges) {
      routes.addEdge(stoi(e[0]), stoi(e[1]), stod(e[2]));
   } // check pop
}