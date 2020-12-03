#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;

class Vertex {
    public:
        // Constructors
        Vertex(): id_("invalid_vertex") { /* nothing */ }
        Vertex(string id): id_(id) { /* nothing */ }
        Vertex(string id, string name, string description, string language,
               vector<string> actors, string director, string country, vector<string> genre, int year, double rating, double popularity)
            : id_(id), name_(name), description_(description), language_(language), actors_(actors), director_(director), country_(country), genre_(genre), year_(year), rating_(rating), popularity_(popularity) { /* nothing */ }

        // Getters
        // Below are all information about the movie
        string get_id() const { return id_; }
        string get_name() const { return name_; };
        string get_description() const { return description_; };
        string get_language() const { return language_; };
        vector<string> get_actors() const { return actors_; };
        double get_rating() const { return rating_; };

        // Below features are used to calculate similarity between movies
        string get_actor() const { return actors_[0]; };
        string get_director() const { return director_; };
        string get_country() const { return country_; };
        vector<string> get_genre() const { return genre_; };
        int get_year() const { return year_; };
        double get_popularity() const {return popularity_;}
        
        // Label used in traversals
        string get_label() const {return label_;}
        void set_label(string label) {label_ = label;}

        // Operators
        bool operator==(const Vertex& v) const;
        bool operator!=(const Vertex& v) const;
        
    private:
        string id_;
        string name_;
        string description_;
        string language_;
        double rating_;

        vector<string> actors_;
        string director_;
        string country_;
        vector<string> genre_;
        int year_;
        double popularity_;

        string label_;
};