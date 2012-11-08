#include "../../model/World/World.h"
#include "../../view/View.h"

#include <time.h>
#include <iostream>

/// Period for world updating.
const int PERIOD = CLOCKS_PER_SEC/32;

int main()
{
    World* w = new World();
    View* view = new View(w);
    int t0 = clock();

    do
    {
        if(clock() - t0 > PERIOD)
        {
            t0 += PERIOD;
        }

        view->redraw();

        std::cin.get();
    } while(view->isExit());

    delete view;
}
