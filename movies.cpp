#include "movies.h"
#include <queue>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

using std::string;
using std::queue;
using std::cout;
using std::endl;
using std::quoted;
using std::make_heap;
using std::push_heap;
using std::pop_heap;

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
    // First insert every node
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

    // Then insert edge using edge_file
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

    // Then insert edge using edge_file
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
    // cout << v.get_id() << " " << v.get_name() << endl;

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

vector<string> Movies::BFS() {
    Graph g = g_;
    vector<string> ids;
    for(Vertex v: g.getVertices()) {
        map[v] = "UNEXPLORED";
    }
    for(Edge e: g.getEdges()) {
        g.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }
    for(Vertex v: g.getVertices()) {
        if(map[v] == "UNEXPLORED") {
            BFS(&g, v, ids);
        }
    }
    map.clear();
    return ids;
}

void Movies::BFS(Graph* G, Vertex v, vector<string>& ids) {
    queue<Vertex> q;
    map[v] = "VISITED";
    q.push(v);

    while(!q.empty()) {
        v = q.front();
        ids.push_back(v.get_id());
        q.pop();
        for(Vertex w: G->getAdjacent(v)) {
            if(map[w] == "UNEXPLORED") {
                G->setEdgeLabel(v, w, "DISCOVERY");
                map[w] = "VISITED";
                q.push(w);
            }
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

vector<Vertex> Movies::shortestPath(Vertex s) {
    unordered_map<Vertex, double, MyHash> d;
    unordered_map<Vertex, Vertex, MyHash> p;
    auto compare = [&](Vertex& v1, Vertex& v2) {return d[v1] > d[v2];};
    for(Vertex v: g_.getVertices()) {
        d[v] = INT_MAX;
        p[v] = Vertex();
    }
    d[s] = 0;
    vector<Vertex> Q;
    for(Vertex v: g_.getVertices()) {
        Q.push_back(v);
        push_heap(Q.begin(),Q.end(), compare);
    }
    make_heap(Q.begin(),Q.end(),compare);
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
    vector<Vertex> neighbors = g_.getAdjacent(s);
    Vertex destination;
    double min = INT_MAX;
    for(auto it = d.begin(); it != d.end(); it++) {
        if(std::find(neighbors.begin(), neighbors.end(), it->first) != neighbors.end() || it->first == s)
            continue;
        if(it->second < min) {
            min = it->second;
            destination = it->first;
        }
    }
    vector<Vertex> recommendations;
    Vertex pre = p[destination];
    while(pre != Vertex() && pre != s) {
        recommendations.push_back(pre);
        pre = p[pre];
    } 
    return recommendations;
}