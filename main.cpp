#include <iostream>

#include "model/BasicDefines.h"

#include "model/World/World.h"
#include "control/Controller/Controller.h"
#include "view/View.h"

int main()
{
    try
    {
        World world(rand(), SZ_WORLD_HSIDE);
        Controller control(&world);
        View view(&world);
    }
    catch(std::bad_alloc & exc)
    {
        std::cerr << "[ERROR] Failed to allocate memory. Terminating." <<
                     std::endl;
    }

    return 0;
}
