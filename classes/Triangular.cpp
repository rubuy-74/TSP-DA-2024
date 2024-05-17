//
// Created by rubem on 10-05-2024.
//

#include "Triangular.h"
#include <queue>

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

    Node* startingNode = graph.getVertexSet()[0];
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
