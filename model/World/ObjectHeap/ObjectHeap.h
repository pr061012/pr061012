/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECT_HEAP_H
#define OBJECT_HEAP_H

#include <vector>
#include <cstdlib>

#include "../Object/Object.h"
#include "../../BasicTypes.h"

/**
 * @class ObjectHeap
 * @brief ObjectHeap class
 */
class ObjectHeap
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    ObjectHeap();

    /**
     * @brief Destructor.
     */
    ~ObjectHeap();

    //**************************************************************************
    // GETTING TYPE AMOUNT
    //**************************************************************************

    /**
     * @brief  get amount of element this type
     * @param  type object type
     * @return amount of element
     */
    unsigned int getTypeAmount(ObjectType);

    //**************************************************************************
    // ADDING/REMOVING ELEMENTS.
    //**************************************************************************

    /**
     * @brief  Pushes object to heap.
     * @param  object   object to push
     * @return
     */
    bool push(Object* object);

    /**
     * @brief  Removes object from heap.
     * @param  object   object to remove
     * @return
     */
    bool remove(Object* object);

private:
    std::vector < std::vector <Object*>* > data;
};

#endif // OBJECTHEAP_H
