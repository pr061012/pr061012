/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef HUMANOID_VALUE_MAP_H
#define HUMANOID_VALUE_MAP_H

#include "../../../../Utilities/Vector/Vector.h"
#include "../../../ObjectHeap/ObjectHeap.h"

/**
 * @brief Contains humanoid's map with cells' values. Is used for best home
 *        place choosing.
 */
class HumanoidValueMap
{
public:
    /**
     * @brief Constructor.
     * @param v_size    world's vertical size
     * @param h_size    world's horizontal size
     * @param heap      heap with objects
     */
    HumanoidValueMap(double v_size, double h_size, ObjectHeap* heap);

    /**
     * @brief Reevaluates map.
     */
    void reevaluate();

    /**
     * @brief  Finds the best place for home.
     * @return best place's coordinates
     */
    Vector getBestPlace() const;

    /**
     * @brief  Prints map to string. (For debug).
     * @return string with map
     */
    std::string print() const;

private:
    /// Pointer to heap.
    ObjectHeap* heap;

    /// Map with values.
    std::vector< std::vector<double> > map;

    /// Amount of rows in map.
    uint map_rows;

    /// Amount of columns in map.
    uint map_columns;
};

#endif // HUMANOID_VALUE_MAP_H
