/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <string>
#include <map>

#include "../Object/Object.h"
#include "../ObjectHeap/ObjectHeap.h"

/**
 * @class ObjectFactory
 * @brief ObjectFactory Class
 */
class ObjectFactory
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    ObjectFactory();

    /**
     * @brief Destructor.
     */
    ~ObjectFactory();

    //**************************************************************************
    // OBJECTS CREATION.
    //**************************************************************************

    /**
     * @brief  Creates new object.
     * @param  type     object type
     * @param  params   map with object params
     * @return pointer to created object
     */
    Object * createObject(ObjectType type, const std::map <std::string, int> & params);
};

#endif // OBJECT_FACTORY_H
