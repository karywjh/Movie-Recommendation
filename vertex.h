#pragma once

#include <string>
using std::string;

class Vertex {
    public:
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