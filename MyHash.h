#include <string>
#include "vertex.h"

using std::size_t;
using std::hash;
using std::string;

class MyHash { 
    public: 
        size_t operator()(const Vertex& v) const
        { 
            return (hash<string>()(v.get_id())) ^  
                (hash<string>()(v.get_name()));
        } 
}; 