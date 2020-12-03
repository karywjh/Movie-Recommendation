#include "vertex.h"

bool Vertex::operator==(const Vertex& v) const {
    return id_ == v.id_;
}

bool Vertex::operator!=(const Vertex& v) const {
    return id_ != v.id_;
}

bool Vertex::operator<(const Vertex& v) const
{
    return id_ < v.get_id();
}