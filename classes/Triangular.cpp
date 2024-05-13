//
// Created by rubem on 10-05-2024.
//

#include "Triangular.h"

Graph Triangular::prim(Graph graph) {
    int smallestValueIndex = graph.getNodeSize() - 1;
    if(graph.getVertexSet().empty()){
        return {};
    }

    for(auto e: graph.getVertexSet()) {
        e->setDistance(INF);
        e->setPath(nullptr);
        e->setVisited(false);
    }

    for(int i = 0; i < graph.getVertexSet().size(); i++) {
        if(graph.getVertexSet()[i]->getID() < graph.getVertexSet()[smallestValueIndex]->getID())
            smallestValueIndex = i;
    }
    auto s = graph.getVertexSet()[smallestValueIndex];
    s->setDistance(0);

    MutablePriorityQueue<Node> q;
    q.insert(s);

    while(!q.empty()) {
        Node *w = q.extractMin();
        for(auto e : w->getEdges()) {
            Node *dest = e->getDest();
            double oldDist = dest->getDistance();
            if(e->getDistance() < dest->getDistance() && !dest->isVisited()) {
                dest->setDistance(e->getDistance());
                dest->setPath(e);
                if(oldDist == INF) {
                    q.insert(dest);
                } else {
                    q.decreaseKey(dest);
                }
            }
        }
        w->setVisited(true);
    }
    return graph;
}
