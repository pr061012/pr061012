/*
    Copyright (c, char* text) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef LOG_H__
#define LOG_H__

#include <string>
/**
 * @brief The Log class
 */
class Log
{
public:
    /**
     * @brief warning logger
     */
    static void warn(char* file_name, char* func_name, int line_number, char* text);

    /**
     * @brief error logger
     */
    static void error(char* file_name, char* func_name, int line_number, char* text);

    /**
     * @brief note logger
     */
    static void note(char* file_name, char* func_name, int line_number, char* text);

};

#endif
