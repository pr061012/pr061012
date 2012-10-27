/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef INDEXATOR_H
#define INDEXATOR_H

#include <string>
#include <vector>
#include "../Object/Object.h"
#include "../ObjectHeap/ObjectHeap.h"

/**
 * @class Indexator
 * @brief
 */
class Indexator
{

//******************************************************************************
// NESTED CLASSES
//******************************************************************************

class Window;
#include "Window/Window.h"

class Cell;
#include "Cell/Cell.h"

public:
    //**************************************************************************
    // CONSTRUCTORS/DESTRUCTOR.
    //**************************************************************************

    /**
     *  @brief Constructor.
     */
    Indexator();

    /**
     *  @brief  Creates grid, visible areas for creatures and weather
     *          and indexates object from heap.
     *  @param  list heap with objects
     */
    Indexator(ObjectHeap * list);

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

    /**
     *  @brief  Add new object to the index
     *  @param  object an object to add
     */
    void addObject(Object * object);

    /**
     * @brief   Creates a list of objects that are visible to the given object
     *          and returns a pointer to it.
     * @param   object  pointer to object
     * @return  visible objects
     */
    ObjectHeap * createWindow(Object * object);

    //**************************************************************************
    // STEP.
    //**************************************************************************

    /**
     * @brief   Reindexes objects.
     */
    void step();

private:
    /// List with all windows.
    std::vector <Window> windows;
};

#endif // INDEXATOR_H
