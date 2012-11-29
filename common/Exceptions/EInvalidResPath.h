/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef E_INVALID_RES_PATH_H
#define E_INVALID_RES_PATH_H

#include <string>
#include <exception>

/**
 * @brief Invalid resource path exception: failed to load game resource with
 *        specified path because it doesn't exist.
 */
class EInvalidResPath : public std::exception
{
public:
    /**
     * @brief Constructor.
     * @param res_path  path to resource
     */
    EInvalidResPath(std::string res_path);

    /**
     * @brief  Gets resource path.
     * @return resource path
     */
    std::string getResPath();

    virtual const char* what() const throw();

private:
    /// Resource path.
    std::string res_path;
};

#endif // EINVALIDRESPATH_H
