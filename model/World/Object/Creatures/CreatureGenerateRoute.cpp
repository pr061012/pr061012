#include <set>
#include "Creature.h"

#define __creature_generate_route_complete 0

// Class for vertices with which we will build our graph.
class Vertex
{
public:

    // The actual point.
    Vector point;

    // The vertex that we came from.
    Vertex * prev_vertex;

    double distance_to_origin;

    // The distance straight to the goal.
    double heuristic_value;

    Vertex(Vector point, Vertex * origin, Vector goal) :
        point(point),
        prev_vertex(origin),
        heuristic_value(point.getDistance(goal))
    {
        if (origin)
        {
            distance_to_origin = origin -> point.getDistance(point) + 
                           origin -> distance_to_origin;
        }
        else
        {
            distance_to_origin = 0;
        }
    }
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

typedef std::set<Vertex*, VertexComp> VSet;

const Vector Creature::neighbour_offsets[8] = 
{
};

// TODO
// Make this virual and split it between humanoids and nonhumanoids.
//
// Check whether given point is passable or not, and check if it hits the goal.
int Creature::checkPointIsPassable(Vector point)
{
    // Place our body on the point
    Shape sample = this -> getShape();
    sample.setCenter(point);
    
    // Check if we can hit the goal.
    if (sample.hitTest(goal -> getShape()))
    {
        return 1;
    }

    // Check if it collides with something that we see
    for (ObjectHeap::iterator i = objects_around.begin();
            i != objects_around.end(); i++)
    {
        if ((*i) -> isSolid() && *i != this)
        {
            if ((*i) -> getShape().hitTest(sample))
            {
                return -1;
            }
        }
    }
    
    // If nothing bad happened, we can stang on the point
    return 0;

}

// TODO
// Implement A*
Creature::Path Creature::generateRoute()
{
    // Some creatures can fly
    if (__creature_generate_route_complete && this -> isSolid())
    {
        Vector goalPoint = goal -> getCoords();
        // A closed list for vertices already processed.
        // Needed to find path back.
        VSet closed_set;
        // An open list for future vertices.
        VSet open_set;
        // Iterators
        VSet::iterator i;
        Vertex* current;

        // Add starting vertex to the open_list.
        open_set.insert(new Vertex(this -> getCoords(), 0, goalPoint));
        while (!open_set.empty())
        {
            // Get vertex with lowest value = the best one
            i = open_set.begin();
            current = *i;
            // Move it to processed list
            open_set.erase(i);
            closed_set.insert(current);
            

        }
        // FIXME
        // Think how to process failures (path not found)
    }
    
    // Default behaviour
    Path result;
    result.push(goal -> getCoords());
    return result;
}
