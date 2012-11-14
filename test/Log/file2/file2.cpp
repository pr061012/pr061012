#include "file2.h"

#include "../../../log/Log.h"

void ClassFile2::printFile2()
{
    Log::NOTE("Note Class File2");
    Log::WARN("Warn Class File2");
    Log::ERROR("Error Class File2");
}

void fooFile2()
{
    Log::NOTE("Note fooFile2");
    Log::WARN("Warn fooFile2");
    Log::ERROR("Error fooFile2");
}
