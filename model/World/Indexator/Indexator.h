/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef INDEXATOR_H
#define INDEXATOR_H

#include <string>
#include <set>
#include <map>
#include "../Object/Object.h"
#include "../ObjectHeap/ObjectHeap.h"

//*****************************************************************************
// TODO
// - fix getAreaContents so it works with toroidal world
//*****************************************************************************

/**
 * @class Indexator
 * @brief
 */
class Indexator
{
public:
    //**************************************************************************
    // CONSTRUCTORS/DESTRUCTOR.
    //**************************************************************************

    /**
     *  @brief  Creates grid and indexates object from heap.
     *  @param  list heap with objects
     *  @param  size size of the world
     */
    Indexator(double size, ObjectHeap * list = 0);

    /**
     * @brief Destructor.
     */
    ~Indexator();

    //**************************************************************************
    // GETTING OBJECTS.
    //**************************************************************************

    /**
     *  @brief  Returns heap with objects from the certain area.
     *  @param  area where to look for objects
     *  @return heap with objects in given area
     */
    ObjectHeap * getAreaContents(Shape area);

    //**************************************************************************
    // REINDEXATING
    //**************************************************************************

    /**
     *  @brief  Creates an index for all given objects, and removes the previous
     *          one.
     *  @param  objects heap of objects
     */
    void reindexate(ObjectHeap * objects);

    /**
     *  @brief  Reindexates an object or adds new object to index.
     *  @param  object an object t reindexate
     */
    void reindexate(Object * object);

    /**
     * @brief   Adds object to index.
     * @param   object an object to add
     */
    void addObject(Object * object);

    /**
     * @brief   Removes object from index.
     * @param   object an object to remove
     */
    void removeObject(Object * object);


private:

    /**
     *  @brief Hidden empty constructor.
     */
    Indexator();

    //**************************************************************************
    // ATTRIBUTES
    //**************************************************************************

    /// Maximimum size of the cell
    static const double MAX_CELL_SIZE;

    /// Size of world
    const double world_size;

    /// Ammount of cells on a row
    const uint row_size;

    /// Cell size
    const double cell_size;

    /// Shape of the world
    const Shape world_shape;

    /// Type of an index structure
    typedef std::map<Object *, uint *> Index;

    /// Index structure
    Index index;
    ObjectHeap ** cells;

    //**************************************************************************
    // UTILITIES
    //**************************************************************************

    /**
     * @brief   Returns the minimum of two uints.
     */
    uint min (uint a, uint b);

    /**
     * @brief   Returns maximum of two uints.
     */
    uint max (uint a, uint b);

    /**
     * @brief   Returns cells within which the shape lies
     * @param   shape 
     * @return  an array of coordinates of left bottom and
     *          right top coordinates (must be freed)
     */
    uint * getCellsArea(Shape& shape);

    /**
     * @brief   Returns row index for coodinate
     * @param   coordinate
     * @return  index of coordinate
     */
    uint getRow(double coordinate);

    /**
     * @brief   Initialize index
     */
    void init();

    /**
     * @brief   Destroys index.
     */
    void destroy();

};

#endif // INDEXATOR_H
