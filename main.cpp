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
 * Need to run constructor (./main constructor edgefile_name num_vertices edge_file) 
 * BFS run with default 3000 vertices graph (./main BFS)
 * Shortest Path
 * Graph coloring
 */
int main(int argc, char** argv) {
  auto start = high_resolution_clock::now();

  if (argc == 5 && strcmp(argv[1], "constructor") == 0) {  
    try {
      if (strcmp(argv[4], "true") == 0) {
        Movies m("IMDb moviesCSV.csv", argv[2], std::stoi(argv[3]), true);
        m.getGraph().print();
        cout << "number of vertices: " << m.getGraph().getVertices().size() << endl;

      } else if (strcmp(argv[4], "false") == 0) {
        Movies m("IMDb moviesCSV.csv", argv[2], std::stoi(argv[3]));
        m.getGraph().print();
      } else {
        throw std::invalid_argument("invalid boolean: fourth arg");
      }
    } catch (std::exception e) {
      throw std::invalid_argument(e.what());
    }
  } else if (argc == 2 && strcmp(argv[1], "BFS") == 0) {
    Movies m("IMDb moviesCSV.csv", "out3000.csv", 3000, true);
  } else {
    cout << "Invalid Argument" << endl;
  }
  

  // Save an graph PNG:
  // m.getGraph().savePNG("Out");

  // Calculate total time for program to run
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << "Program takes " << (duration.count() / 1000.0) << "s" << endl;
  return 0;
}