#include "movies.h"
#include <vector>
#include "edge.h"
#include <iostream>

using std::endl;
using std::cout;

int main() {

  // Test Vertices ( 1 & 2 similarity = 20) (1 & 3: 100)
  vector<Vertex> vertices;
  Vertex v1("tt0000009", "Miss Jerry", "None", vector<string>{"Blanche Bayliss", "William Courtenay", "Chauncey Depew"},  "Alexander Black", "USA", vector<string>{"Romance"}, 1894, 5.9, 302.4, "The adventures of a female reporter in the 1890s.");

  Vertex v2("tt0000574", "The Story of the Kelly Gang", "None", vector<string>{"Elizabeth Tait", "John Tait", "Norman Campbell", "Bella Cola", "Will Coyne"}, "Charles Tait", "Australia", vector<string>{"Biography", "Crime", "Drama"}, 1906, 6.1, 305.4, "True story of notorious Australian outlaw Ned Kelly (1855-80).");

  Vertex v3("tt0000010", "Miss Jerry2", "None", vector<string>{"Blanche Bayliss", "William Courtenay", "Chauncey Depew"}, "Alexander Black", "USA", vector<string>{"Crime", "Romance"}, 1894, 5.9, 302.4, "The adventures of a female reporter in the 1890s.");

  vertices.push_back(v1);
  vertices.push_back(v2);
  vertices.push_back(v3);
  
  Movies m(vertices);
  
  // Print textual output of the graph:
  m.getGraph().print();

  for (Vertex v : m.getGraph().getVertices()) {
    cout << v.get_id() << endl;
  }

  // Save an graph PNG:
  // m.getGraph().savePNG("Out");

  return 0;
}