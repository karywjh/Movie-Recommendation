# Final Project 
*enxuhan2-jiahuiw4-junbohe2-shunl2*

Made by Enxu Han, Jiahui(Kary) Wang, Junbo He, Shun Li

## Project
Our team uses [IMDb dataset](https://www.kaggle.com/stefanoleone992/imdb-extensive-dataset), designed and implemented a movie recommendation program using graph data structure.

## Algorithms Used
blablabla

## Getting Started

To run our test cases:
```c++
make test
./test
```

To run our main.cpp:
```c++
make final_project

// Below all construct and run algorithms with 3000-vertices dataset
./final_project             // construct graph with 3000 vertices
./final_project coloring    // runs Graph Coloring Algorithm
./final_project BFS         // runs BFS and print out movie names in BFS order

./final_project shortestpath     // runs Graph Coloring Algorithm
./final_project shortestpath id  // runs Graph Coloring Algorithm with user specified id
//example: (replace id with e.g. tt0006206, tt0007047, tt0010418, and etc.)
./final_project shortestpath tt0005060
```

To run our constructor with different args:
```c++
make final_project
./final_project constructor // construct graph with 3000 vertices
./final_project constructor num_vertices // Replace num_vertices with an int to specify how many vertices you want in the graph (run with original csv -- will be slow)

// replace edgefile_name with out500.csv out3000.csv or out10000.csv; replace num_vertices with corresponding int
// Edge connection file is already been made for 500, 3000, and 10000 vertices dataset so runtime will be fast
./final_project constructor edgefile_name num_vertices

 // example:
./final_project constructor out500.csv 500
```

**To get a sense of our algorithm optimization on constructing the graph:**
```c++
make final_project
./final_project 10000 false // Slow: Using original dataset to read in 10000 vertices and making the graph, output the edge connection in output.csv

./final_project 10000 true // Fast: Using premade edge connection file (out10000.csv) to build the graph with 10000 vertices
``` 

