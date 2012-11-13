/*
    Copyright (c, std::string text) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <fstream>
#define PATH_TO_LOG "../log"
#include "Log.h"

void Log::open()
{
    log_file.open(PATH_TO_LOG);
}

void Log::close()
{
    log_file.close();
}

void Log::error(std::string file_name, std::string func_name, int line_number, std::string text)
{
    log_file << "[ERROR]" << file_name << " : " << func_name;
    log_file << " : " << line_number << " : "<< text;
}

void Log::note(std::string file_name, std::string func_name, int line_number, std::string text)
{
    log_file << "[NOTE]" << file_name << " : " << func_name;
    log_file << " : " << line_number << " : "<< text;
}

void Log::warn(std::string file_name, std::string func_name, int line_number, std::string text)
{
    log_file << "[WARN]" << file_name << " : " << func_name;
    log_file << " : " << line_number << " : "<< text;
}


