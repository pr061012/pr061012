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
    ~ParamArray(){}

    //**************************************************************************
    // KEYS ACCESSING.
    //**************************************************************************

    /**
     * @brief Adds new key with value into param array. Note: it will overwrite
     *        value if such key already exists!
     * @param key   key to add
     * @param value key value
     */
    template <class Type> void addKey(std::string key, Type value);

    /**
     * @brief  Gets key value by key.
     * @param  key  key
     * @return key value
     */
    template <class Type> Type getValue(std::string key) const throw(EParamArrayBadKey);

    /**
     * @brief  Removes key from param array.
     * @param  key  to remove
     * @return true, if key was existed and succesfully removed
     * @return false, if key wasn't existed
     */
    template <class Type> bool removeKey(std::string key);

private:
    /// Map with keys.
    std::map <std::string, void *> map;
};

#endif // PARAM_ARRAY_H
