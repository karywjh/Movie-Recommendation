#include "movies.h"
#include <queue>
using std::string;
using std::queue;
Movies::Movies() : g_(true) {
    
}

void Movies::BFS(Graph G) {
    for(Vertex v: G.getVertices()) {
        v.set_label("UNEXPLORED");
    }
    for(Edge e: G.getEdges()) {
        e.setLabel("UNEXPLORED");
    }
    for(Vertex v: G.getVertices()) {
        if(v.get_label() == "UNEXPLORED") {
            BFS(G, v);
        }
    }
}

void Movies::BFS(Graph G, Vertex v) {
    queue<Vertex> q;
    v.set_label("VISITED");
    q.push(v);

    while(!q.empty()) {
        v = q.back();
        cout << "name: " << v.get_name() << " Description: " << v.get_description() << endl;
        q.pop();
        for(Vertex w: G.getAdjacent(v)) {
            if(w.get_label() == "UNEXPLORED") {
                G.setEdgeLabel(v, w, "DISCOVERY");
                w.set_label("VISITED");
                q.push(w);
            }
            else if(G.getEdge(v, w).getLabel() == "UNEXPLORED") {
                G.setEdgeLabel(v, w, "CROSS");
            }
        }
    }
}