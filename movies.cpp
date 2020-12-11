#include "movies.h"
#include <queue>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>

using std::string;
using std::queue;
using std::cout;
using std::endl;
using std::quoted;
using std::make_heap;
using std::push_heap;
using std::pop_heap;
using std::reverse;

Movies::Movies() : g_(true) {

}

Movies::Movies(const Graph* g) : g_(true) {
    g_ = *g;
}

Movies::Movies(vector<Vertex> vertices, string out_name) : g_(true) {
    std::ofstream outFile(out_name);

    for (Vertex v : vertices) {
        insertMovieConnection(v, outFile, out_name);
    }
}

Movies::Movies(string file, string out_name) : g_(true) {

    std::ifstream inFile(file);
    std::ofstream outFile(out_name);

    if (!inFile.is_open())
        throw std::runtime_error("Could not open file");

    string id, placeholder;
    getline(inFile, placeholder, '\n'); // get rid of first line (title)

    // read every line and insert node
    while (getline(inFile, id, ',')) {
        Vertex v = lineToVertex(inFile, id);
        insertMovieConnection(v, outFile, out_name);
    }
}

Movies::Movies(string file, string out_name, int num) : g_(true) {
    std::ifstream inFile(file);
    std::ofstream myFile(out_name);

    if (!inFile.is_open())
        throw std::runtime_error("Could not open file");

    string id, placeholder;
    getline(inFile, placeholder, '\n'); // get rid of first line (title)

    int i = 0;
    // Limited to num lines of data
    while (i < num && getline(inFile, id, ',')) {
        Vertex v = lineToVertex(inFile, id);
        insertMovieConnection(v, myFile, out_name);
        i++;
    }
}

Movies::Movies(string movies_file, string edge_file, bool read_edge) : g_(true) {
    // First insert every node without connecting
    std::ifstream inFile(movies_file);
    if (!inFile.is_open())
        throw std::runtime_error("Could not open movies file");

    string id, placeholder;
    getline(inFile, placeholder, '\n'); // get rid of first line (title)

    while (getline(inFile, id, ',')) {
        Vertex v = lineToVertex(inFile, id);
        g_.insertVertex(v);
    }
    inFile.close();

    // Then insert edge using pre-generated edge_file
    std::ifstream inFile2(edge_file);
    if (!inFile2.is_open())
        throw std::runtime_error("Could not open edges file");

    string first, second, w_str;
    while (getline(inFile2, first, ',')) {
        getline(inFile2, second, ',');
        getline(inFile2, w_str, '\n');
        g_.insertEdge(Vertex(first), Vertex(second));
        g_.setEdgeWeight(Vertex(first), Vertex(second), std::stod(w_str));
    }
}

Movies::Movies(string movies_file, string edge_file, int num, bool read_edge) : g_(true) {
    // First insert every node
    std::ifstream inFile(movies_file);
    if (!inFile.is_open())
        throw std::runtime_error("Could not open movies file");

    string id, placeholder;
    getline(inFile, placeholder, '\n'); // get rid of first line (title)

    int i = 0;
    while (i < num && getline(inFile, id, ',')) {
        Vertex v = lineToVertex(inFile, id);
        g_.insertVertex(v);
        i++;
    }
    inFile.close();

    // Then insert edge using pre-generated edge_file
    std::ifstream inFile2(edge_file);
    if (!inFile2.is_open())
        throw std::runtime_error("Could not open edges file");

    string first, second, w_str;
    while (getline(inFile2, first, ',')) {
        getline(inFile2, second, ',');
        getline(inFile2, w_str, '\n');
        g_.insertEdge(Vertex(first), Vertex(second));
        g_.setEdgeWeight(Vertex(first), Vertex(second), std::stod(w_str));
    }
}

Vertex Movies::lineToVertex(std::ifstream& inFile, string id) {
    string forquote;
    vector<string> actors, genre;
    string actor, gen;

    string name, language, director, country, description;
    string yearstr, rat, pop;
    int year;
    double rating, popularity;

    getline(inFile, name, ',');

    if (inFile.peek() == '"') {
        getline(inFile, forquote, '"');
        getline(inFile, language, '"');
        getline(inFile, description, ',');
    } else {
        getline(inFile, language, ',');
    }

    getline(inFile, yearstr, ',');
    // cout << id << " " << name << " " << language << " year:" << yearstr << "." << endl;
    year = stoi(yearstr);
    getline(inFile, rat, ',');
    rating = std::stod(rat);
    getline(inFile, pop, ',');
    popularity = std::stod(pop);

    getline(inFile, country, ',');
    getline(inFile, director, ',');

    if (inFile.peek() == '"') {
        getline(inFile, forquote, '"');

        while (actor.back() != '"') {
            getline(inFile, actor, ',');
            actors.push_back(actor);
        }

        actor.pop_back();
        actors.pop_back();
        actors.push_back(actor);
    } else {
        getline(inFile, actor, ',');
        actors.push_back(actor);
    }

    if (inFile.peek() == '"') {
        getline(inFile, forquote, '"');

        while (gen.back() != '"') {
            getline(inFile, gen, ',');
            genre.push_back(gen);
        }

        gen.pop_back();
        genre.pop_back(); 
    } else {
        getline(inFile, gen, ',');
    }

    genre.push_back(gen);

    getline(inFile, description, '\n');
    
    // read data into vertex
    return Vertex(id, name, language, actors, director, country, genre, year, rating, popularity, description);
}

void Movies::insertMovieConnection(Vertex v, std::ofstream& myFile, string out_name) {
    // Connect it with other vertices
    g_.insertVertex(v);
    cout << v.get_id() << " " << v.get_name() << endl;

    myFile.open(out_name, std::ios::out | std::ofstream::app);

    for (Vertex u: g_.getVertices()) {
        if (v != u) {
            double weight = calcWeight(v, u);
            // Connect if similarity >= 40 (weight <= 1/40)
            if (weight <= (1.0 / 40)) {
                g_.insertEdge(v, u);
                g_.setEdgeWeight(v, u, weight);

                // Store edge to file
                string id_v = v.get_id();
                string id_u = u.get_id();
                myFile << v.get_id() << "," << u.get_id() << "," << weight << "\n";
            }
        }
    }
    
    myFile.close();
}

vector<Vertex> Movies::BFS() {
    Graph g = g_;
    vector<Vertex> ids;

    //mark all vertices as unexplored at first
    for(Vertex v: g.getVertices()) {
        map[v] = "UNEXPLORED";
    }

    //mark all edges as unexplored at first
    for(Edge e: g.getEdges()) {
        g.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }

    // call BFS helper on vertices that are unexplored yet
    for(Vertex v: g.getVertices()) {
        if(map[v] == "UNEXPLORED") {
            BFS(&g, v, ids);
        }
    }

    // clear map each time BFS is finished
    map.clear();
    return ids;
}

void Movies::BFS(Graph* G, Vertex v, vector<Vertex>& ids) {
    // mark the current source as visited and push it to queue
    queue<Vertex> q;
    map[v] = "VISITED";
    q.push(v);

    while(!q.empty()) {
        // for each vertex in queue, push it in ids, pop it from queue,
        v = q.front();
        ids.push_back(v);
        q.pop();

        // add all of its neighbors which are not visisted yet to queue
        for(Vertex w: G->getAdjacent(v)) {
            // if the vertex is not visited yet, mark it as visited and push it in queue
            if(map[w] == "UNEXPLORED") {
                G->setEdgeLabel(v, w, "DISCOVERY");
                map[w] = "VISITED";
                q.push(w);
            }
            
            // else if the edge between v, w is unexplored, mark the edge as cross. 
            else if(G->getEdgeLabel(v, w) == "UNEXPLORED") {
                G->setEdgeLabel(v, w, "CROSS");
            }
        }
    }
}

/**
 * Actor:       bool  30
 * Director:    bool  30
 * Country:     bool  10
 * Year:    dif <= 5  10
 * Genre:       bool  10
 * Popularity: dif <= 10 10
 * 
 * Connect Score >= 40 (weight <= 1/40)
 */
double Movies::calcWeight(Vertex u, Vertex v) {
    int total_score = 0;

    if ((u.get_actor() == v.get_actor()))
        total_score += 30;

    if (u.get_director() == v.get_director())
        total_score += 30;

    if ((u.get_country() == v.get_country()))
        total_score += 10;

    if ((abs(u.get_year() - v.get_year()) <= 5))
        total_score += 10;

    if ((abs(u.get_popularity() - v.get_popularity()) <= 10))
        total_score += 10;

    for (string su: u.get_genre()) {
        for (string sv: v.get_genre()) {
            if (su == sv) {
                total_score += 10;
                return 1.0 / double(total_score);
            }
        }
    }

    return 1.0 / double(total_score);
}

unordered_map<Vertex, std::pair<Vertex, double>, MyHash> Movies::shortestPathHelper(Vertex s) {
    // map used to track distance to source
    unordered_map<Vertex, double, MyHash> d;

    // map used to track the predecessor of each vertex. 
    unordered_map<Vertex, Vertex, MyHash> p;

    // lambda function to build min heap. 
    auto compare = [&](Vertex& v1, Vertex& v2) {return d[v1] > d[v2];};

    // mark the distance of all vertices to source as infinite at first, and mark all predecessor to nothing
    for(Vertex v: g_.getVertices()) {
        d[v] = INT_MAX;
        p[v] = Vertex();
    }

    // mark the distance of source to itself as 0
    d[s] = 0;

    // min heap(actually a wrapper of make_heap(), pop_heap(), and push_heap())
    vector<Vertex> Q;

    // push all vertices to the min heap
    for(Vertex v: g_.getVertices()) {
        Q.push_back(v);
        push_heap(Q.begin(),Q.end(), compare);
    }
    
    // reorder the min heap based on the weight(the front is always the vertex with smallest weight)
    make_heap(Q.begin(),Q.end(),compare);

    // use T mark visited
    Graph T(true, false);
    while (!Q.empty()) {
        Vertex u = Q.front();
        pop_heap(Q.begin(), Q.end(), compare);
        Q.pop_back();
        T.insertVertex(u);
        for(Vertex v: g_.getAdjacent(u)) {
            if(T.vertexExists(v))
                continue;
            if((d[u] + g_.getEdge(u, v).getWeight()) < d[v]) {
                d[v] = d[u] + g_.getEdge(u, v).getWeight();
                p[v] = u;
                make_heap(Q.begin(),Q.end(),compare);
            }
        }
    }
    unordered_map<Vertex, std::pair<Vertex, double>, MyHash> result;
    for(Vertex v: g_.getVertices()) {
        std::pair<Vertex, double> pair(p[v], d[v]);
        result[v] = pair;
    }
    return result;
}

vector<Vertex> Movies::shortestPathFilter(unordered_map<Vertex, std::pair<Vertex, double>, MyHash> pairs, Vertex s) {
    vector<Vertex> neighbors = g_.getAdjacent(s);
    Vertex destination;
    double min = INT_MAX;

    // find a vertex that is closet to s among vertices that is not a neighbor of s
    for(auto it = pairs.begin(); it != pairs.end(); it++) {
        if(std::find(neighbors.begin(), neighbors.end(), it->first) != neighbors.end() || it->first == s)
            continue;
        else if(it->second.second < min) {
            min = it->second.second;
            destination = it->first;
        }
    }
    vector<Vertex> recommendations;
    Vertex pre = destination;
    // keep track on predecessor to produce the path
    while(pre != Vertex()) {
        recommendations.push_back(pre);
        pre = pairs[pre].first;
    }
    if(!recommendations.empty()) {
        reverse(std::begin(recommendations), std::end(recommendations));
    }
    else {
        double min = INT_MAX;
        Vertex neighbor;
        for(Vertex w: g_.getAdjacent(s)) {
            if(pairs[w].second < min) {
                min = pairs[w].second;
                neighbor = w;
            }
        }
        recommendations.push_back(neighbor);
        cout << "We cannot find path to vertex " << s.get_id() << ": " << s.get_name() << " that's not directly connected" << endl;
        cout << neighbor.get_id() << " is its closest neighbor" << endl;
    }   
    return recommendations;
}

// Get Shortest Path
vector<Vertex> Movies::getShortestPath(Vertex s) {
    return shortestPathFilter(shortestPathHelper(s), s);
}

// Graph Coloring
int Movies::greedyColoring() {
    vector<Vertex> vertices = g_.getVertices();
    size_t size = vertices.size();
    unordered_map<Vertex, int, MyHash> result;
  
    // Initialize remaining all vertices as unassigned 
    for (Vertex v: vertices) 
        result[v] = -1;  // no color is assigned to v

    // Assign the first color to first vertex 
    result[vertices[0]]  = 0; 
  
    // A temporary array to store the available colors. True 
    // value of available[cr] would mean that the color cr is 
    // assigned to one of its adjacent vertices 
    unordered_map<int, bool> available;
    for (int cr = 0; cr < (int)size; cr++) 
        available[cr] = false; 
  
    // Assign colors to remaining V-1 vertices 
    for (int u = 1; u < (int)size; u++) 
    { 
        // Process all adjacent vertices and flag their colors 
        // as unavailable 
        vector<Vertex> neighbors = g_.getAdjacent(vertices[u]);
        for (auto it = neighbors.begin(); it != neighbors.end(); it++) 
            if (result[*it] != -1) 
                available[result[*it]] = true; 
  
        // Find the first available color 
        int cr; 
        for (cr = 0; cr < (int)size; cr++) 
            if (available[cr] == false) 
                break; 
  
        result[vertices[u]] = cr; // Assign the found color 
  
        // Reset the values back to false for the next iteration 
        for (auto it = neighbors.begin(); it != neighbors.end(); it++) 
            if (result[*it] != -1) 
                available[result[*it]] = false; 
    }
    set<int> colors;
    for(auto it = result.begin();it != result.end(); it++) {
        colors.insert(it->second);
    }
    return colors.size();
}

void Movies::write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<string>>> dataset) {
    std::ofstream myFile(filename);

    for(unsigned j = 0; j < dataset.size(); ++j) {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ",";\
    }
    myFile << "\n";

    for(unsigned i = 0; i < dataset.at(0).second.size(); ++i) {
        for(unsigned j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << ",";
        }
        myFile << "\n";
    }

    myFile.close();
}