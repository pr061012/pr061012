// Needed for std::this_thread::sleep_for.
#define _GLIBCXX_USE_NANOSLEEP

#include <iostream>
#include <chrono>
#include <thread>
#include <random>

#include "common/BasicDefines.h"
#include "common/Log/Log.h"
#include "common/Exceptions/EInvalidResPath.h"
#include "control/Controller/Controller.h"
#include "model/World.h"
#include "view/View.h"
#include "cli/CLI.h"

// Period (in milliseconds).
#define PERIOD          (uint) 1000 / TM_TICKS_PER_SECOND

int main()
{
    // Printing licensing information.
    std::cout << "pr061012 Copyright (C) 2012, pr061012 Team." << std::endl
              << "This program comes with ABSOLUTELY NO WARRANTY; for details"
              << " look for COPYING file." << std::endl
              << "This is free software, and you are welcome to redistribute it"
              << " under certain conditions." << std::endl;

    // Initializing random.
    srand(time(0));

    // Running game.
    try
    {
        // Creating World, View and Controller.
        World world(rand(), SZ_WORLD_HSIDE, false);
        Controller control(&world);
        View view(world);
        CLI cli(&world, &control);

        // Pausing game.
        view.setPaused(true);

        // Starting time point.
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

        while (true)
        {
            // Au revoir.
            if (!view.continues())
            {
                break;
            }

            // Current time point and difference between current and previous
            // points.
            std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time_span = std::chrono::duration_cast< std::chrono::duration<double> >(t2 - t1);

            // Check whether we need to update world and picture.
            if (time_span.count() * 1000 > PERIOD)
            {
                t1 = t2;

                // Running CLI.
                std::string cmd = view.getUserInput();
                if (cmd != "")
                {
                    if (cmd == "exit")
                    {
                        break;
                    }

                    std::cout << cli.runCommand(cmd);
                }

                // Running controller step (if needed).
                if (!view.isPaused())
                {
                    control.step();
                }

                // Redrawing picture.
                view.redraw();

                // Check if user wants to reset world.
                /*
                if (view.isReset())
                {
                    view.setReset(false);
                    world.reset();
                }
                */

                // Sleeping.
                std::this_thread::sleep_for(std::chrono::milliseconds(PERIOD));
            }
        }
    }
    // Catching exceptions.
    catch (std::exception& exc)
    {
        Log::ERROR(exc.what());
        std::cout << "An error occurred during game execution. Look for LOG " <<
                     "file for details." << std::endl;
        return 1;
    }

    return 0;
}
