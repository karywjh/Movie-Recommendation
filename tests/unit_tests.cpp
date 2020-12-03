#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../edge.h"
#include "../movies.h"

#include <iostream>
#include <vector>

using std::endl;
using std::cout;


TEST_CASE("Movies constructor", "[weight=1][part=1]") {
  // Test Vertices ( 1 & 2 similarity = 20) (1 & 3: 100)
  vector<Vertex> vertices;
  Vertex v1("tt0000009", "Miss Jerry","The adventures of a female reporter in the 1890s.", "None", vector<string>{"Blanche Bayliss", "William Courtenay", "Chauncey Depew"}, "Alexander Black", "USA", vector<string>{"Romance"}, 1894, 5.9, 302.4);

  Vertex v2("tt0000574", "The Story of the Kelly Gang","True story of notorious Australian outlaw Ned Kelly (1855-80).", "None", vector<string>{"Elizabeth Tait", "John Tait", "Norman Campbell", "Bella Cola", "Will Coyne"}, "Charles Tait", "Australia", vector<string>{"Biography", "Crime", "Drama"}, 1906, 6.1, 305.4);

  Vertex v3("tt0000010", "Miss Jerry2","The adventures of a female reporter in the 1890s.", "None", vector<string>{"Blanche Bayliss", "William Courtenay", "Chauncey Depew"}, "Alexander Black", "USA", vector<string>{"Crime", "Romance"}, 1894, 5.9, 302.4);

  vertices.push_back(v1);
  vertices.push_back(v2);
  vertices.push_back(v3);

  Movies m;

  for (Vertex v : vertices) {
    m.insertMovieConnection(v);
  }

  // Print textual output of the graph:
  m.getGraph().print();

  for (Vertex v : m.getGraph().getVertices()) {
    cout << v.get_id() << " " << v.get_name() << endl;
  }

  Graph g = m.getGraph();
  REQUIRE(g.vertexExists(v1));
  REQUIRE(g.vertexExists(v2));
  REQUIRE(g.vertexExists(v3));

  REQUIRE(!g.edgeExists(v1, v2));
  REQUIRE(g.edgeExists(v1, v3));
}