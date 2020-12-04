#include "movies.h"
#include <queue>
#include <iostream>
#include <sstream>

using std::string;
using std::queue;
using std::cout;
using std::endl;
using std::quoted;

Movies::Movies() : g_(true) {

}

Movies::Movies(vector<Vertex> vertices) : g_(true) {
    for (Vertex v : vertices) {
        insertMovieConnection(v);
    }
}

Movies::Movies(string file) : g_(true) {

    // read every line and insert node
    string forquote;
    vector<string> actors, genre;
    string actor, gen;

    string id, name, language, director, country, description;
    string yearstr, rat, pop;
    int year;
    double rating, popularity;

    std::ifstream inFile(file);

    if (!inFile.is_open())
        throw std::runtime_error("Could not open file");

    string line, c;
    int nline = 0;

    getline(inFile, description, '\n'); // get rid of first line (title)
    int i = 0;

    // Limited to 100 data, TBC
    while (i <= 100 && getline(inFile, id, ',')) {
        actors.clear();
        genre.clear();
        getline(inFile, name, ',');
        getline(inFile, language, ',');

        getline(inFile, yearstr, ',');
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
        Vertex v(id, name, language, actors, director, country, genre, year, rating, popularity, description);
        insertMovieConnection(v);

        i++;
    }
}

void Movies::insertMovieConnection(Vertex v) {
    // Connect it with other vertices
    g_.insertVertex(v);

    for (Vertex u: g_.getVertices()) {
        if (v != u) {
            double weight = calcWeight(v, u);
            // Connect if similarity >= 30 (weight <= 1/30)
            if (weight <= (1.0 / 30)) {
                g_.insertEdge(v, u);
                g_.setEdgeWeight(v, u, weight);

                // Store edge to file
                string id_v = v.get_id();
                string id_u = u.get_id();
                a.push_back(id_v);
                b.push_back(id_u);
            }
        }
    }
}
void Movies::write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<string>>> dataset){
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

void Movies::BFS(Graph G) {
    for(Vertex v: G.getVertices()) {
        v.set_label("UNEXPLORED");
    }
    for(Edge e: G.getEdges()) {
        e.setLabel("UNEXPLORED");
    }
    for(Vertex v: G.getVertices()) {
        if(v.get_label() == "UNEXPLORED") {
            BFS(G, v);
        }
    }
}

void Movies::BFS(Graph G, Vertex v) {
    queue<Vertex> q;
    v.set_label("VISITED");
    q.push(v);

    while(!q.empty()) {
        v = q.back();
        cout << "name: " << v.get_name() << " Description: " << v.get_description() << endl;
        q.pop();
        for(Vertex w: G.getAdjacent(v)) {
            if(w.get_label() == "UNEXPLORED") {
                G.setEdgeLabel(v, w, "DISCOVERY");
                w.set_label("VISITED");
                q.push(w);
            }
            else if(G.getEdge(v, w).getLabel() == "UNEXPLORED") {
                G.setEdgeLabel(v, w, "CROSS");
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
 * Avg_vote: dif <= 2 10
 * 
 * Connect Score >= 30 (weight <= 1/30)
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
