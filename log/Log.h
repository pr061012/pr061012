/*
    Copyright (c, std::string text) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef LOG_H__
#define LOG_H__

class Log;


#include <string>
/**
 * @brief The Log class
 */
class Log
{
    /// Log
    std::ifstream log_file;

public:
    /**
     * @brief Constructor
     */
    Log();

    /**
     * @brief Destructor
     */
    ~Log();

    /**
     * @brief warning logger
     */
    static void warn(std::string file_name, std::string func_name, int line_number, std::string text);

    /**
     * @brief error logger
     */
    static void error(std::string file_name, std::string func_name, int line_number, std::string text);

    /**
     * @brief note logger
     */
    static void note(std::string file_name, std::string func_name, int line_number, std::string text);

};

#endif
