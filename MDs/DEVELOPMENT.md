# Development

## Week 1 (Nov 15 - 21)

<br />

### What We Have Done

Research and brainstormed ideas and discussed about how different algorithms can be used in each ideas. 

<br />

### Details
---

On our first meeting (Nov 16), we brainstormed and listed topics we can do for this project that we are interested in. We came up with ideas related to Covid-19, the 2020 Presidential election, and openflight. We decided to each investigate on how they can incorporate with the graph data structure.

On Nov 17, we meet to discuss what we've found. We talked about how graph structure are usually used in real life, for example, in route mapping and social networking. We've also discussed about how algorithms like Dijkstra’s Algorithm and Prim's Algorithm can be used in our proposed topics. We gave up on ideas like Covid and election, and decided that Openflight and social media ideas are the most suitable. 

On Nov 18, we explored more options, for example, finding safest path (avoid crime) around campus or Chicago and on Stanford's SNAP website. However, most of the SNAP datasets have little information or features about the vertices. Thus, we finalized on doing Openflight as our backup plan. We've also completed our project goals and team contract files.

<br />

## Week 2 (Nov 22 - 28)
<br />

### What We Have Done

We've came up with new ideas and discussed about their feasibility. We found [Facebook Large Page-Page Network Dataset](http://snap.stanford.edu/data/facebook-large-page-page-network.html) to be comprehensive: it includes link name and category for each vertex. We also found another idea [Movie Recommender System](https://www.kaggle.com/rounakbanik/movie-recommender-systems) interesting to do, so we cleaned up the data and tried to find a useful weight for this idea.

We finalized on doing the movie recommender idea, and started modifying the graph, edge, and vertex classes from lab_ml to better fit our data.

<br />

### Details (Meeting Notes)
---

**Nov 23, 2020**

Found that the idea of representing planets and satellites in a graph data structure is not feasible since it's more like a tree structure (distance between planets are constantly changing).

<br />

**Nov 25, 2020**

Proposed idea of Movie Recommender System. Vertices as movies, and edges connecting movies with high similarities. Similarity (the weight or 1/weight) will be calculated by genre, director, actor, and etc. 

<br />

**Nov 26, 2020**

Listed out Tasks:

- Dataset:

    - Get rid of unuseful categories in the dataset. 
    - Actors: Only leave three main actors in the dataset (the first three in the list)
    - Solve the problem of unidetified characters. (open with excel)

- Graph

    - Plan out when will two vertexs be connected.
    - Determine what the weight would be.
    - What each algorithms can do under these circumstances. 


## Week 3 (Nov 29 - Dec 5)
<br />

### What We Have Done

Completed making graph, edge, and vertex class. Filtered out unuseful datas in the dataset, such as rows that contains blank features, those that has mutiple directors, deleted columns like rate counts and etc. Wrote Makefile, test files, and main.cpp and made it work. Created class movies, which contains the constructor of reading the csv datas into vertices and constructing a graph.


<br />

### Details (Meeting Notes)
---

**Dec 5, 2020**

Mid-project check-in meeting. TODO before final submission:

- Provide a smaller dataset to submit/test.
- Add commands needed to run in Readme.
- Come up with questions that can use BFS.

<br/>

## Week 4 (Dec 6 - 11)
<br />

### What We Have Done

Made write edge connections to output file while adding edges worked. Written constructor that can create graph using edge connection file.

Made main.cpp, that user can pass in different arguments to run different algorithms.

<br />

### Details (Meeting Notes)
---

**Dec 10, 2020**

Discussed how algorithms can be implemented and improved. Tested and fixed issues with constructors and algorithms.
