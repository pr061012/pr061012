/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#include "HumanoidValueMap.h"

#include <cmath>
#include <cassert>

// FIXME: Silly.
#define SIZE                1000
/// Cell size.
#define CELL_SIZE           0.1

HumanoidValueMap::HumanoidValueMap(ObjectHeap* heap) :
    heap(heap),
    map_rows(ceil(SIZE / CELL_SIZE)),
    map_columns(ceil(SIZE / CELL_SIZE))
{
    this -> map.resize(this -> map_rows);
    for (uint i = 0; i < this -> map_rows; i++)
    {
        this -> map[i].resize(map_columns);
    }

    this -> reevaluate();
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
        Object* obj = *iter;

        // Evaluating only immovable objects (evaluation for movable objects is
        // strange).
        if (!obj -> isMovable())
        {
            // Getting coordinates.
            Vector coords = obj -> getCoords();

            // Converting 'em to map's indices.
            uint i = floor(coords.getX() / CELL_SIZE);
            uint j = floor(coords.getY() / CELL_SIZE);

            // Increasing value of this cell.
            // FIXME: Rewrite.
            this -> map[i][j] += 1;
        }
    }
}

Vector HumanoidValueMap::getBestPlace()
{
}
