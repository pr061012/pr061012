/*
    Copyright (c, std::string text) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>

#define NOTE(text)  note(__FILE__, __PRETTY_FUNCTION__, __LINE__, text)
#define WARN(text)  warn(__FILE__, __PRETTY_FUNCTION__, __LINE__, text)
#define ERROR(text) error(__FILE__, __PRETTY_FUNCTION__, __LINE__, text)

/**
 * @brief The Log class
 */
class Log
{
    /// Log
    static std::ofstream log_file;

public:

    /**
     * @brief Logs warning to log file.
     */
    static void warn(std::string file_name, std::string func_name,
                     int line_number, std::string text);

    /**
     * @brief Logs error to log file.
     */
    static void error(std::string file_name, std::string func_name,
                      int line_number, std::string text);

    /**
     * @brief Logs note to log file.
     */
    static void note(std::string file_name, std::string func_name,
                     int line_number, std::string text);
};

#endif
