#include <iostream>
#include <ctime>

#include "model/BasicDefines.h"

#include "model/World/World.h"
#include "control/Controller/Controller.h"
#include "view/View.h"

/// Period for world updating.
const int PERIOD = CLOCKS_PER_SEC/TM_TICKS_PER_SECOND;

int main()
{
    try
    {
        World world(rand(), SZ_WORLD_HSIDE);
        //Controller control(&world);
        View view(&world);

        int t0 = clock();

        do
        {
            if(clock() - t0 > PERIOD)
            {
                t0 += PERIOD;
            }

            view.redraw();

        } while(view.isExit());
    }
    catch(std::bad_alloc & exc)
    {
        std::cerr << "[ERROR] Failed to allocate memory. Terminating." <<
                     std::endl;
    }

    return 0;
}
