#ifndef DATASET_H_
#define DATASET_H_

#include "Graph.h"
#include <list>

class Dataset {
   private:
      Graph routes;
   public:
      Dataset();
      Dataset(std::list<std::vector<std::string>> nodes, std::list<std::vector<std::string>> edges);

      void loadNodes(std::list<std::vector<std::string>> nodes);
      void loadEdges(std::list<std::vector<std::string>> edges);

      Graph getGraph() const { return this->routes; }
};

#endif