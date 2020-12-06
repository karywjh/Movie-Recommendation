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

TEST_CASE("BFS traversal works correctly with 3 vertices; depth 1", "[weight=1][part=2]") {
  Graph g(true, false);
  Vertex v1("A");
  Vertex v2("B");
  Vertex v3("C");
  g.insertVertex(v3);
  g.insertVertex(v2);
  g.insertVertex(v1);
  g.insertEdge(v1, v2);
  g.insertEdge(v1, v3);
  Movies m(&g);
  vector<string> solution = {"A", "C", "B"};
  REQUIRE(m.BFS() == solution);
}

TEST_CASE("BFS traversal works correctly with 6 vertices; depth 2", "[weight=1][part=2]") {
  Graph g(true, false);
  Vertex v1("A");
  Vertex v2("B");
  Vertex v3("C");
  Vertex v4("D");
  Vertex v5("E");
  Vertex v6("F");
  g.insertVertex(v6);
  g.insertVertex(v5);
  g.insertVertex(v4);
  g.insertVertex(v3);
  g.insertVertex(v2);
  g.insertVertex(v1);
  g.insertEdge(v1, v2);
  g.insertEdge(v1, v3);
  g.insertEdge(v1, v4);
  g.insertEdge(v2, v5);
  g.insertEdge(v2, v6);
  Movies m(&g);
  vector<string> solution = {"B", "F", "E", "A", "D", "C"};
  REQUIRE(m.BFS() == solution);
}

TEST_CASE("BFS traversal works correctly with 8 vertices; depth 3", "[weight=1][part=2]") {
  Graph g(true, false);
  Vertex v1("A");
  Vertex v2("B");
  Vertex v3("C");
  Vertex v4("D");
  Vertex v5("E");
  Vertex v6("F");
  Vertex v7("G");
  Vertex v8("H");
  g.insertVertex(v8);
  g.insertVertex(v7);
  g.insertVertex(v6);
  g.insertVertex(v5);
  g.insertVertex(v4);
  g.insertVertex(v3);
  g.insertVertex(v2);
  g.insertVertex(v1);
  g.insertEdge(v1, v2);
  g.insertEdge(v1, v3);
  g.insertEdge(v1, v4);
  g.insertEdge(v3, v5);
  g.insertEdge(v3, v6);
  g.insertEdge(v5, v7);
  g.insertEdge(v4, v8);
  Movies m(&g);
  vector<string> solution = {"B", "A", "D", "C", "H", "F", "E", "G"};
  REQUIRE(m.BFS() == solution);
}

TEST_CASE("BFS traversal works correctly with 10 vertices; depth 4", "[weight=1][part=2]") {
  Graph g(true, false);
  Vertex v1("A");
  Vertex v2("B");
  Vertex v3("C");
  Vertex v4("D");
  Vertex v5("E");
  Vertex v6("F");
  Vertex v7("G");
  Vertex v8("H");
  Vertex v9("I");
  Vertex v10("J");
  g.insertVertex(v10);
  g.insertVertex(v9);
  g.insertVertex(v8);
  g.insertVertex(v7);
  g.insertVertex(v6);
  g.insertVertex(v5);
  g.insertVertex(v4);
  g.insertVertex(v3);
  g.insertVertex(v2);
  g.insertVertex(v1);
  g.insertEdge(v1, v2);
  g.insertEdge(v1, v3);
  g.insertEdge(v1, v4);
  g.insertEdge(v3, v5);
  g.insertEdge(v3, v6);
  g.insertEdge(v5, v7);
  g.insertEdge(v4, v8);
  g.insertEdge(v7, v9);
  g.insertEdge(v7, v10);
  Movies m(&g);
  vector<string> solution = {"B", "A", "D", "C", "H", "F", "E", "G", "J", "I"};
  REQUIRE(m.BFS() == solution);
}