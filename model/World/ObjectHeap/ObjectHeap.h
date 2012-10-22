/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

// NOTE:
//  - You should use ObjectType for type.

#ifndef OBJECT_HEAP_H
#define OBJECT_HEAP_H

#include "../Object/Object.h"

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
    // GETTING NEXT ELEMENTS.
    //**************************************************************************

    /**
     * @brief  Return next object in heap.
     * @return pointer to object
     */
    Object* next();

    /**
     * @brief  Work as next(), but return object with certain type.
     * @param  type object type
     * @return pointer to object
     */
    Object* next(int type);

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
};

#endif // OBJECTHEAP_H
