#include <queue>
#include "Prim.h"

Graph* Prim::prim(Graph graph,int firstIndex) {
    Graph* mst = new Graph();

    if(graph.getVertexSet().empty()){
        return {};
    }

    for(auto e: graph.getVertexSet()) {
        e->setDistance(INF);
        e->setPath(nullptr);
        e->setVisited(false);
    }

    Node* startingNode = graph.getVertexSet()[firstIndex];
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
            Node *dest = e.second->getDest();
            if(e.second->getDistance() < dest->getDistance() && !dest->isVisited()) {
                dest->setDistance(e.second->getDistance());
                dest->setPath(e.second);
                pq.push(dest);
            }
        }
    }

    return mst;
}