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
     * @param heap      heap with objects
     * @param v_size    world's vertical size
     * @param h_size    world's horizontal size
     * @param cell_size map's cell size
     */
    HumanoidValueMap(const ObjectHeap* heap, double v_size, double h_size,
                     double cell_size = 0.1);

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
    /**
     * @brief Evaluates one object.
     * @param obj   Object
     */
    void evaluateObject(const Object* obj);

    /// Pointer to heap.
    const ObjectHeap* heap;

    /// Map with values.
    std::vector< std::vector<double> > map;

    /// Cell size.
    double cell_size;

    /// Amount of rows in map.
    uint map_rows;

    /// Amount of columns in map.
    uint map_columns;

    /// Record radius.
    uint record_radius;

    std::vector<int> min_i;
    std::vector<int> min_j;
    double min = 0;
};

#endif // HUMANOID_VALUE_MAP_H
