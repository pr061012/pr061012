#include "../../model/World/World.h"
#include "../../view/View.h"
#include "../../model/BasicDefines.h"

#include <time.h>
#include <iostream>

/// Period for world updating.
const int PERIOD = CLOCKS_PER_SEC/TM_TICKS_PER_SECOND;

int main()
{
    World* w = new World(time(NULL));
    View* view = new View(w);
    int t0 = clock();

    do
    {
        if(clock() - t0 > PERIOD)
        {
            t0 += PERIOD;
        }

        view->redraw();

    } while(view->isExit());

    delete view;
    delete w;
}
