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
            // FIXME: Dirty workaround. Rewrite ParamArray immediately!
            //free(i -> second);
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
        // Copying data.
        Type* copy = static_cast<Type*>( malloc(sizeof(Type)) );
        *copy = value;

        // Firstly removing this key and value (if it's existed).
        // Suppressing error messages (don't want to litter to cerr).
        this -> removeKey(key, true);

        // Adding key.
        this -> map[key] = copy;
    }

    /**
     * @brief  Gets key value by key.
     * @param  key              key
     * @param  suppress_err_msg whether suppress error messages to cerr or not
     * @return key value
     */
    template <class Type> Type getValue(std::string key, bool suppress_err_msgs = false) const throw(EParamArrayBadKey)
    {
        std::map <std::string, void *> :: const_iterator iter = this -> map.find(key);

        if (iter == map.end())
        {
            if (!suppress_err_msgs)
            {
                std::cerr << "[WARN] ParamArray: tried to get value by key, " <<
                             "which doesn't seem to be existed (key is '" <<
                             key << "')." << std::endl;
            }

            throw EParamArrayBadKey();
        }

        return *(static_cast<Type*>(iter -> second));
    }

    /**
     * @brief  Removes key from param array.
     * @param  key              key
     * @param  suppress_err_msg whether suppress error messages to cerr or not
     * @return true, if key was existed and succesfully removed
     * @return false, if key wasn't existed
     */
    bool removeKey(std::string key, bool suppress_err_msgs = false)
    {
        std::map <std::string, void*> :: const_iterator iter = this -> map.find(key);

        if (iter == map.end())
        {
            if (!suppress_err_msgs)
            {
                std::cerr << "[WARN] ParamArray: tried to delete key, which " <<
                             "doens't exist (key is '" << key << "')." <<
                             std::endl;
            }

            return false;
        }

        free(iter -> second);
        this -> map.erase(iter);

        return true;
    }

    /**
     * @brief Removes all elements from ParamArray.
     */
    void clear()
    {
        // FIXME: Memory leaks!
        this -> map.clear();
    }

private:
    /// Map with keys.
    std::map <std::string, void*> map;
};

#endif // PARAM_ARRAY_H
