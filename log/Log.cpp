/*
    Copyright (c, std::string text) 2012, pr061012 Team.
    See the LICENSE file for copying permission.
*/

#include <cstdlib>

#include "Log.h"

std::ofstream Log::log_file("LOG");

void Log::error(std::string file_name, std::string func_name,
                int line_number, std::string text)
{
    log_file << "[ERROR] " << file_name << ":" << line_number;
    log_file << " : " << func_name << " "<< text << std::endl;
}

void Log::note(std::string file_name, std::string func_name,
               int line_number, std::string text)
{
    log_file << "[NOTE]  " << file_name << ":" << line_number;
    log_file << " : " << func_name << " "<< text << std::endl;
}

void Log::warn(std::string file_name, std::string func_name,
               int line_number, std::string text)
{
    log_file << "[WARN]  " << file_name << ":" << line_number;
    log_file << " : " << func_name << " "<< text << std::endl;
}


