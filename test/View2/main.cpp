#include "../../model/World/IWorld.h"
#include "../../model/World/World.h"
#include "../../view/WorldRenderer.h"

int main()
{
    World* w = new World();
    WorldRenderer* view = new WorldRenderer(w);

//    view->drawingLoop();

    do
    {

    } while(view->isExit());

    //glfwTerminate();
}
