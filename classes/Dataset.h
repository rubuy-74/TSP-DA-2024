#ifndef DATASET_H_
#define DATASET_H_

#include "Graph.h"
#include <list>
#include <string>

class Dataset {
   private:
      Graph routes;
      std::vector<std::vector<double>> adjacencyMatrix;
   public:
      Dataset();
      Dataset(std::list<std::vector<std::string>> nodes, std::list<std::vector<std::string>> edges);

      void loadNodes(std::list<std::vector<std::string>> nodes);
      void loadEdges(std::list<std::vector<std::string>> edges);


      Graph getGraph() const { return this->routes; }
      std::vector<std::vector<double>> getAdjMatrix() const { return this->adjacencyMatrix; }

      void loadMatrix(std::list<std::vector<std::string>> edges);

      void initializeAdjacencyMatrix(std::list<std::vector<std::string>> edges);
};

#endif