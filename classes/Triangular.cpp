// Created by rubem on 10-05-2024.
//
//

#include "Triangular.h"
#include "Prim.h"
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>



double Triangular::tspTriangular(Graph graph,std::vector<int> &result) {
    int firstIndex = 0;
    int sumDist = 0;

    Graph* newGraph = Prim::prim(graph,firstIndex);

    Node *firstNode = (*newGraph).findNode(firstIndex);
    preOrderGraph(firstNode,*newGraph,(graph),result,sumDist);
    return sumDist;
}

void Triangular::preOrderGraph(Node *node, Graph graph, Graph oldGraph, std::vector<int> &result, int &sumDist) {
    std::queue<int> q;
    int finalIndex = 0;

    q.push(node->getID());
    while(!q.empty()) {
        int currentIndex = q.front();
        q.pop();
        finalIndex = currentIndex;
        result.push_back(currentIndex);
        auto n = graph.findNode(currentIndex);
        n->setVisited(true);
        for(auto e: n->getEdges()) {
            auto w = e->getDest();
            if(!w->isVisited()) {
                sumDist += e->getDistance();
                q.push(w->getID());
            }
        }
    }
    Edge *finalEdge = oldGraph.findEdge(finalIndex,node->getID());
    sumDist += finalEdge->getDistance();
    result.push_back(node->getID());
}
