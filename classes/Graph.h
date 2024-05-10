#ifndef GRAPH_H_
#define GRAPH_H_

#include <unordered_map>
#include <vector>

class Graph;
class Node;
class Edge;

class Graph {
   private:
      std::unordered_map<int, Node*> nodes;
   public:
      Node* findNode(int id) const;
      Edge* findEdge(int source, int dest) const;

      int getNodeSize() const { return nodes.size(); }

      bool addNode(Node* n);
      bool removeNode(int id);

      bool addEdge(int source, int dest, double distance);
      bool removeEdge(int source, int dest);
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
      int getLongitude() const { return this->longitude; }
      int getLatitude() const { return this->latitude; }

      std::vector<Edge*> getEdges() const { return this->edges; }
      void setEdges(std::vector<Edge*> edges) { this->edges = edges; }

      bool addEdge(Node* dest, double distance);
      bool removeEdge(Node* edge);
};



class Edge {
   private:
      Node* dest;
      double distance;
   public:
      Edge(Node* _dest, double _distance) : dest(_dest), distance(_distance) {};

      Node* getDest() const { return this->dest; }
      void setDest(Node* dest) { this->dest = dest; }

      double getDistance() const { return this->distance; }
      void setDistance(double capacity) { this->distance = distance; }
};

#endif