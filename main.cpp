#include <iostream>

#include "model/World/World.h"

int main()
{
    try
    {
        World world(100, 50, 50);
    }
    catch(std::bad_alloc & exc)
    {
        std::cerr << "[ERROR] Failed to allocate memory. Terminating." <<
                     std::endl;
    }

    return 0;
}
