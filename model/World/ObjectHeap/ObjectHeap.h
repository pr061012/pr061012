/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECTHEAP_H
#define OBJECTHEAP_H

#include "../Object/Object.h"


/**
  * @class ObjectHeap
  * @brief ObjectHeap class
  */

class ObjectHeap
{
public:

    //******************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //******************************************************************************

    /**
     * @brief Constructor.
     */
    ObjectHeap();

    /**
     * @brief Destructor.
     */
     ~ObjectHeap();

	/**
     * @brief Return next object in world.
     * @return Object*
	 */
    Object* next();

	/**
     * @brief Work as next(), but return object with certain type.
     * @return Object*
	 * @param  type
	 */
    Object* next(int type);

	/**
     * @brief Push object to heap.
     * @param  object
     * @return
	 */
    bool push(Object* object);

	/**
     * @brief Remove object from heap.
	 * @param  object
     * @return
	 */
    bool remove(Object* object);
};

#endif // OBJECTHEAP_H
