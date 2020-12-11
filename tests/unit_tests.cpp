#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../edge.h"
#include "../movies.h"

#include <iostream>
#include <vector>

using std::endl;
using std::cout;


TEST_CASE("Movies constructor from vector", "[weight=1][part=1]") {
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

  Movies m(vertices, "out_vector.csv");

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
  Movies m("tests/Test_Small.csv", "small_out.csv");
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
//   Movies m("IMDb moviesCSV.csv", "full_out.csv");
//   // for (Vertex v : m.getGraph().getVertices()) {
//   //   cout << v.get_id() << " " << v.get_name() << endl;
//   // }
//   // cout << m.getGraph().getVertices().size() << endl;

//   m.getGraph().print();
// }

TEST_CASE("Movies constructor with num of lines as arg", "[weight=1][part=1]") {
  Movies m("IMDb moviesCSV.csv", "out500.csv", 500);
  // for (Vertex v : m.getGraph().getVertices()) {
  //   cout << v.get_id() << " " << v.get_name() << endl;
  // }
  // cout << m.getGraph().getVertices().size() << endl;

  m.getGraph().print();
  REQUIRE(m.getGraph().getEdges().size() == 1647);
}

TEST_CASE("Movies constructor with edge file as arg (small dataset)", "[weight=1][part=1]") {
  Movies t("tests/Test_Small.csv", "small_out.csv");
  Movies m("tests/Test_Small.csv", "small_out.csv", true); // read from edge file

  m.getGraph().print();
  REQUIRE(m.getGraph().getEdges().size() == 4);
}

TEST_CASE("Movies constructor with edge file as arg (500 lines)", "[weight=1][part=1]") {
  Movies t("IMDb moviesCSV.csv", "out500.csv", 500);
  Movies m("IMDb moviesCSV.csv", "out500.csv", 500, true);

  m.getGraph().print();
  REQUIRE(m.getGraph().getEdges().size() == 1647);
}

TEST_CASE("Movies constructor with edge file as arg (3000 lines)", "[weight=1][part=1]") {
  clock_t tStart = clock();
    
  // Movies t("IMDb moviesCSV.csv", "out3000.csv", 3000);
  Movies m("IMDb moviesCSV.csv", "out3000.csv", 3000, true);

  m.getGraph().print();

  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  REQUIRE(m.getGraph().getEdges().size() == 33207);
}

TEST_CASE("BFS traversal works correctly with 3 vertices; length 1， with one disconnected", "[weight=1][part=2]") {
  Graph g(true, false);
  Vertex v1("A");
  Vertex v2("B");
  Vertex v3("C");
  Vertex v4("D");
  g.insertVertex(v4);
  g.insertVertex(v3);
  g.insertVertex(v2);
  g.insertVertex(v1);
  g.insertEdge(v1, v2);
  g.insertEdge(v1, v3);
  Movies m(&g);
  vector<Vertex> solution = {v1, v3, v2, v4};
  REQUIRE(m.BFS() == solution);
  REQUIRE(m.BFS().size() == m.getGraph().getVertices().size());
}

TEST_CASE("BFS traversal works correctly with 6 vertices; length 2", "[weight=1][part=2]") {
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
  vector<Vertex> solution = {v2, v6, v5, v1, v4, v3};
  REQUIRE(m.BFS() == solution);
}

TEST_CASE("BFS traversal works correctly with 8 vertices; length 3", "[weight=1][part=2]") {
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
  vector<Vertex> solution = {v2, v1, v4, v3, v8, v6, v5, v7};
  REQUIRE(m.BFS() == solution);
}

TEST_CASE("BFS traversal works correctly with 10 vertices; length 4", "[weight=1][part=2]") {
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
  vector<Vertex> solution = {v2, v1, v4, v3, v8, v6, v5, v7, v10, v9};
  REQUIRE(m.BFS() == solution);
}

TEST_CASE("shortest path works with 2 nodes one edge", "[weight=1][part=3]") {
  Graph g(true, false);
  Vertex v1("A");
  Vertex v2("B");
  g.insertVertex(v2);
  g.insertVertex(v1);
  g.insertEdge(v1, v2);
  g.setEdgeWeight(v1, v2, 1.0/2);
  Movies m(&g);
  vector<Vertex> solution;
  REQUIRE(m.shortestPath(v1) == solution);
  REQUIRE(m.shortestPath(v2) == solution);
  cout << endl;
}

TEST_CASE("shortest path works with triangle", "[weight=1][part=3]") {
  Graph g(true, false);
  Vertex v1("A");
  Vertex v2("B");
  Vertex v3("C");
  g.insertVertex(v3);
  g.insertVertex(v2);
  g.insertVertex(v1);
  g.insertEdge(v1, v2);
  g.insertEdge(v1, v3);
  g.insertEdge(v2, v3);
  g.setEdgeWeight(v1, v2, 1.0/2);
  g.setEdgeWeight(v1, v3, 1.0/3);
  g.setEdgeWeight(v2, v3, 1.0/4);
  Movies m(&g);
  vector<Vertex> solution;
  REQUIRE(m.shortestPath(v1) == solution);
  REQUIRE(m.shortestPath(v2) == solution);
  REQUIRE(m.shortestPath(v3) == solution);
  cout << endl;
}

TEST_CASE("shortest path works with triangle plus one more edge", "[weight=1][part=3]") {
  Graph g(true, false);
  Vertex v1("A");
  Vertex v2("B");
  Vertex v3("C");
  Vertex v4("D");
  g.insertVertex(v4);
  g.insertVertex(v3);
  g.insertVertex(v2);
  g.insertVertex(v1);
  g.insertEdge(v1, v2);
  g.insertEdge(v1, v3);
  g.insertEdge(v2, v3);
  g.insertEdge(v2, v4);
  g.setEdgeWeight(v1, v2, 1.0/2);
  g.setEdgeWeight(v1, v3, 1.0/3);
  g.setEdgeWeight(v2, v3, 1.0/4);
  g.setEdgeWeight(v2, v4, 1.0/5);
  Movies m(&g);
  vector<Vertex> solution_1 = {v1, v2, v4};
  vector<Vertex> solution_2;
  vector<Vertex> solution_3 = {v3, v2, v4};
  vector<Vertex> solution_4 = {v4, v2, v3};
  REQUIRE(m.shortestPath(v1) == solution_1);
  REQUIRE(m.shortestPath(v2) == solution_2);
  REQUIRE(m.shortestPath(v3) == solution_3);
  REQUIRE(m.shortestPath(v4) == solution_4);
  cout << endl;
}

TEST_CASE("shortest path works with triangle plus two more edges", "[weight=1][part=3]") {
  Graph g(true, false);
  Vertex v1("A");
  Vertex v2("B");
  Vertex v3("C");
  Vertex v4("D");
  Vertex v5("E");
  g.insertVertex(v5);
  g.insertVertex(v4);
  g.insertVertex(v3);
  g.insertVertex(v2);
  g.insertVertex(v1);
  g.insertEdge(v1, v2);
  g.insertEdge(v1, v3);
  g.insertEdge(v2, v3);
  g.insertEdge(v2, v4);
  g.insertEdge(v4, v5);
  g.setEdgeWeight(v1, v2, 1.0/2);
  g.setEdgeWeight(v1, v3, 1.0/3);
  g.setEdgeWeight(v2, v3, 1.0/4);
  g.setEdgeWeight(v2, v4, 1.0/5);
  g.setEdgeWeight(v4, v5, 1.0/6);
  Movies m(&g);
  vector<Vertex> solution_1 = {v1, v2, v4};
  vector<Vertex> solution_2 = {v2, v4, v5};
  vector<Vertex> solution_3 = {v3, v2, v4};
  vector<Vertex> solution_4 = {v4, v2, v3};
  vector<Vertex> solution_5 = {v5, v4, v2};
  REQUIRE(m.shortestPath(v1) == solution_1);
  REQUIRE(m.shortestPath(v2) == solution_2);
  REQUIRE(m.shortestPath(v3) == solution_3);
  REQUIRE(m.shortestPath(v4) == solution_4);
  REQUIRE(m.shortestPath(v5) == solution_5);
}

TEST_CASE("shortest path works with complex graph", "[weight=1][part=3]") {
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
  g.insertEdge(v1, v4);
  g.insertEdge(v1, v6);
  g.insertEdge(v2, v3);
  g.insertEdge(v2, v4);
  g.insertEdge(v3, v5);
  g.insertEdge(v3, v8);
  g.insertEdge(v5, v6);
  g.insertEdge(v5, v7);
  g.insertEdge(v5, v8);
  g.insertEdge(v6, v7);
  g.insertEdge(v7, v8);
  g.setEdgeWeight(v1, v2, 10.0);
  g.setEdgeWeight(v1, v4, 3.0);
  g.setEdgeWeight(v1, v6, 7.0);
  g.setEdgeWeight(v2, v3, 7.0);
  g.setEdgeWeight(v2, v4, 5.0);
  g.setEdgeWeight(v3, v5, 6.0);
  g.setEdgeWeight(v3, v8, 4.0);
  g.setEdgeWeight(v5, v6, 5.0);
  g.setEdgeWeight(v5, v7, 2.0);
  g.setEdgeWeight(v5, v8, 3.0);
  g.setEdgeWeight(v6, v7, 4.0);
  g.setEdgeWeight(v7, v8, 5.0);
  Movies m(&g);
  vector<Vertex> solution_1 = {v1, v6, v7};
  vector<Vertex> solution_2 = {v5, v6, v1};
  vector<Vertex> solution_3 = {v3, v5, v7};
  REQUIRE(m.shortestPath(v1) == solution_1);
  REQUIRE(m.shortestPath(v5) == solution_2);
  REQUIRE(m.shortestPath(v3) == solution_3);
}

TEST_CASE("shortest path works with a small dataset", "[weight=1][part=3]") {
  Movies m("tests/Test_Small.csv", "small_out.csv");
  // vector<Vertex> result = m.shortestPath(*(m.getGraph().getVertices().begin()));
  vector<Vertex> result = m.shortestPath(Vertex("tt0003037"));
  m.getGraph().print();
  // cout << "Begin is: " << m.getGraph().getVertices().begin()->get_name() << endl;
  cout << result.size() << endl;
}

TEST_CASE("graph coloring works with 3 vertices", "[weight=1][part=4]") {
  Graph g(true, false);
  Vertex v1("A");
  Vertex v2("B");
  Vertex v3("C");
  g.insertVertex(v3);
  g.insertVertex(v2);
  g.insertVertex(v1);
  g.insertEdge(v1, v2);
  g.insertEdge(v2, v3);
  Movies m(&g);
  int solution = 2;
  REQUIRE(m.greedyColoring() == solution);
}

TEST_CASE("graph coloring works with 10 vertices complex graph", "[weight=1][part=4]") {
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
  g.insertEdge(v1, v3);
  g.insertEdge(v1, v4);
  g.insertEdge(v2, v4);
  g.insertEdge(v2, v5);
  g.insertEdge(v3, v5);
  g.insertEdge(v6, v7);
  g.insertEdge(v7, v8);
  g.insertEdge(v8, v9);
  g.insertEdge(v9, v10);
  g.insertEdge(v10, v6);
  g.insertEdge(v1, v6);
  g.insertEdge(v2, v7);
  g.insertEdge(v3, v8);
  g.insertEdge(v4, v9);
  g.insertEdge(v5, v10);
  Movies m(&g);
  int solution = 3;
  REQUIRE(m.greedyColoring() == solution);
}

TEST_CASE("greedy coloring works with edge file as arg (500 lines)", "[weight=1][part=4]") {
  Movies m("IMDb moviesCSV.csv", "out500.csv", 500, true);
  Movies t("IMDb moviesCSV.csv", "out3000.csv", 3000, true);
  int solution_1 = 20;
  int solution_2 = 43;
  REQUIRE(m.greedyColoring() == solution_1);
  REQUIRE(t.greedyColoring() == solution_2);
}