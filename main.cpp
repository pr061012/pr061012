#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <cstdlib>

#include "common/BasicDefines.h"
#include "common/Log/Log.h"
#include "common/Exceptions/EInvalidResPath.h"
#include "control/Controller/Controller.h"
#include "model/World/World.h"
#include "view/View.h"

// TODO: Use threads, Luke! We really don't need clock() and usleep().

// Clock period.
#define CLOCK_PERIOD        CLOCKS_PER_SEC / TM_TICKS_PER_SECOND
// Period for usleep() (in microseconds). Divided by 3 for better perfomance.
#define USLEEP_PERIOD       1000 * 1000 / TM_TICKS_PER_SECOND / 3

int main()
{
    // Error flag.
    bool error = false;

    // Initializing random.
    srand(time(0));

    // Running game.
    try
    {
        // Creating World, View and Controller.
        World world(rand(), SZ_WORLD_HSIDE);
        Controller control(&world);
        View view(world);

        // Pausing game.
        view.setPaused(true);

        long long beginning = clock();

        while(true)
        {
            // Au revoir.
            if(!view.continues())
            {
                break;
            }

            if(clock() - beginning > CLOCK_PERIOD)
            {
                beginning += CLOCK_PERIOD;

                // Running controller step (if needed).
                if(!view.isPaused())
                {
                    control.step();
                }

                // Redrawing picture.
                view.redraw();

                // Check if user wants to reset world.
                if(view.isReset())
                {
                    view.setReset(false);
                    world.reset();
                }

                usleep(USLEEP_PERIOD);
            }
        }
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
