#include <iostream>
#include <ctime>
#include <random>
#include <stdlib.h>
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
        srand(time(NULL));

        World world(rand(), SZ_WORLD_HSIDE);
        Controller control(&world);
        View view(&world);

        int t0 = clock();
        int counter = 0;

        do
        {
            if(clock() - t0 > PERIOD)
            {
                t0 += PERIOD;
            }

            if(counter++ == 3)
            {
                control.step();
                counter = 0;
            }

            view.redraw();
            std::cout << counter << "\n";

        } while(view.isExit());
    }
    catch(std::bad_alloc & exc)
    {
        std::cerr << "[ERROR] Failed to allocate memory. Terminating." <<
                     std::endl;
    }

    return 0;
}
