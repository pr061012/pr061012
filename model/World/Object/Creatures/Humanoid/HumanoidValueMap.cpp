/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include <cmath>
#include <cassert>
#include <sstream>

#include "../../../../../common/Math/Random.h"
#include "../../../../../common/Math/DoubleComparison.h"
#include "HumanoidValueMap.h"

#define INFTY           1E+11

HumanoidValueMap::HumanoidValueMap(const ObjectHeap* heap, double v_size,
                                   double h_size, double cell_size) :
    heap(heap),
    cell_size(cell_size),
    map_rows(ceil(v_size / cell_size)),
    map_columns(ceil(h_size / cell_size))
{
    this -> map.resize(this -> map_rows);
    for (uint i = 0; i < this -> map_rows; i++)
    {
        this -> map[i].resize(map_columns);
    }

    uint r = 42;
    if (r > this -> map_rows)    r = this -> map_rows / 3 - 1;
    if (r > this -> map_columns) r = this -> map_columns / 3 - 1;
    this -> record_radius = r;

    this -> reevaluate();
}

void HumanoidValueMap::evaluateObject(const Object* obj)
{
    // Getting coordinates.
    Vector coords = obj -> getCoords();

    // Converting 'em to map's indices.
    uint obj_i = floor(coords.getX() / this -> cell_size);
    uint obj_j = floor(coords.getY() / this -> cell_size);

    // Calculating begin and end i, j.
    int begin_i = obj_i - this -> record_radius - 1;
    int begin_j = obj_j - this -> record_radius - 1;
    int end_i   = obj_i + this -> record_radius + 1;
    int end_j   = obj_j + this -> record_radius + 1;
    begin_i = begin_i < 0 ? 0 : begin_i;
    begin_j = begin_j < 0 ? 0 : begin_j;
    end_i   = end_i   >= this -> map_rows    ? this -> map_rows    : end_i;
    end_j   = end_j   >= this -> map_columns ? this -> map_columns : end_j;

    // Updating cell's values.
    for (uint i = begin_i; i < end_i; i++)
    {
        for (uint j = begin_j; j < end_j; j++)
        {
            // Calculating distance.
            int delta_i = (int) i - (int) obj_i;
            int delta_j = (int) j - (int) obj_j;
            uint distance = ceil(sqrt(delta_i * delta_i + delta_j * delta_j));

            // If this point is in record radius from object, increase counter.
            if (distance <= this -> record_radius)
            {
                if (distance != 0)
                {
                    this -> map[i][j] += (double) 1 / distance;
                    double value = this -> map[i][j];

                    // New maximum.
                    if (DoubleComparison::isGreater(value, this -> max))
                    {
                        this -> max = value;

                        this -> max_i.clear();
                        this -> max_i.push_back(i);

                        this -> max_j.clear();
                        this -> max_j.push_back(j);
                    }
                    // Found cell, which is equal to current maximum.
                    else if (DoubleComparison::areEqual(value, max))
                    {
                        this -> max_i.push_back(i);
                        this -> max_j.push_back(j);
                    }
                }
                else
                {
                    // Cell with this object in. Setting cell's value to
                    // infinity.
                    this -> map[i][j] = INFTY;
                }
            }
        }
    }
}

void HumanoidValueMap::reevaluate()
{
    // Clearing map.
    for (uint i = 0; i < this -> map_rows; i++)
    {
        for (uint j = 0; j < this -> map_columns; j++)
        {
            this -> map[i][j] = 0;
        }
    }

    // TODO: Evaluating only resources. Is it a good idea?
    ObjectHeap::const_iterator iter;
    ObjectHeap::const_iterator begin = this -> heap -> begin(RESOURCE);
    ObjectHeap::const_iterator end   = this -> heap -> end(RESOURCE);

    for (iter = begin; iter != end; iter++)
    {
        const Object* obj = *iter;

        // Evaluating only immovable objects (evaluation for movable objects is
        // strange).
        if (!obj -> isMovable())
        {
            this -> evaluateObject(obj);
        }
    }
}

Vector HumanoidValueMap::getBestPlace() const
{
    if (max_i.size() == 0)
    {
        return Vector(-1, -1);
    }

    uint id = Random::int_num(max_i.size());
    return Vector(this -> cell_size * max_i[id], this -> cell_size * max_j[id]);
}

std::string HumanoidValueMap::print() const
{
    std::stringstream ss;

    for (uint i = 0; i < this -> map_rows; i++)
    {
        for (uint j = 0; j < this -> map_columns; j++)
        {
            ss << this -> map[i][j] << "\t";
        }
        ss << std::endl;
    }

    return ss.str();
}
