// Created by rubem on 10-05-2024.
//
//

#include "Triangular.h"
#include <iostream>
#include <stack>
#include <queue>

std::vector<int> Triangular::findEulerianCircuit(Graph *graph) { // (nv)
    std::vector<int> circuit;
    std::stack<int> s;
    std::unordered_map<int, std::vector<int>> adjList;

    for(auto n : graph->getVertexSet()){
        for(auto e : n->getEdges()){
            adjList[n->getID()].push_back(e->getDest()->getID());
        }
    }

    s.push(graph->getVertexSet()[0]->getID());
    while(!s.empty()){
        int node = s.top();
        if(!adjList[node].empty()) {
            int adj = adjList[node].back();
            adjList[node].pop_back();
            s.push(adj);
        } else {
            circuit.push_back(node);
            s.pop();
        }
    }

    return circuit;
}

std::unordered_map<int, std::unordered_map<int, double>> Triangular::djikstra(Graph *graph, std::set<int> oddDegreeNodes){
    std::unordered_map<int, std::unordered_map<int, double>> shortestPaths;
    for(int first : oddDegreeNodes){
        std::unordered_map<int, double> distances;
        for(auto second : graph->getVertexSet()){
            distances[second->getID()] = INF;
        }
        distances[first] = 0;
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;

        pq.push({0, first});

        while (!pq.empty()) {
            int nodeID = pq.top().second;
            double d = pq.top().first;
            pq.pop();

            if(d > distances[nodeID]) continue;

            Node* node = graph->findNode(nodeID);

            if(node) {
                for(Edge* edge : node->getEdges()){
                    int destID = edge->getDest()->getID();
                    double distance = edge->getDistance();
                    if(distances[nodeID] + distance < distances[destID]){
                        distances[destID] = distances[nodeID] + distance;
                        pq.push({distances[destID], destID});
                    }
                }
            }
        }
        shortestPaths[first] = distances;
    }
    return shortestPaths;
}

Graph* Triangular::minimumWeightPerfectMatching(Graph *graph, std::set<int> oddDegreeNodes){
    Graph* matching = new Graph();

    std::unordered_map<int, std::unordered_map<int, double>> shortestPaths = djikstra(graph, oddDegreeNodes);

    std::vector<std::tuple<int, int, double>> edges; //cringe but yea

    for(int first : oddDegreeNodes){
        for(int second : oddDegreeNodes){
            if(first != second){
                edges.push_back({first, second, shortestPaths[first][second]});
            }
        }
    }

    std::sort(edges.begin(), edges.end(), [](const std::tuple<int, int, double>& a, const std::tuple<int, int, double>& b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    std::set<int> alreadyMatchedNodes;
    for(auto edge: edges){
        int first = std::get<0>(edge);
        int second = std::get<1>(edge);
        double distance = std::get<2>(edge);

        if(alreadyMatchedNodes.find(first) == alreadyMatchedNodes.end() && alreadyMatchedNodes.find(second) == alreadyMatchedNodes.end()){
            alreadyMatchedNodes.insert(first);
            alreadyMatchedNodes.insert(second);

            matching->addNode(new Node(first, graph->findNode(first)->getLongitude(), graph->findNode(first)->getLatitude()));
            matching->addNode(new Node(second, graph->findNode(second)->getLongitude(), graph->findNode(second)->getLatitude()));
            matching->addEdge(first, second, distance);
            matching->addEdge(second, first, distance);
        }

        if(alreadyMatchedNodes.size() == oddDegreeNodes.size()) break;
    }

    return matching;
}

Graph* Triangular::prim(Graph graph) {
    Graph* mst = new Graph();

    if(graph.getVertexSet().empty()){
        return {};
    }

    for(auto e: graph.getVertexSet()) {
        e->setDistance(INF);
        e->setPath(nullptr);
        e->setVisited(false);
    }

    Node* startingNode = graph.getVertexSet()[2];
    startingNode->setDistance(0);

    auto compare = [](Node* fNode, Node* lNode) { return fNode->getDistance() > lNode->getDistance(); };
    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> pq(compare);
    
    pq.push(startingNode);

    while(!pq.empty()) {
        Node* currentNode = pq.top();
        pq.pop();

        if(currentNode->isVisited()) {
            continue;
        }

        currentNode->setVisited(true);

        Node* mstNode = new Node(currentNode->getID(), currentNode->getLongitude(), currentNode->getLatitude());
        mst->addNode(mstNode);

        if(currentNode->getPath() != nullptr){
            Edge* mstEdge = currentNode->getPath();
            mst->addEdge(mstEdge->getOrig()->getID(), mstEdge->getDest()->getID(), mstEdge->getDistance());
            mst->addEdge(mstEdge->getDest()->getID(), mstEdge->getOrig()->getID(), mstEdge->getDistance());
        }

        for(auto e : currentNode->getEdges()) {
            Node *dest = e->getDest();
            if(e->getDistance() < dest->getDistance() && !dest->isVisited()) {
                dest->setDistance(e->getDistance());
                dest->setPath(e);
                pq.push(dest);
            }
        }
    }

    return mst;
}

std::set<int> getOddDegreeNodes(Graph *graph) {
    std::set<int> oddDegreeNodes;
    for (auto node : graph->getVertexSet()) {
        if (node->getEdges().size() % 2 != 0) {
            oddDegreeNodes.insert(node->getID());
        }
    }
    return oddDegreeNodes;
}

double calculateTotalDistance(const std::vector<int>& path, Graph* graph) {
    double totalDistance = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        Node* node = graph->findNode(path[i]);
        for (Edge* edge : node->getEdges()) {
            if (edge->getDest()->getID() == path[i + 1]) {
                totalDistance += edge->getDistance();
                break;
            }
        }
    }
    return totalDistance;
}


std::pair<double, std::vector<int>> Triangular::heuristic(Graph *graph){
    Graph *mst = prim(*graph);
    std::set<int> oddDegreeNodes = getOddDegreeNodes(mst);
    Graph *matching = minimumWeightPerfectMatching(mst, oddDegreeNodes);

    Graph matchedMST;

    for(auto n : mst->getVertexSet()){
        matchedMST.addNode(new Node(n->getID(), n->getLongitude(), n->getLatitude()));
    }

    for(auto n : mst->getVertexSet()){
        for(auto e : n->getEdges()){
            matchedMST.addEdge(e->getOrig()->getID(), e->getDest()->getID(), e->getDistance());
        }
    }
    
    for(auto n : matching->getVertexSet()){
        for(auto e : n->getEdges()) {
            matchedMST.addEdge(e->getOrig()->getID(), e->getDest()->getID(), e->getDistance());
        }
    }

    std::vector<int> eulerianPath = findEulerianCircuit(&matchedMST);

    std::vector<int> tsp;
    std::set<int> visited; // or mark all as not visited again??

    for(int i : eulerianPath){
        if(visited.find(i) == visited.end()){
            tsp.push_back(i);
            visited.insert(i);
        }
    }

    tsp.push_back(matchedMST.getVertexSet()[0]->getID());
    return {calculateTotalDistance(tsp, graph), tsp};
}
