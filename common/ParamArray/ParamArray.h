/*
    Copyright (c) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef PARAM_ARRAY_H
#define PARAM_ARRAY_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <map>

#include "EParamArrayInvalidKey.h"
#include "../BasicTypes.h"
#include "../Log/Log.h"

/**
 * @class ParamArray
 * @brief Assoсiative array (keys are strings, value type -- doesn't matter).
 *        Used in Action, Message and ObjectFactory.
 *
 *        *NOTE*: You will experience memory leaks, if you will add classes
 *                instantations to this array. Reason is simple: ParamArray
 *                doesn't calling any destructors.
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
    ParamArray() :
        memory(new char[64]),
        memory_size(64),
        current_index(0)
    {
    }

    /**
     * @brief Copy constructor.
     */
    ParamArray(const ParamArray& pa) :
        memory(new char[pa.memory_size]),
        memory_size(pa.memory_size),
        current_index(pa.current_index)
    {
        memcpy(memory, pa.memory, pa.memory_size);
    }

    /**
     * @brief Destructor.
     */
    ~ParamArray()
    {
        delete[] (this -> memory);
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
        // Don't have enough memory?
        if (this -> current_index + sizeof(Type) >= this -> memory_size)
        {
            char* new_memory = new char[this -> memory_size + 64];
            memcpy(new_memory, this -> memory, this -> memory_size);

            delete[] (this -> memory);
            this -> memory = new_memory;

            this -> memory_size += 64;
        }

        // Copying data.
        void* ptr = &(this -> memory[this -> current_index]);
        new (ptr) Type(value);

        // Adding key.
        this -> map[key] = ptr;

        // Increase index.
        this -> current_index += sizeof(Type);
    }

    /**
     * @brief  Gets key value by key.
     * @param  key              key
     * @param  suppress_err_msg whether suppress error messages to cerr or not
     * @return key value
     */
    template <class Type> Type getValue(std::string key, bool suppress_err_msgs = false) const throw(EParamArrayInvalidKey)
    {
        std::map <std::string, void *> :: const_iterator iter = this -> map.find(key);

        if (iter == map.end())
        {
            if (!suppress_err_msgs)
            {
                Log::WARN(std::string("Tried to get value by key, which ") +
                          std::string("doesn't seem to be existed (key is '") +
                          key + "').");
            }

            throw EParamArrayInvalidKey();
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
                Log::WARN(std::string("Tried to delete key, which doesn't ") +
                          std::string("seem to be existed (key is '") + key +
                          "').");
            }

            return false;
        }

        this -> map.erase(iter);

        return true;
    }

    /**
     * @brief Removes all elements from ParamArray.
     */
    void clear()
    {
        this -> map.clear();
    }

private:
    /// Map with keys.
    std::map <std::string, void*> map;

    /// Pointer to allocated memory.
    char* memory;

    /// Memory size.
    uint memory_size;

    /// Index of free memory in memory array.
    uint current_index;
};

#endif // PARAM_ARRAY_H
