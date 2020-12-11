## Dataset:

[https://www.kaggle.com/stefanoleone992/imdb-extensive-dataset](https://www.kaggle.com/stefanoleone992/imdb-extensive-dataset)

We are using the dataset of IMDb on kaggle. The dataset includes 85,855 movies with attributes such as movie description, average rating, number of votes, genre, etc.

## Goal:

We will build a movie search and recommendation engine where users can search a specific movie through actors, directors, year, and other tags. Each Vertex represent a specific movie which will be built with 'structure' in C++ and contains tags such as rating scores; directors; actors; country and so on. Each edge which represent the similarity between 2 movies will be weighted and undirected. The similary will be calculated is calculated through weight mean. 2 vertices will be connected only if the weight mean reached 30. 

## Traversal: 
We will use BFS. We have almost 100,000 movies, DFS will be much slower. 

## Algorithms:

1. Use Dijkstra&#39;s Algorithm to find the shortest path between 2 vertices which are movies similar to the source and destination vertices. Make sure the shortest path is not the edge between source and the destination.
2. Use graph coloring to analyze the graph. Neighbors will have different colors, so number of colors identify number of categories in the graph.