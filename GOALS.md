## Dataset:

[https://openflights.org/data.html](https://openflights.org/data.html)

We are using the dataset from openflights, with nodes representing airports, and edges representing flight routes. Data files include airports.dat, routes.dat and so on.

## Goal:

We are interested in finding the shortest path between cities. To implement this, we will use weight as the distance of the flight route between two airports.

## Algorithms:

1. Traversal: DFS
2. Use Dijkstra&#39;s Algorithm to find the shortest path between two airports
3. Use Landmark Path to find the shortest path through another airport (if traveler wants to travel to several places in between of starting city and destination)