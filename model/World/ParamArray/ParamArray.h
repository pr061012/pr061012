/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef PARAM_ARRAY_H
#define PARAM_ARRAY_H

#include <string>
#include <map>

#include "EParamArrayBadKey.h"

/**
 * @class ParamArray
 * @brief Assoсiative array (keys are strings, values are ints). Used in
 *        PendingAction and ObjectFactory.
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

        for(i = this -> map.begin(); i != map.end(); i++)
        {
            delete i -> second;
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
        Type * copy = new Type(value);
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

        if(iter == map.end())
        {
            std::cerr << "[WARN] ParamArray: tried to get value by key, which " <<
                         "doesn't seem to be existed (key is '" << key << "')." <<
                         std::endl;

            throw EParamArrayBadKey();
        }

        return *(reinterpret_cast<Type *>(iter -> second));
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

        if(iter == map.end())
        {
            std::cerr << "[WARN] ParamArray: tried to delete key, which doesn't " <<
                         "seem to be be existed (key is '" << key << "')." <<
                         std::endl;

            return false;
        }

        delete iter -> second;
        this -> map.erase(iter);

        return true;
    }

private:
    /// Map with keys.
    std::map <std::string, void *> map;
};

#endif // PARAM_ARRAY_H
