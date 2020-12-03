#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;

class Vertex {
    public:
        // Constructors
        Vertex(): id_("invalid_vertex") { /* nothing */ }
        Vertex(string id, string name, string description, string language,
               string actor, string director, string country, vector<string> genre, int year, double rating)
            : id_(id), name_(name), description_(description), language_(language), actor_(actor), director_(director), country_(country), genre_(genre), year_(year), rating_(rating) { /* nothing */ }

        // Getters
        string get_id() const { return id_; }
        string get_name() const { return name_; };
        string get_description() const { return description_; };
        string get_language() const { return language_; };

        string get_actor() const { return actor_; };
        string get_director() const { return director_; };
        string get_country() const { return country_; };
        vector<string> get_genre() const { return genre_; };
        int get_year() const { return year_; };
        double get_rating() const { return rating_; };
        double get_popularity() const {return popularity_;}
        string get_label() const {return label_;}

        void set_label(string label) {label_ = label;}

        // Operators
        bool operator==(Vertex v) const;
        bool operator!=(Vertex v) const;
        
    private:
        string id_;
        string name_;
        string description_;
        string language_;

        string actor_;
        string director_;
        string country_;
        vector<string> genre_;
        int year_;
        double rating_;
        double popularity_;
        string label_;
};