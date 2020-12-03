#pragma once

#include "graph.h"
#include "edge.h"
#include "vertex.h"

class Movies {
    public:

        Movies();
        // Movies(file);

        /**
         * Returns a constant reference to the state space graph.
         *
         * @returns A constant reference to the state space graph.
         */
        const Graph & getGraph() const { return g_; }

        void BFS(Graph);

        void BFS(Graph, Vertex);

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
        double calcWeight(Vertex u, Vertex v);

    private:
        Graph g_;
        Vertex startingVertex_;
};