#include <iostream>
#include <ctime>
#include <random>
#include <cstdlib>

#include "common/BasicDefines.h"
#include "common/Log/Log.h"
#include "common/Exceptions/EInvalidResPath.h"
#include "control/Controller/Controller.h"
#include "model/World/World.h"
#include "view/View.h"

/// Period for world updating.
const int PERIOD = CLOCKS_PER_SEC / TM_TICKS_PER_SECOND;

int main()
{
    // Error flag.
    bool error = false;

    // Initializing random.
    srand(time(NULL));

    // Running game.
    try
    {
        // Creating World, View and Controller.
        World world(rand(), SZ_WORLD_HSIDE);
        Controller control(&world);
        View view(world);

        // Pausing game.
        view.setPaused(true);

        int t0 = clock();

        do
        {
            if(clock() - t0 > PERIOD)
            {
                t0 += PERIOD;
                if(!view.isPaused())
                {
                    control.step();
                }
                view.redraw();

                // Check if user wants to reset world.
                if(view.isReset())
                {
                    view.setReset(false);
                    world.reset();
                }
            }
        } while(view.continues());
    }
    // Invalid game resource path exception.
    catch(EInvalidResPath& exc)
    {
        error = true;
        Log::ERROR("Failed to load game resource '" + exc.getResPath() +
                   "'. Terminating.");
    }
    // Bad alloc exception.
    catch(std::bad_alloc& exc)
    {
        error = true;
        Log::ERROR("Failed to allocate memory. Terminating.");
    }

    if(error)
    {
        std::cout << "An error occurred during game execution. Look for LOG " <<
                     "file for details." << std::endl;
        return 1;
    }

    return 0;
}
