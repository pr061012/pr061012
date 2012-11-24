/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECT_HEAP_H
#define OBJECT_HEAP_H

#include <vector>
#include <cstdlib>
#include <algorithm>

#include "../Object/Object.h"
#include "../../../common/BasicTypes.h"

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
     * @brief  get amount of element
     * @return amount of element
     */
    unsigned int getAmount();

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

    //**************************************************************************
    // PRINTING CONTENTS.
    //**************************************************************************

    /**
     * @brief  Print IDs of contained objects.
     * @return string with ids.
     */
    std::string printIDs(std::string indent = "\t", uint columns = 5) const;

private:
    /// Vector with all objects.
    std::vector < std::vector <Object*> > data;

    //**************************************************************************
    // ITERATOR
    //**************************************************************************
public:
    typedef std::vector <Object*>::iterator iterator;
    typedef std::vector <Object*>::const_iterator const_iterator;

    iterator begin(ObjectType type)
    {
        return data[type+1].begin();
    }

    const_iterator begin(ObjectType type) const
    {
        return data[type+1].begin();
    }

    iterator end(ObjectType type)
    {
        return data[type+1].end();
    }

    const_iterator end(ObjectType type) const
    {
        return data[type+1].end();
    }

    iterator begin()
    {
        return data[0].begin();
    }

    const_iterator begin() const
    {
        return data[0].begin();
    }

    iterator end()
    {
        return data[0].end();
    }

    const_iterator end() const
    {
        return data[0].end();
    }

    iterator find(Object* obj, bool return_obj_type_iter = true)
    {
        iterator begin;
        iterator end;

        if ( return_obj_type_iter )
        {
            ObjectType type = obj -> getType();

            begin = this -> begin(type);
            end = this -> end(type);
        }
        else
        {
            begin = this -> begin();
            end = this -> end();
        }

        for (iterator i = begin; i != end; i++)
        {
            if (*i == obj)
            {
                return i;
            }
        }

        return end;
    }

};

#endif // OBJECTHEAP_H
