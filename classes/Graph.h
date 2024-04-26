#ifndef GRAPH_H_
#define GRAPH_H_

#include <unordered_map>
#include <vector>

class Graph {
   private:
      std::unordered_map<int, Node*> nodes;
   public:
      Node* findNode(const int id) const;
      Edge* findEdge(const int source, const int dest) const;

      int getNodeSize() const { return nodes.size(); }

      bool addNode(const Node* n);
      bool removeNode(const int id);

      bool addEdge(const int source, const int dest, const double distance);
      bool removeEdge(const int source, const int dest);
};

class Node {
   private:
      int id;
      double longitude;
      double latitude;
      std::vector<Edge*> edges;
   public:
      Node(int _id, double _longitude, double _latitude) : id(_id), longitude(_longitude), latitude(_latitude) {};

      int getID() const { return this->id; }

      std::vector<Edge*> getEdges() const { return this->edges; }
      void setEdges(std::vector<Edge*> edges) { this->edges = edges; }

      bool addEdge(Node* dest, double capacity);
      bool removeEdge(Edge* edge);
};

class Edge {
   private:
      Node* dest;
      double capacity;
   public:
      Edge(Node* _dest, double _capacity) : dest(_dest), capacity(_capacity) {};

      Node* getDest() const { return this->dest; }
      void setDest(Node* dest) { this->dest = dest; }

      double getCapacity() const { return this->capacity; }
      void setCapacity(double capacity) { this->capacity = capacity; }
};

#endif