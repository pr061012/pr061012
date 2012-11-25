#include <set>
#include "../../../../common/Math/DoubleComparison.h"
#include "../../../../common/BasicDefines.h"
#include "Creature.h"

#define __creature_generate_route_complete 1
#define SCALE_FACTOR 2
#define NODE_LIMIT 2500

// Class for vertices with which we will build our graph.
class Vertex
{
public:

    // The actual point.
    Vector point;

    // The vertex that we came from.
    Vector prev_vertex;

    double distance_to_origin;

    // The distance straight to the goal.
    double heuristic_value;

    // The sum of distance_to_origin and heuristic_value
    double value;

    Vertex(Vector point, Vector goal) :
        point(point),
        prev_vertex(point),
        distance_to_origin(0),
        heuristic_value(point.getDistance(goal)),
        value(heuristic_value)
    {
    }

    Vertex(Vector point, const Vertex &origin, Vector goal) :
        point(point),
        prev_vertex(origin.point),
        distance_to_origin(origin.point.getDistance(point) + 
                           origin.distance_to_origin),
        heuristic_value(point.getDistance(goal)),
        value(distance_to_origin + heuristic_value)
    {
    }
};

// NOTE
// The std::set thinks that elements are equal if:
// !(a < b) && !(b < a)
// This check is needed to identify equal elements in set.

// Comparison class for set.
struct VertexComp
{
    bool operator()(const Vertex& a, const Vertex& b) const
    {
        return DoubleComparison::isLess(a.value, b.value);
    }
};

struct VectorComp
{
    bool operator()(const Vertex& a, const Vertex& b) const
    {
        if (a.point == b.point)
            return false;
        // left-bottom to right top
        if (DoubleComparison::areEqual(a.point.getX(), b.point.getX()))
        {
            return DoubleComparison::isLess(a.point.getY(), b.point.getY());
        }
        return DoubleComparison::isLess(a.point.getX(), b.point.getX());
    }
};

const Vector Creature::neighbour_offsets[8] = 
{
    Vector(   0,    1),
    Vector(   1,    1),
    Vector(   1,    0),
    Vector(   1,   -1),
    Vector(   0,   -1),
    Vector(  -1,   -1),
    Vector(  -1,    0),
    Vector(  -1,    1)
};

// TODO
// Make this virual and split it between humanoids and nonhumanoids.
//
// Check whether given point is passable or not, and check if it hits the goal.
int Creature::checkPointIsPassable(Vector point, bool goal_in_sight)
{
    // Check if we can hit the goal.
    if (goal_in_sight && goal -> getShape().hitTest(point))
    {
        return 1;
    }
    // Check if we came to the border of our view_area
    else if (!goal_in_sight && !view_area.hitTest(point))
    {
        return 1;
    }

    // Check if we are out of bounds.
    if (point.getX() < 0 || point.getY() < 0 ||
        point.getX() >= SZ_WORLD_HSIDE ||
        point.getY() >= SZ_WORLD_VSIDE)
    {
        return -1;
    }
    // Place our body on the point
    Shape sample = this -> getShape();
    sample.setCenter(point);

    // Check if it collides with something that we see
    for (ObjectHeap::iterator i = obstacles -> begin();
            i != obstacles -> end(); i++)
    {
        if ((*i) -> getShape().hitTest(sample))
        {
            return -1;
        }
    }
    
    // If nothing bad happened, we can stand on the point
    return 0;

}

// TODO
// Limit the search by constant number of processed nodes.
Creature::Path Creature::generateRoute()
{
    // Default behaviour
    Path result;
    result.push(goal -> getCoords());

    // Debug counter
    uint debug_step = 0;

    // Some creatures can fly
    if (__creature_generate_route_complete && this -> isSolid())
    {
        // Check if our object lies inside view_area
        view_area.setCenter(this -> getCoords());
        Vector goal_point = goal -> getCoords();
        bool goal_in_sight = view_area.hitTest(goal -> getShape());

        // A closed list for vertices already processed.
        // Needed to find path back.
        std::set<Vertex, VectorComp> closed_set;
        // An open list for future vertices ordered by vertex value.
        std::set<Vertex, VertexComp> open_vertex_set;
        // Same list ordered by vertices
        std::set<Vertex, VectorComp> open_vector_set;

        // Form obstacles heap.
        delete obstacles;
        obstacles = new ObjectHeap();
        for (ObjectHeap::iterator i = objects_around.begin();
             i != objects_around.end(); i++)
        {
            if (!(*i) -> isDestroyed() && (*i) -> isSolid() && (*i) != this)
            {
                // Check if we are stuck inside something
                if (this -> getShape().hitTest((*i) -> getShape()))
                {
                    return result;
                }
                obstacles -> push(*i);
            }
        }

        // Iterators
        std::set<Vertex, VertexComp>::iterator vertex_iter;
        std::set<Vertex, VectorComp>::iterator vector_iter;
        Vertex current(this -> getCoords(), goal_point);

        // Add starting vertex to the open_list.
        open_vertex_set.insert(current);
        open_vector_set.insert(current);

        while (!open_vertex_set.empty())
        {
            if (debug_step > NODE_LIMIT)
            {
                aim = nullptr;
                break;
            }
            debug_step++;
            // Get vertex with lowest value = the best one
            vertex_iter = open_vertex_set.begin();
            current = *vertex_iter;

            // Move it to processed list
            open_vertex_set.erase(vertex_iter);
            open_vector_set.erase(current);
            closed_set.insert(current);

            // Look through neighbours
            for (uint i = 0; i < 8; i++)
            {
                Vector next_point =  current.point + 
                        Creature::neighbour_offsets[i] * getShape().getSize() 
                                                        / SCALE_FACTOR;
                int passable = checkPointIsPassable(next_point, goal_in_sight);

                // If we already processed this vertex, skip it.
                Vertex neighbour(next_point, current, goal_point);
                if (closed_set.find(neighbour) != closed_set.end())
                {
                    continue;
                }

                switch (passable)
                {
                    // Can't pass through this point.
                    case -1:
                        // Remember that we can't stand here.
                        closed_set.insert(neighbour);
                        break;
                    
                    // Reached the goal.
                    case 1:
                        // Get the result path
                        while (current.point != this -> getCoords())
                        {
                            result.push(current.point);
                            current.point = current.prev_vertex;
                            current = *(closed_set.find(current));
                        }

                        // Make the loops stop
                        open_vertex_set.clear();
                        i = 100;
                        continue;

                    case 0:
                        // if we already seen this vertex, update it
                        if ((vector_iter = open_vector_set.find(neighbour)) !=
                                 open_vector_set.end())
                        {
                            // if the vertex we have has bigger value, then delete it
                            if ((*vector_iter).value > neighbour.value)
                            {
                                open_vertex_set.erase(*vector_iter);
                                open_vector_set.erase(vector_iter);
                            }
                            else
                            {
                                continue;
                            }
                        }
                        // add the new vertex
                        open_vector_set.insert(neighbour);
                        open_vertex_set.insert(neighbour);
                        break;
                }
            }

        }
        // FIXME
        // Think how to process failures (path not found)

    }
    //std::cout << "Creature:" << getObjectID() << ' ' << "Goal:" << 
    //        goal -> getObjectID() << ' ' << "Nodes:" << debug_step << std::endl;

    return result;
}
