/**
 * @file edge.h
 * Definition and (minimal) implementation of an edge class.
 */

#pragma once

#include <string>
#include <limits.h>
#include "vertex.h"

using std::string;

/**
 * Represents an edge in a graph; used by the Graph class.
 *
 * @author Sean Massung
 * @date Spring 2012
 */
class Edge
{
  public:
    Vertex source; /**< The source of the edge **/
    Vertex dest; /**< The destination of the edge **/

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     */
    Edge(Vertex u, Vertex v)
        : source(u), dest(v), label(""), weight(calcWeight(u, v))
    { /* nothing */
    }

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param lbl - the edge label
     */
    Edge(Vertex u, Vertex v, string lbl)
        : source(u), dest(v), label(lbl), weight(calcWeight(u, v))
    { /* nothing */
    }

    /**
     * Parameter constructor for weighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param w - the weight of the edge
     * @param lbl - the edge label
     */
    Edge(Vertex u, Vertex v, int w, string lbl)
        : source(u), dest(v), label(lbl), weight(w)
    { /* nothing */
    }

    /**
     * Default constructor.
     */
    Edge() : source(), dest(), label(""), weight(-1)
    { /* nothing */
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
    double calcWeight(Vertex u, Vertex v) {
        int total_score;

        if ((u.get_id() == v.get_id()))
            total_score += 30;

        if (u.get_director() == v.get_director())
            total_score += 30;

        if ((u.get_country() == v.get_country()))
            total_score += 10;

        if ((abs(u.get_year() - v.get_year()) <= 5))
            total_score += 10;
        
        if ((u.get_genre() == v.get_genre()))
            total_score += 10;

        if ((abs(u.get_rating() - v.get_rating()) <= 2))
            total_score += 10;
        
        return 1 / double(total_score);
    }

    /**
     * Compares two Edges.
     * operator< is defined so Edges can be sorted with std::sort.
     * @param other - the edge to compare with
     * @return whether the current edge is less than the parameter
     */
    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }

    /**
     * Gets edge label.
     */
    string getLabel() const
    {
        return this->label;
    }

    /**
     * Gets edge weight.
     */
    int getWeight() const
    {
        return this->weight;
    }

    /**
     * Compares two edges' source and dest.
     * @param other - the edge to compare with
     */
    bool operator==(Edge& other) const
    {
        return this->source == other.source && this->dest == other.dest;
    }
private:
    string label; /**< The edge label **/
    int weight; /**< The edge weight (if in a weighed graph) **/

};
