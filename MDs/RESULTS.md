# Final Report
Made by Enxu Han, Jiahui(Kary) Wang, Junbo He, Shun Li

(*enxuhan2-jiahuiw4-junbohe2-shunl2*)

## Outcome

### Dataset
We've used [IMDb dataset](https://www.kaggle.com/stefanoleone992/imdb-extensive-dataset) to construct the graph. At the very beginning, we deleted invalid movies (rows with blank elements, with multiple directors, and etc.) and deleted some unuseful features. 

### Constructor
When constructing the graph, we implemented two ways. **First** way is to read the original dataset that doesn't have any connection information about vertices. Every time a vertex is being added, we calculate the similarity of it to every other existing vertices. We connect them if similarity >= 40%. As we are connecting vertices, we write the edge connection and weight to an output file. **Second** way is to read from our generated edge-connection file and connect the vertices. Therefore after executing one time with the dataset, we can achieve a much faster execution time when running the second time with the same dataset.

### Algorithms
We choose to implement BFS traversal; Dijkstra's Algorithm(shortest path); and graph-coloring. When firstly implementing BFS, we find that our BFS traversal was unable to visit vertices that are disconnected from the graph. So we fix our BFS traversal follwing the lecture, which is to call the BFS helper function to all unexplored vertices. As for the Dijkstra's algorithm, our original goal is to return a path whose source is the passed in argument and whose destination is the closet vertex to the source among vertices that are not neighbors of source. However, for several vertices there is no path returned. We finally realized that those vertices exist in a complete graph. Thus, we seperate our shortest path function to 3 functions: the first funciton(shortestPathHelper(Vertex s)) takes in the source vertex and returns an unordered map(Vertex as key, pair<Vertex, double>) which used to represent the predecessor and distance to source vertex; the second function(shortestPathFilter(unordered_map<Vertex, std::pair<Vertex, double>, MyHash>, Vertex)) takes in an unordered map and the source vertex and returns a vector<Vertex> which is used to filter those source vertices that will cause this function to return an empty path; the last function(getShortestPath(Vertex s)) simply merge the previous 2 functions together and return the final path. For our graph-coloring reports how many colors would be used for our graph to show the complexity of our graph. 

<br/>

## Discoveries

### Constructor Optimization
We've reached a much faster execution time using the second constructor method:
1. 3000 lines from original movies file takes: 67.144s
2. 3000 lines from edge-connection file takes: 2.225s
3. 10000 lines from original movies file takes:  586.342s
4. 10000 lines from edge-connection file takes: 1.287s

As one can see from the data, the second time running constructing the same dataset would use only 0.22% - 3.3% of the first execution time, which is really a big improvement. This is because the first time, it needs to go over every other vertices when adding a vertex, but if we have the edge connection the first time, the second time we can directly insert the edges and connect the graph without worrying about calculating weight another time.