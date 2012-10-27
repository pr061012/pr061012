/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef INDEXATOR_H
#define INDEXATOR_H

#include <string>
#include <vector>
#include "Window/Window.h"
#include "../Object/Object.h"
#include "../ObjectHeap/ObjectHeap.h"

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
     * @brief Constructor.
     */
    Indexator();

    /**
     * @brief Creates grid and indexates object from heap.
     * @param list  heap with objects
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
     * @brief  Returns heap with objects from the certain area.
     * @param  area where to look for objects
     * @return heap with objects in given area
     */
    ObjectHeap * getAreaContents(Shape area);

    /**
     * @brief Creates window in windows for certain object and returns pointer
     *        "view from window". Object must have view_area (shape).
     * @param  object  pointer to object
     * @return visible objects
     */
    ObjectHeap * createWindow(Object * object);

    //**************************************************************************
    // STEP.
    //**************************************************************************

    /**
     * @brief Reindexes objects and changes window's positions.
     */
    void step();

private:
    /// List with all windows.
    std::vector <Window> windows;
};

#endif // INDEXATOR_H
