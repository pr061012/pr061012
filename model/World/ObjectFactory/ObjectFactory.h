/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "../Object/Object.h"

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

    /**
     * @brief Create object
     * @return Object*
     * @param  type
     * @param  params
     */
    Object* createObject(int type, std::map<std::string,void*> params);

};

#endif // OBJECTFACTORY_H
