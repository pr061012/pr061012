#include "../../model/World/IWorld.h"
#include "../../model/World/World.h"
#include "../../view/WorldRenderer.h"

#include <time.h>

int main()
{
    World* w = new World();
    WorldRenderer* view = new WorldRenderer(w);

//    view->drawingLoop();

    do
    {
        view->redraw();
    } while(view->isExit());

    //glfwTerminate();
}
