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
  Vertex v1("tt0000009", "Miss Jerry", "None", vector<string>{"Blanche Bayliss", "William Courtenay", "Chauncey Depew"},  "Alexander Black", "USA", vector<string>{"Romance"}, 1894, 5.9, 302.4, "The adventures of a female reporter in the 1890s.");

  Vertex v2("tt0000574", "The Story of the Kelly Gang", "None", vector<string>{"Elizabeth Tait", "John Tait", "Norman Campbell", "Bella Cola", "Will Coyne"}, "Charles Tait", "Australia", vector<string>{"Biography", "Crime", "Drama"}, 1906, 6.1, 305.4, "True story of notorious Australian outlaw Ned Kelly (1855-80).");

  Vertex v3("tt0000010", "Miss Jerry2", "None", vector<string>{"Blanche Bayliss", "William Courtenay", "Chauncey Depew"}, "Alexander Black", "USA", vector<string>{"Crime", "Romance"}, 1894, 5.9, 302.4, "The adventures of a female reporter in the 1890s.");

  Vertex v4("tt0000011", "Miss Jerry3", "None", vector<string>{"Blanche Bayliss", "William Courtenay", "Chauncey Depew"}, "Alexander Black", "USA", vector<string>{"Crime", "Romance"}, 1894, 5.9, 302.4, "The adventures of a female reporter in the 1890s.");
  
  vertices.push_back(v1);
  vertices.push_back(v2);
  vertices.push_back(v3);
  vertices.push_back(v4);

  Movies m(vertices);

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
  REQUIRE(g.getEdges().size() == 3);
}

TEST_CASE("Movies constructor with read small file", "[weight=1][part=1]") {
  Movies m("tests/Test_Small.csv");
  m.getGraph().print();

  for (Vertex v : m.getGraph().getVertices()) {
    cout << v.get_id() << " " << v.get_name() << endl;
  }

  Graph g = m.getGraph();
  REQUIRE(g.vertexExists("tt0002101"));
  REQUIRE(g.vertexExists("tt0003165"));
  REQUIRE(g.vertexExists("tt0003740"));
  REQUIRE(g.getEdges().size() == 4);
}


// TEST_CASE("Movies constructor with read entire file", "[weight=1][part=1]") {
//   Movies m("IMDb moviesCSV.csv");
//   // for (Vertex v : m.getGraph().getVertices()) {
//   //   cout << v.get_id() << " " << v.get_name() << endl;
//   // }
//   // cout << m.getGraph().getVertices().size() << endl;

//   m.getGraph().print();
// }

TEST_CASE("Movies constructor with num of lines as arg", "[weight=1][part=1]") {
  Movies m("IMDb moviesCSV.csv", 500);
  // for (Vertex v : m.getGraph().getVertices()) {
  //   cout << v.get_id() << " " << v.get_name() << endl;
  // }
  // cout << m.getGraph().getVertices().size() << endl;

  m.getGraph().print();
  REQUIRE(m.getGraph().getEdges().size() == 1647);
}