#include "vertex.h"

bool Vertex::operator==(Vertex v) const {
    return id_ == v.id_;
}

bool Vertex::operator!=(Vertex v) const {
    return id_ != v.id_;
}