#include <set>
#include "Creatures.h"

#define __creatures_generate_route_complete 0

struct Vertex
{
    Vector point;
    Vertex * prev_vertex;
    double distance_to_origin;
    double distance_to_goal;
    double value;
}

bool comp(Vertex * a, Vertex * b)
{
    return a -> value < b -> value;
}

// TODO
// Implement A* for humanoid
Creature::Path Creature::generateRoute(Object * goal)
{
    if (__creature_generate_route_complete)
    {
        // Create
        std::set<Vertex*, comp> 
    }
    else
    {
        Path result;
        result.push(goal -> getCoords());
        return result;
    }
}
