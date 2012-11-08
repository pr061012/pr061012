/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef PARAM_ARRAY_H
#define PARAM_ARRAY_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

#include "EParamArrayBadKey.h"

/**
 * @class ParamArray
 * @brief Assoсiative array (keys are strings, values are ints). Used in
 *        PendingAction and ObjectFactory.
 *
 *        **NOTE**: Be very accurate while working with this class. You
 *                  *shouldn't* store in ParamArray any classes instantiations.
 *                  Reason of such restriction is pretty simple: ParamArray uses
 *                  C functions malloc() and free() (instead of new and delete).
 *
 *        FIXME: It's working variant, but still ugly because of
 *               reinterpret_cast<>(). Need to look through boost::any and
 *               implement something similar.
 */
class ParamArray
{
public:
    //**************************************************************************
    // CONSTRUCTOR/DESTRUCTOR.
    //**************************************************************************

    /**
     * @brief Constructor.
     */
    ParamArray(){}

    /**
     * @brief Destructor.
     */
    ~ParamArray()
    {
        std::map <std::string, void*> :: const_iterator i;

        for (i = this -> map.begin(); i != map.end(); i++)
        {
            free(i -> second);
        }

        this -> map.clear();
    }

    //**************************************************************************
    // KEYS ACCESSING.
    //**************************************************************************

    /**
     * @brief Adds new key with value into param array. Note: it will overwrite
     *        value if such key already exists!
     * @param key   key to add
     * @param value key value
     */
    template <class Type> void addKey(std::string key, Type value)
    {
        Type * copy = static_cast<Type *>( malloc(sizeof(Type)) );
        *copy = value;

        this -> map[key] = copy;
    }

    /**
     * @brief  Gets key value by key.
     * @param  key  key
     * @return key value
     */
    template <class Type> Type getValue(std::string key) const throw(EParamArrayBadKey)
    {
        std::map <std::string, void *> :: const_iterator iter = this -> map.find(key);

        if (iter == map.end())
        {
            std::cerr << "[WARN] ParamArray: tried to get value by key, " <<
                         "which doesn't seem to be existed (key is '" << key <<
                         "')." << std::endl;

            throw EParamArrayBadKey();
        }

        return *(static_cast<Type *>(iter -> second));
    }

    /**
     * @brief  Removes key from param array.
     * @param  key  to remove
     * @return true, if key was existed and succesfully removed
     * @return false, if key wasn't existed
     */
    bool removeKey(std::string key)
    {
        std::map <std::string, void *> :: const_iterator iter = this -> map.find(key);

        if (iter == map.end())
        {
            std::cerr << "[WARN] ParamArray: tried to delete key, which " <<
                         "doens't exist (key is '" << key << "')." << std::endl;

            return false;
        }

        free(iter -> second);
        this -> map.erase(iter);

        return true;
    }

private:
    /// Map with keys.
    std::map <std::string, void *> map;
};

#endif // PARAM_ARRAY_H
