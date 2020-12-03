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
        : source(u), dest(v), label(""), weight(-1)
    { /* nothing */
    }

    Edge(Vertex u, Vertex v, int w)
        : source(u), dest(v), label(""), weight(w)
    { /* nothing */
    }

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param lbl - the edge label
     */
    Edge(Vertex u, Vertex v, string lbl)
        : source(u), dest(v), label(lbl), weight(-1)
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

    void setLabel(string label_) {
        label = label_;
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
