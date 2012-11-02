/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef INDEXATOR_H
#define INDEXATOR_H

#include <string>
#include <vector>
#include <map>
#include "../Object/Object.h"
#include "../ObjectHeap/ObjectHeap.h"


/**
 * @class Indexator
 * @brief
 */
class Indexator
{

private:
//**************************************************************************
// FOR TEST USE ONLY!!!
typedef std::vector<Object*> ObjectHeap;
//**************************************************************************

public:
    //**************************************************************************
    // CONSTRUCTORS/DESTRUCTOR.
    //**************************************************************************

    /**
     *  @brief Constructor.
     */
    Indexator();

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
     *  @brief  Creates an index for all given objects.
     *  @param  objects heap of objects
     */
    void reindexate(ObjectHeap * objects);

    /**
     *  @brief  Reindexates an object or adds new object to index.
     *  @param  object an object t reindexate
     */
    void reindexate(Object * object);

private:


    /// Maximimum size of the cell
    static const double MAX_CELL_SIZE;

    /// Cell size
    double cell_size;

    /// Ammount of cells on a row
    int row_size;

    /// Type of an index structure
    typedef int Area[4];
    typedef std::map<Object *, Area> Index;

    /// Index structure
    Index index;
    ObjectHeap ** cells;
};

#endif // INDEXATOR_H
