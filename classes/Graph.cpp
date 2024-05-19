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

std::unordered_map<int, std::unordered_map<int, double>> Graph::floydWarshall() {
    std::unordered_map<int, std::unordered_map<int, double>> dist;

    for(auto& node1 : nodes) {
        for(auto& node2 : nodes) {
            dist[node1.first][node2.first] = (node1.first == node2.first) ? 0 : INF;
        }
    }

    for(auto& node1 : nodes) {
        for(auto& edge : node1.second->getEdges()) {
            int destID = edge.second->getDest()->getID();
            double distance = edge.second->getDistance();
            dist[node1.first][destID] = distance;
        }
    }

    for(auto& k : nodes) {
        for(auto& i : nodes) {
            for(auto& j : nodes) {
                if(dist[i.first][k.first] < INF && dist[k.first][j.first] < INF) {
                    dist[i.first][j.first] = std::min(dist[i.first][j.first], dist[i.first][k.first] + dist[k.first][j.first]);
                }
            }
        }
    }
    return dist;
}

bool Graph::connectGraphThroughDjikstra() {
    auto shortestPaths = floydWarshall();

    for(auto& node1 : nodes) {
        for(auto& node2 : nodes) {
            if(node1.first != node2.first) {
                if(findEdge(node1.first, node2.first) == nullptr) {
                    double distance = shortestPaths[node1.first][node2.first];
                    if(distance != INF) {
                        addEdge(node1.first, node2.first, distance);
                        addEdge(node2.first, node1.first, distance);
                    } else {
                        std::cerr << "Cannot fully connect the graph, as there is no path between node " << node1.first << " and node " << node2.first << std::endl;
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
    size_t n = vertices.size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            Node* n1 = vertices[i];
            Node* n2 = vertices[j];

            if (findEdge(n1->getID(), n2->getID()) == nullptr) {
                double distance = calculate_distance(n1->getLatitude(), n1->getLongitude(), n2->getLatitude(), n2->getLongitude());
                addEdge(n1->getID(), n2->getID(), distance);
                addEdge(n2->getID(), n1->getID(), distance);
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
