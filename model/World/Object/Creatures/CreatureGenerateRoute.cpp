#include <set>
#include "../../../../common/Math/DoubleComparison.h"
#include "../../../../common/BasicDefines.h"
#include "Creature.h"

#define __creature_generate_route_complete 1
#define SCALE_FACTOR 3
#define NODE_LIMIT 100000

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

    // The index of direction
    uint direction;

    Vertex(Vector point, Vector goal, uint direction) :
        point(point),
        prev_vertex(point),
        distance_to_origin(0),
        heuristic_value(point.getDistance(goal)),
        value(heuristic_value),
        direction(direction)
    {
    }

    Vertex(Vector point, const Vertex &origin, Vector goal, uint direction) :
        point(point),
        prev_vertex(origin.point),
        distance_to_origin(origin.point.getDistance(point) + 
                           origin.distance_to_origin),
        heuristic_value(point.getDistance(goal)),
        value(distance_to_origin + heuristic_value),
        direction(direction)
    {
    }
};

//**********************************************************
// NOTE
// The std::set thinks that elements are equal if:
// !(a < b) && !(b < a)
// This check is needed to identify equal elements in set.
//**********************************************************
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

//**********************************************************
// CONSTANTS
//**********************************************************

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

const double Creature::MAX_OFFSET = 3;

//**********************************************************
// METHODS
//**********************************************************

// TODO
// Make this virual and split it between humanoids and nonhumanoids.
//
// Check whether given point is passable or not, and check if it hits the goal.
int Creature::checkPointIsPassable(Vector point, bool goal_in_sight)
{
    Shape ghost = getShape();
    ghost.setCenter(point);
    // Check if we can hit the goal.
    if (goal_in_sight && ghost.hitTest(aim -> getShape()))
    {
        return 1;
    }
    // Check if we came to the border of our view_area
    if (!view_area.hitTest(point))
    {
        // if goal outside our sight, then we better come out of our
        // view_area to the nearest point to the aim
        if (!goal_in_sight)
        {
            return 1;
        }
        // otherwise the way to the goal must be inside our view
        else
        {
            return -1;
        }
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
    if ((obstacles_index -> getAreaContents(sample)).getAmount())
    {
        return -1;
    }

    // If nothing bad happened, we can stand on the point
    return 0;

}

// TODO
// Make straightening of the route.
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
        if (!goal_in_sight)
        {
            route.pop();
        }

        // A closed list for vertices already processed.
        // Needed to find path back.
        std::set<Vertex, VectorComp> closed_set;
        // An open list for future vertices ordered by vertex value.
        std::set<Vertex, VertexComp> open_vertex_set;
        // Same list ordered by vertices
        std::set<Vertex, VectorComp> open_vector_set;

        // Form index.
        delete obstacles_index;
        obstacles_index = new Indexator(view_area.getSize(), 0,
                this -> getCoords() - Vector(1, 1) * (view_area.getSize() / 2),
                Indexator::MIN_CELL_SIZE);

        for (ObjectHeap::iterator i = objects_around.begin();
             i != objects_around.end(); i++)
        {
            // FIXME Make better check for dangers.
            if (!(*i) -> isDestroyed() && 
                ((*i) -> isSolid() || (*i) -> getType() == WEATHER) &&
                (*i) != this)
            {
                // Check if we are stuck inside something
                if (this -> getShape().hitTest((*i) -> getShape()))
                {
                    return result;
                }
                obstacles_index -> addObject(*i);
            }
        }

        // Iterators
        std::set<Vertex, VertexComp>::iterator vertex_iter;
        std::set<Vertex, VectorComp>::iterator vector_iter;
        Vertex current(this -> getCoords(), goal_point, 100);

        // Add starting vertex to the open_list.
        open_vertex_set.insert(current);
        open_vector_set.insert(current);

        // Direction buffer
        uint direction;

        while (!open_vertex_set.empty())
        {
            if (debug_step > NODE_LIMIT)
            {
                //aim = nullptr;
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
                    Creature::neighbour_offsets[i] * CREAT_SPEED_SLOW_VALUE *
                    SCALE_FACTOR;
                int passable = checkPointIsPassable(next_point, goal_in_sight);

                // If we already processed this vertex, skip it.
                Vertex neighbour(next_point, current, goal_point, i);
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
                        direction = 100;
                        // Get the result path
                        while (current.point != this -> getCoords())
                        {
                            // Put only turning points
                            if (current.direction != direction)
                            {
                                result.push(current.point);
                                current.point = current.prev_vertex;
                                current = *(closed_set.find(current));
                            }
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
    std::cout << "Creature:" << getObjectID() << ' ' << "Goal:" << 
            goal -> getObjectID() << ' ' << "Nodes:" << debug_step << std::endl;

    return result;
}
