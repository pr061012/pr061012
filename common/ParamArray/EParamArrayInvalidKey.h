/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef E_PARAM_ARRAY_INVALID_KEY_H
#define E_PARAM_ARRAY_INVALID_KEY_H

#include <string>
#include <exception>

/**
 * @brief ParamArray exception -- unknown (invalid) key was used.
 */
class EParamArrayInvalidKey : public std::exception
{
public:
    /**
     * @brief Constructor.
     * @param key_name  invalid key name
     */
    EParamArrayInvalidKey(std::string key_name);

    /**
     * @brief  Gets invalid key name.
     * @return invalid key name
     */
    std::string getKeyName();

    virtual const char* what() const throw();
private:
    /// Invalid key name.
    std::string key_name;
};

#endif // E_PARAM_ARRAY_BAD_KEY_H
