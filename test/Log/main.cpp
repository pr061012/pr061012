#include "../../log/Log.h"
#include "../../log/LogDefines.h"

void foo()
{
    Log::warn("Foo_Warning");
    Log::error("Foo_Error");
    Log::note("Foo_Note");
}

int main()
{
    Log::warn("Warning");
    Log::error("Error");
    Log::note("Note");
    foo();
}
