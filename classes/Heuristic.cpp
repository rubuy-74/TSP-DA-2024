#include <stack>
#include <queue>
#include <algorithm>
#include "Heuristic.h"

std::vector<int> Heuristic::findEulerianCircuit(Graph *graph) { // (nv)
    std::vector<int> circuit;
    std::stack<int> s;
    std::unordered_map<int, std::vector<int>> adjList;

    for(auto n : graph->getVertexSet()){
        for(auto e : n->getEdges()){
            adjList[n->getID()].push_back(e.second->getDest()->getID());
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

std::unordered_map<int, std::unordered_map<int, double>> Heuristic::heuristicDjikstra(Graph *graph, std::set<int> oddDegreeNodes){
    std::unordered_map<int, std::unordered_map<int, double>> shortestPaths;
    for(int first : oddDegreeNodes){
        std::unordered_map<int, double> distances;
        for(auto second : oddDegreeNodes){
            distances[second] = INF;
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
        shortestPaths[first] = distances;
    }
    return shortestPaths;
}

Graph* Heuristic::minimumWeightPerfectMatching(Graph *graph, std::set<int> oddDegreeNodes){
    Graph* matching = new Graph();

    std::unordered_map<int, std::unordered_map<int, double>> shortestPaths = heuristicDjikstra(graph, oddDegreeNodes);

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
        for (auto edge : node->getEdges()) {
            if (edge.second->getDest()->getID() == path[i + 1]) {
                totalDistance += edge.second->getDistance();
                break;
            }
        }
    }
    return totalDistance;
}

std::pair<double, std::vector<int>> Heuristic::heuristic(Graph *graph){
    Graph *mst = Prim::prim(*graph);
    std::set<int> oddDegreeNodes = getOddDegreeNodes(mst);
    Graph *matching = minimumWeightPerfectMatching(mst, oddDegreeNodes);

    Graph matchedMST;

    for(auto n : mst->getVertexSet()){
        matchedMST.addNode(new Node(n->getID(), n->getLongitude(), n->getLatitude()));
    }

    for(auto n : mst->getVertexSet()){
        for(auto e : n->getEdges()){
            matchedMST.addEdge(e.second->getOrig()->getID(), e.second->getDest()->getID(), e.second->getDistance());
        }
    }

    for(auto n : matching->getVertexSet()){
        for(auto e : n->getEdges()) {
            matchedMST.addEdge(e.second->getOrig()->getID(), e.second->getDest()->getID(), e.second->getDistance());
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
