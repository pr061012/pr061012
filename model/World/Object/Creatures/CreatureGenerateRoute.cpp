#include <set>
#include "Creature.h"

#define __creature_generate_route_complete 0

struct Vertex
{
    // The actual point.
    Vector point;

    // The vertex that we came from.
    Vertex * prev_vertex;

    double distance_to_origin;

    // The distance straight to the goal.
    double heuristic_value;
};

// Comparison class for set.
struct VertexComp
{
    bool operator()(const Vertex * a, const Vertex * b) const
    {
        // The std::set thinks that elements are equal if:
        // !(a < b) && !(b < a)
        // This check is needed to replace duplicate elements
        if (a -> point == b -> point)
        {
            return false;
        }

        return a -> distance_to_origin + a -> heuristic_value <
               b -> distance_to_origin + b -> heuristic_value;
    }
};

// TODO
// Implement A* for humanoid
Creature::Path Creature::generateRoute(Object * goal)
{
    if (__creature_generate_route_complete)
    {
        // A closed list for vertices already processed
        std::set<Vertex*, VertexComp> closed_list;
        // An open list for future vertices
        std::set<Vertex*, VertexComp> open_list;
        //
    }
    else
    {
        Path result;
        result.push(goal -> getCoords());
        return result;
    }
}
