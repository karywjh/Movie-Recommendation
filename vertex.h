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
        Vertex(string id, string name, string language,
               vector<string> actors, string director, string country, vector<string> genre, int year, double rating, double popularity, string description)
            : id_(id), name_(name), language_(language), actors_(actors), director_(director), country_(country), genre_(genre), year_(year), rating_(rating), popularity_(popularity), description_(description) { /* nothing */ }

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
        bool operator==(const Vertex& v) const { return id_ == v.id_; }
        bool operator!=(const Vertex& v) const { return id_ != v.id_; }
        
        /**
         * operator< is defined so Vertex can be used in Set.
         */
        bool operator<(const Vertex& v) const { return id_ < v.get_id(); }

    private:
        string id_;
        string name_;
        
        string language_;

        vector<string> actors_;
        string director_;
        string country_;
        vector<string> genre_;
        int year_;
        double rating_;
        double popularity_;
        string description_;

        string label_;
};