/*
    Copyright (c) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef E_CLI_INVALID_INPUT_H
#define E_CLI_INVALID_INPUT_H

#include <string>
#include <exception>

/**
 * @brief Invalid CLI input exception.
 */
class ECLIInvalidInput: public std::exception
{
public:
    /**
     * @brief Constructor.
     * @param res_path  path to resource
     */
    ECLIInvalidInput(std::string reason);

    virtual const char * what() const throw();

private:
    /// Reason of this exception.
    std::string reason;
};

#endif // E_CLI_INVALID_INPUT_H
