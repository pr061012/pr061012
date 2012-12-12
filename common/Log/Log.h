/*
    Copyright (C) 2012, pr061012 Team.
    See the COPYING file for copying permission.
*/

#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>

/// NOTE define.
#define NOTE(text)  note(__FILE__, __PRETTY_FUNCTION__, __LINE__, text)

/// WARN define.
#define WARN(text)  warn(__FILE__, __PRETTY_FUNCTION__, __LINE__, text)

/// ERROR define.
#define ERROR(text) error(__FILE__, __PRETTY_FUNCTION__, __LINE__, text)

/**
 * @brief Logger class.
 */
class Log
{
    /// Log file.
    static std::ofstream log_file;

public:

    /**
     * @brief Logs warning to the log file.
     */
    static void warn(std::string file_name, std::string func_name,
                     int line_number, std::string text);

    /**
     * @brief Logs error to the log file.
     */
    static void error(std::string file_name, std::string func_name,
                      int line_number, std::string text);

    /**
     * @brief Logs note to the log file.
     */
    static void note(std::string file_name, std::string func_name,
                     int line_number, std::string text);
};

#endif // LOG_H
