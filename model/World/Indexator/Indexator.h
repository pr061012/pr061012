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
     * @brief  Returns heap with objects from the certain frame.
     * @param  frame    from to find objects from
     * @return heap with objects
     */
    ObjectHeap * getFrameContents(Frame frame);

    /**
     * @brief Creates window in windows for certain object and returns pointer
     *        "view from window". Object must have view_area (Frame).
     * @param  object   pointer to object
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

    //**************************************************************************
    // ACCESSORS.
    //**************************************************************************

    /**
     * @brief Set the value of windows.
     * @param new_var the new value of windows
     */
    void setWindows(std::vector <Window> new_var);

    /**
     * @brief Get the value of windows.
     * @return the value of windows
     */
    std::vector <Window> getWindows();

private:
    /// List with all windows.
    std::vector <Window> windows;
};

#endif // INDEXATOR_H
