#pragma once

#include "graph.h"
#include "edge.h"
#include "vertex.h"

class Movies {
    public:

        Movies();
        
        /**
         * Returns a constant reference to the state space graph.
         *
         * @returns A constant reference to the state space graph.
         */
        const Graph & getGraph() const { return g_; }

        void BFS(Graph);

        void BFS(Graph, Vertex);

    private:
        Graph g_;
        Vertex startingVertex_;
};