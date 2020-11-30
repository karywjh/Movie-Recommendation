#pragma once

#include <string>
using std::string;

class Vertex {
    public:
        // Constructors
        Vertex(): name_("invalid_vertex") { /* nothing */ }
        Vertex(string id, string name, string description, string language,
               string actor, string director, string country, string genre, int year, double rating)
            : id_(id), name_(name), description_(description), language_(language), actor_(actor), director_(director), country_(country), genre_(genre), year_(year), rating_(rating) { /* nothing */ }

        // Getters
        string get_id() const { return id_; }
        string get_name() const { return name_; };
        string get_description() const { return description_; };
        string get_language() const { return language_; };

        string get_actor() const { return actor_; };
        string get_director() const { return director_; };
        string get_country() const { return country_; };
        string get_genre() const { return genre_; };
        int get_year() const { return year_; };
        double get_rating() const { return rating_; };

        // Setters
        void set_id(string id) { id_ = id; }
        void set_name(string name) { name_ = name; };
        void set_description(string description) { description_ = description; };
        void set_language(string language) { language_ = language; };

        void set_actor(string actor) { actor_ = actor; };
        void set_director(string director) { director_ = director; };
        void set_country(string country) { country_ = country; };
        void set_genre(string genre) { genre_ = genre; };
        int set_year(int year) { year_ = year; };
        double set_rating(double rating) { rating = rating_; };

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
        string genre_;
        int year_;
        double rating_;
};