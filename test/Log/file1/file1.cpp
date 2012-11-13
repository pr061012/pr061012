#include "../../../log/Log.h"
#include "../../../log/LogDefines.h"
#include "file1.h"

void ClassFile1::printFile1()
{
    Log::note("Note Class File1");
    Log::warn("Warn Class File1");
    Log::error("Error Class File1");
}

void fooFile1()
{
    Log::note("Note fooFile1");
    Log::warn("Warn fooFile1");
    Log::error("Error fooFile1");
}
