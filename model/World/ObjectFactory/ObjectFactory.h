/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

// NOTE:
//  - You should use ObjectType for type.

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
    /// If not NULL, all objects will be automatically added in this ObjectHeap
    ObjectHeap* list;

public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    ObjectFactory();

    /**
     * @brief Create ObjectFactory which will automatically add created objects in ObjectHeap provided.
     */
    ObjectFactory(ObjectHeap* list);

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
    Object* createObject(int type, std::map <std::string, void*> params);
};

#endif // OBJECT_FACTORY_H
