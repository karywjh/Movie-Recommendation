#include "movies.h"
#include <vector>
#include "edge.h"
#include <iostream>
#include <chrono> 
#include <exception>
#include <string.h>
#include<stdio.h> 

using std::endl;
using std::cout;
using namespace std::chrono;

/**
 * Need to run:
 * make final_project
 * constructor  (./final_project constructor num_vertices) -- run with original csv 
 *              (./final_project constructor edgefile_name num_vertices)
 *              (./final_project constructor edgefile_name num_vertices)
 * BFS run with default 3000 vertices graph (./final_project BFS)
 * Shortest Path (./final_project shortestpath) or (./final_project shortestpath id)
 * Graph coloring (./final_project coloring)
 */
int main(int argc, char** argv) {
  auto start = high_resolution_clock::now();

  // default if no arguments are passed
  if (argc == 1) {
    Movies m("IMDb moviesCSV.csv", "out3000.csv", 3000, true);
    cout << "Constructed graph with 3000 vertices" << endl;
  }

  // Run Graph Coloring
  else if (strcmp(argv[1], "coloring") == 0) {
    Movies m("IMDb moviesCSV.csv", "out3000.csv", 3000, true);
    cout << "Constructed graph with 3000 vertices" << endl;
    cout << "Requires " << m.greedyColoring() << " colors" << endl;
  }

  // Run BFS
  else if (strcmp(argv[1], "BFS") == 0) {
    Movies m("IMDb moviesCSV.csv", "out3000.csv", 3000, true);
    vector<Vertex> vector = m.BFS();

    // print all Movies names
    cout << "Printing all movies' names in BFS order:" << endl;
    for (Vertex v : vector) {
      cout << v.get_name() << " ";
    }
    cout << endl;

    // BFS size should be total vertex number
    cout << "BFS vector size: " << vector.size() << endl;
    cout << "Graph total vertices: " << m.getGraph().getVertices().size() << endl;
  }

  // Run Shortest Path
  else if (strcmp(argv[1], "shortestpath") == 0) {
    Movies m("IMDb moviesCSV.csv", "out3000.csv", 3000, true);
    vector<Vertex> vector;

    // Run with default source vertex
    if (argc == 2) {
      vector = m.shortestPath(Vertex("tt0004181"));
      cout << "Shortest Path from Movie tt0004181: (Not directly connected)" << endl;

      for (Vertex v : vector) {
        cout << v.get_id() << ": " << v.get_name() << endl;
      }
    }
    // Run with user input's id as source
    else {
      try {
        m.shortestPath(Vertex(argv[2]));
        cout << "Shortest Path from Movie " << argv[2] << ": (Not directly connected)" << endl;
        for (Vertex v : vector) {
          cout << v.get_id() << ": " << v.get_name() << endl;
        }
      } catch(std::exception e) {
        throw std::invalid_argument(e.what());
      }
    }
  }

  // Run Constructor with different args
  else if (strcmp(argv[1], "constructor") == 0) {
    try {
      if (argc == 2 || (argc == 3 && strcmp(argv[2], "print") == 0)) {
        Movies m("IMDb moviesCSV.csv", "out3000.csv", 3000, true);
        if (strcmp(argv[2], "print") == 0)
          m.getGraph().print();

        cout << "Constructed graph with 3000 vertices" << endl;
      }

      else if (argc == 3 || (argc == 4 && strcmp(argv[3], "print") == 0)) {
        Movies m("IMDb moviesCSV.csv", "output.csv", std::stoi(argv[2]));
        if (strcmp(argv[3], "print") == 0)
          m.getGraph().print();

        cout << "Constructed graph with " << argv[2] << " vertices using original dataset (will be slower than running with edgefile)" << endl;
      }

      else if (argc == 4 || (argc == 5 && strcmp(argv[4], "print") == 0)) {
        Movies m("IMDb moviesCSV.csv", argv[2], std::stoi(argv[3]), true);
        if (strcmp(argv[4], "print") == 0)
          m.getGraph().print();

        cout << "Constructed graph with " << argv[3] << " vertices using edgefile. (will be faster than using original dataset)" << endl;
      }

      else {
        cout << "Too many arguments" << endl;
      }
    } catch (std::exception e) {
      throw std::invalid_argument(e.what());
    }
  }

  else {
    cout << "Invalid Argument" << endl;
  }
  
  // Calculate total time for program to run
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << "Program takes " << (duration.count() / 1000.0) << "s" << endl;
  return 0;
}