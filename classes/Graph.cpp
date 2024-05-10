#include "Graph.h"

Node *Graph::findNode(int id) const {
    for(auto it = this->nodes.begin(); it != this->nodes.end();it++) {
        if(it->first == id) {
            return it->second;
        }
    }
    return nullptr;
}

Edge *Graph::findEdge(const int source, const int dest) const {
    Node* src = findNode(source);

    for(Edge* p: src->getEdges()) {
        if(p->getDest()->getID() == dest) {
            return p;
        }
    }
    return nullptr;
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
    if(src == nullptr) {
        src = new Node(source,0,0);
        this->addNode(src);
    }
    if(dst == nullptr) {
        dst = new Node(dest, 0, 0);
        this->addNode(dst);
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
    if(findNode(n->getID()) != nullptr) return false;
    nodes.insert({n->getID(),n});
    return true;
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