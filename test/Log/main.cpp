#include "../../log/Log.h"

#include "file1/file1.h"
#include "file2/file2.h"

class Any
{
public:
    void foo()
    {
        Log::WARN("Any_Foo_Warning");
        Log::ERROR("Any_Foo_Error");
        Log::NOTE("Any_Foo_Note");
    }
};

void foo()
{
    Log::WARN("Foo_Warning");
    Log::ERROR("Foo_Error");
    Log::NOTE("Foo_Note");
}

int main()
{
    Log::WARN("Warning");
    Log::ERROR("Error");
    Log::NOTE("Note");

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
