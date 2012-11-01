#include "gui_main.h"

int initWindow()
{
    int width,height;

    glfwInit();

    if( !glfwOpenWindow( 512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowTitle("GLFW Application");


    glMatrixMode(GL_PROJECTION); // editing projection params
    glLoadIdentity();
    glfwGetWindowSize( &width, &height );
    float aspect_ratio = ((float)height) / width;
    glFrustum(-.5, .5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 50);

    glMatrixMode(GL_MODELVIEW);

    return 0;
}
