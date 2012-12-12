/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECT_HEAP_H
#define OBJECT_HEAP_H

#include <cstdlib>
#include <algorithm>
#include <map>

#include "../Object/Object.h"
#include "../../common/BasicTypes.h"

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
    uint getAmount() const;

    /**
     * @brief  get amount of element this type
     * @param  type object type
     * @return amount of element
     */
    uint getTypeAmount(ObjectType type) const;


private:
    /// Vector with all objects.
    std::map<uint,Object*> data[AMNT_OBJECT_TYPES + 1];

    //**************************************************************************
    // ITERATOR
    //**************************************************************************
public:

    /**
     * @brief The iterator class
     */
    class iterator: public std::map <uint, Object*>::iterator
    {
    public:
        Object* operator *()
        {
            return static_cast<std::_Rb_tree_node< std::pair< uint,Object* > >*>(_M_node)->_M_value_field.second;
        }
        iterator(std::map<uint, Object*>::iterator it)
        {
            this->_M_node = it._M_node;
        }

        iterator()
        {

        }

    };

    /**
     * @brief The iterator_const class
     */
    class const_iterator: public std::map<uint, Object*>::const_iterator
    {
    public:
        Object* operator *() const
        {
            return static_cast<const std::_Rb_tree_node< std::pair< uint,Object* > >*>(_M_node)->_M_value_field.second;
        }

        const_iterator(std::map<uint, Object*>::const_iterator it)
        {
            this -> _M_node = it._M_node;
        }

        const_iterator()
        {

        }

        const_iterator(iterator it)
        {
            this -> _M_node = it._M_node;
        }
    };


    iterator begin()
    {
        return static_cast<iterator>(this->data[0].begin());
    }

    iterator end()
    {
        return static_cast<iterator>(this->data[0].end());
    }

    iterator begin(ObjectType type)
    {
        return static_cast<iterator>(this->data[type + 1].begin());
    }

    iterator end(ObjectType type)
    {
        return static_cast<iterator>(this->data[type + 1].end());
    }

    const_iterator begin() const
    {
        return static_cast<const_iterator>(this->data[0].begin());
    }

    const_iterator end() const
    {
        return static_cast<const_iterator>(this->data[0].end());
    }

    const_iterator begin(ObjectType type) const
    {
        return static_cast<const_iterator>(this->data[type + 1].begin());
    }

    const_iterator end(ObjectType type) const
    {
        return static_cast<const_iterator>(this->data[type + 1].end());
    }
    iterator find(Object* obj, bool return_obj_type_iter = true)
    {
        iterator iter;
        if (return_obj_type_iter)
        {
            iter = data[obj -> getType()].find(obj->getObjectID());
        }
        else
        {
            iter = data[0].find(obj->getObjectID());
        }
        return iter;
    }
public:
    //**************************************************************************
    // ADDING/REMOVING ELEMENTS.
    //**************************************************************************

    /**
     * @brief  Pushes object to heap.
     * @param  object   object to push
     * @return
     */
    bool push(Object* obj);

    /**
     * @brief  Removes object from heap.
     * @param  object   object to remove
     * @return
     */
    bool remove(Object* object);

    /**
     * @brief Clears the heap
     */
    void clear();

    //**************************************************************************
    // PRINTING CONTENTS.
    //**************************************************************************

    /**
     * @brief  Print IDs of contained objects.
     * @return string with ids.
     */
    std::string printIDs(std::string indent = "\t", uint columns = 5) const;

};


#endif // OBJECTHEAP_H
