#ifndef GRAPH_H_
#define GRAPH_H_

#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

#define INF std::numeric_limits<int>::max()

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

      std::vector<Node *> getVertexSet();

      bool addNode(Node* n);
      bool removeNode(int id);

      bool addEdge(int source, int dest, double distance);
      bool removeEdge(int source, int dest);
      void makeGraphFullyConnected();
      bool connectGraphThroughDjikstra();
};

class Node {
protected:
      int id;
      double longitude;
      double latitude;
      double distance;
      bool visited;
      Edge *path;
      std::unordered_map<std::string, Edge*> edges;
   public:
      Node(int _id, double _longitude, double _latitude) : id(_id), longitude(_longitude), latitude(_latitude) {};

      int getID() const { return this->id; }
      int getLongitude() const { return this->longitude; }
      int getLatitude() const { return this->latitude; }

      bool isVisited() const { return this->visited; }
      void setVisited(bool v) { this->visited = v; }

      double getDistance() const { return this->distance; }
      void setDistance(double d) { this->distance = d; }

      Edge *getPath() { return this->path; }
      void setPath(Edge *edge) { this->path = edge; }

      std::unordered_map<std::string, Edge*> getEdges() const { return this->edges; }
      void setEdges(std::unordered_map<std::string, Edge*> edges) { this->edges = edges; }

      bool operator<(const Node &node) const;

      bool addEdge(Node* dest, double distance);
      bool removeEdge(Node* edge);


    int queueIndex = 0;     // Required by MutablePriorityQueue
};



class Edge {
   private:
      Node* dest;
      Node* orig;
      double distance;
   public:
      Edge(Node* _dest,Node *_orig, double _distance) : dest(_dest), orig(_orig),distance(_distance) {};

      Node* getDest() const { return this->dest; }
      void setDest(Node* dest) { this->dest = dest; }

      double getDistance() const { return this->distance; }
      void setDistance(double capacity) { this->distance = distance; }

      Node *getOrig() const { return this->orig; }
      void setOrig(Node* orig) { this->orig = orig; }
};

#endif