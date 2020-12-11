#pragma once

#include "graph.h"
#include "edge.h"
#include "vertex.h"

class Movies {
    public:

        Movies();
        Movies(const Graph*);
        Movies(vector<Vertex> vertices, string out_name);
        Movies(string file, string out_name); // reads entire file
        Movies(string file, string out_name, int num); // only reads first (num) numbers of lines

        Movies(string movies_file, string edge_file, bool read_edge); // insert edge from edge_file
        Movies(string movies_file, string edge_file, int num, bool read_edge);
        

        /**
         * Returns a constant reference to the state space graph.
         */
        const Graph & getGraph() const { return g_; }

        vector<string> BFS();

        void BFS(Graph*, Vertex, vector<string>&);

        vector<Vertex> shortestPath(Vertex);

        /**
         * Actor:       bool  30
         * Director:    bool  30
         * Country:     bool  10
         * Year:    dif <= 5  10
         * Genre:       bool  10
         * Popularity: dif <= 10 10
         * 
         * Connect Score >= 40 (weight <= 1/40)
         */
        double calcWeight(Vertex u, Vertex v);
        
        /**
         * Read one line into one vertex and return that vertex
         */
        Vertex lineToVertex(std::ifstream& inFile, string id);

        /**
         * Check Vertex v's similarity with all existing vertices
         * Connect if similarity reaches certain threshold
         * Output all edges (source, destrination) to output file
         */
        void insertMovieConnection(Vertex v, std::ofstream& outFile, string out_name);

        void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<string>>> dataset);

    private:
        Graph g_;
        unordered_map<Vertex, string, MyHash> map;
};