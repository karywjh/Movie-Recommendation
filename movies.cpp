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

/**
 * Actor:       bool  30
 * Director:    bool  30
 * Country:     bool  10
 * Year:    dif <= 5  10
 * Genre:       bool  10
 * Avg_vote: dif <= 2 10
 * 
 * Connect Score >= 30 (weight <= 1/30)
 */
double Movies::calcWeight(Vertex u, Vertex v) {
    int total_score;

    if ((u.get_id() == v.get_id()))
        total_score += 30;

    if (u.get_director() == v.get_director())
        total_score += 30;

    if ((u.get_country() == v.get_country()))
        total_score += 10;

    if ((abs(u.get_year() - v.get_year()) <= 5))
        total_score += 10;

    if ((abs(u.get_popularity() - v.get_popularity()) <= 2))
        total_score += 10;

    for(auto i = u.get_genre().begin(); i != u.get_genre().end(); i++) {
        for(auto j = v.get_genre().begin(); j != v.get_genre().end(); j++) {
            if (*i == *j) {
                total_score += 10;
                return 1 / double(total_score);
            }
        }
    }
    
    return 1 / double(total_score);
}
