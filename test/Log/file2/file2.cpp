#include "../../../log/Log.h"
#include "../../../log/LogDefines.h"
#include "file2.h"

void ClassFile2::printFile2()
{
    Log::note("Note Class File2");
    Log::warn("Warn Class File2");
    Log::error("Error Class File2");
}

void fooFile2()
{
    Log::note("Note fooFile2");
    Log::warn("Warn fooFile2");
    Log::error("Error fooFile2");
}
