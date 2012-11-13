#include "../../log/Log.h"
#include "../../log/LogDefines.h"

#include "file1/file1.h"
#include "file2/file2.h"

class Any
{
public:
    void foo()
    {
        Log::warn("Any_Foo_Warning");
        Log::error("Any_Foo_Error");
        Log::note("Any_Foo_Note");
    }
};

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
    Any var;
    var.foo();
    ClassFile1 class_file1;
    ClassFile2 class_file2;
    class_file1.printFile1();
    class_file2.printFile2();
    fooFile1();
    fooFile2();
}
