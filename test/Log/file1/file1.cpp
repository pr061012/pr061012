#include "file1.h"

#include "../../../log/Log.h"

void ClassFile1::printFile1()
{
    Log::NOTE("Note Class File1");
    Log::WARN("Warn Class File1");
    Log::ERROR("Error Class File1");
}

void fooFile1()
{
    Log::NOTE("Note fooFile1");
    Log::WARN("Warn fooFile1");
    Log::ERROR("Error fooFile1");
}
