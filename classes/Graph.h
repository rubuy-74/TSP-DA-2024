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


Node *Graph::findNode(int id) const {
    for(auto it = this->nodes.begin(); it != this->nodes.end();it++) {
        if(it->first == id) {
            return it->second;
        }
    }
}

Edge *Graph::findEdge(const int source, const int dest) const {
    Node* src = findNode(source);

    for(Edge* p: src->getEdges()) {
        if(p->getDest()->getID() == dest) {
            return p;
        }
    }
}

bool Graph::removeNode(const int id) {
    auto n = findNode(id);
    if(n == nullptr) return false;
    for(auto p: n->getEdges()) {
        removeEdge(id,p->getDest()->getID());
    }
    return true;
}

bool Graph::addEdge(const int source, const int dest, const double distance) {
    auto src = findNode(source);
    auto dst = findNode(dest);
    if(src == nullptr || dst == nullptr) {
        return false;
    }
    src->addEdge(dst,distance);
    return true;
}

bool Graph::removeEdge(const int source, const int dest) {
    auto src = findNode(source);
    auto dst = findNode(dest);
    if(src == nullptr || dst == nullptr) {
        return false;
    }
    return src->removeEdge(dst);
}

bool Graph::addNode(Node *n) {
    if(findNode(n->getID()) != NULL) return false;
    nodes.insert({n->getID(),n});
}

bool Node::addEdge(Node *dest, double distance) {
    Edge* edge = new Edge(dest,distance);
    this->edges.push_back(edge);
    return true;
}

bool Node::removeEdge(Node *dest) {
    for(auto e: this->edges) {
        if(e->getDest()->getID() == dest->getID()) {
            delete e;
            return true;
        }
    }
    return false;
}

#endif