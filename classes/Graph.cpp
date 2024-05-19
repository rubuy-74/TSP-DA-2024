#include "Graph.h"
#include "Haversine.h"
#include <iostream>

Node* Graph::findNode(int id) const {
    auto n = nodes.find(id);
    if(n != nodes.end()){
        return n->second;
    }
    return nullptr;
}

std::unordered_map<int, std::unordered_map<int, double>> djikstra(Graph *graph){
    std::unordered_map<int, std::unordered_map<int, double>> shortestPaths;
    for(auto first : graph->getVertexSet()){
        std::unordered_map<int, double> distances;
        for(auto second : graph->getVertexSet()){
            distances[second->getID()] = INF;
        }
        distances[first->getID()] = 0;
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;

        pq.push({0, first->getID()});

        while (!pq.empty()) {
            int nodeID = pq.top().second;
            double d = pq.top().first;
            pq.pop();

            if(d > distances[nodeID]) continue;

            Node* node = graph->findNode(nodeID);

            if(node) {
                for(auto edge : node->getEdges()){
                    int destID = edge.second->getDest()->getID();
                    double distance = edge.second->getDistance();
                    if(distances[nodeID] + distance < distances[destID]){
                        distances[destID] = distances[nodeID] + distance;
                        pq.push({distances[destID], destID});
                    }
                }
            }
        }
        shortestPaths[first->getID()] = distances;
    }
    return shortestPaths;
}

bool Graph::connectGraphThroughDjikstra() {
    std::unordered_map<int, std::unordered_map<int, double>> shorteshPaths = djikstra(this);
    for(auto first : getVertexSet()){
        for(auto second : getVertexSet()){
            if(first->getID() != second->getID()){
                Edge* e = findEdge(first->getID(), second->getID());
                if(e == nullptr){
                    if(shorteshPaths[first->getID()][second->getID()] != INF){
                        addEdge(first->getID(), second->getID(), shorteshPaths[first->getID()][second->getID()]);
                        addEdge(second->getID(), first->getID(), shorteshPaths[first->getID()][second->getID()]);
                    }
                    else {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void Graph::makeGraphFullyConnected() {
    auto vertices = getVertexSet();
    for(auto n1 : vertices){
        if(n1->getEdges().size() == nodes.size() - 1) continue;
        for(auto n2 : vertices){
            if(n1->getID() != n2->getID()){
                Edge* e = findEdge(n1->getID(), n2->getID());
                if(e == nullptr){
                    const double distance = calculate_distance(n1->getLatitude(), n1->getLongitude(), n2->getLatitude(), n2->getLongitude());
                    addEdge(n1->getID(), n2->getID(), distance);
                    addEdge(n2->getID(), n1->getID(), distance);
                }
            }
        }
    }
}

Edge *Graph::findEdge(const int source, const int dest) const {
    Node* src = findNode(source);
    auto edges = src->getEdges();
    auto e = edges.find(std::to_string(source) + std::to_string(dest));

    if(e != src->getEdges().end()){
        return e->second;
    }
    return nullptr;
}

bool Graph::removeNode(const int id) {
    auto n = findNode(id);
    if(n == nullptr) return false;
    for(auto p: n->getEdges()) {
        removeEdge(id,p.second->getDest()->getID());
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

std::vector<Node *> Graph::getVertexSet() {
    std::vector<Node *> result;
    for(auto e: this->nodes) {
        result.push_back(e.second);
    }
    return result;
}

bool Node::addEdge(Node *dest, double distance) {
    Edge* edge = new Edge(dest,this,distance);
    this->edges.insert({std::to_string(this->getID()) + std::to_string(dest->getID()), edge});

    return true;
}

bool Node::removeEdge(Node *dest) {
    this->edges.erase(std::to_string(this->getID()) + std::to_string(dest->getID()));
    return true;
}

bool Node::operator<(const Node &node) const {
    return node.getID() > this->getID();
}
