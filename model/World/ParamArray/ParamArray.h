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
    void addKey(std::string key, int value);

    /**
     * @brief  Gets key value by key.
     * @param  key  key
     * @return key value
     */
    int getValue(std::string key) const throw(EParamArrayBadKey);

    /**
     * @brief  Removes key from param array.
     * @param  key  to remove
     * @return true, if key was existed and succesfully removed
     * @return false, if key wasn't existed
     */
    bool removeKey(std::string key);

private:
    /// Map with keys.
    std::map <std::string, int> map;
};

#endif // PARAM_ARRAY_H
