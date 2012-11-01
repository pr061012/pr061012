/********************************************************************/
/* To successfully build this test you have to      */
/* Link certain libaries: GL, GLU, GLFW, libSOIL.a  */
/* Add project folder to resources search directory */
/********************************************************************/


#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "SOIL.h" //Simple OpenGL Image Library

#include <GL/glfw.h>
#include <GL/gl.h>

#include "../../view/ViewObject.h"

#include "gui_main.h"

int main()
{
    srand(time(NULL)); // Getting random seed for our application.

    ViewObject* objects[5]; // Creating array of 'creatures' to render.

    for(int i = 0; i<5; ++i) // Filling it with humanoids standing at random positions.
    {
        objects[i] = new ViewObject(HUMANOID, rand()%16 - 8, rand()%16 - 8);

        std::cout << "Spawned humanoid at" <<
                     "x = " << objects[i]->getX() << "\t y = " << objects[i]->getY() << std::endl;
    }

    if(initWindow() != 0) return -2; // If window is not initialized, return error code.

    GLuint texture_buf[2]; // buffer for openGL textures.

    texture_buf[0] = SOIL_load_OGL_texture // Load an image file directly as a new OpenGL texture, using SOIL.
	(
        "grass.png",
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS
	);

	texture_buf[1] = SOIL_load_OGL_texture // Load an image file directly as a new OpenGL texture, using SOIL.
	(
        "human.png",
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MULTIPLY_ALPHA
	);

    // Check for an error during the load process
    if( 0 == texture_buf[0] || 0 == texture_buf[1] )
    {
        std::cout<< "SOIL loading error:'" << SOIL_last_result() << "' \n";
    }

    do
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glTranslatef( 0.0f, 0.0f, -16.0f ); // Push view back to see more.

        glBindTexture(GL_TEXTURE_2D, texture_buf[0]); // Choosing grass texture to render into the window

        // select modulate to mix texture with color for shading
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        // when texture area is small, bilinear filter the closest mipmap
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
        // when texture area is large, bilinear filter the original
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        glEnable(GL_TEXTURE_2D); // Entering texture drawing environment.

        glColor3f(0.9f, 0.9f, 0.9f); // Texture color may be changed to make darker grass or to make day/night sequence.

        glBegin(GL_POLYGON); // Texturing window frame with grass
            glTexCoord2f(0.0,   0.0); glVertex2f(-8.0f, -8.0f);
            glTexCoord2f(16.0,  0.0); glVertex2f( 8.0f, -8.0f);
            glTexCoord2f(16.0, 16.0); glVertex2f( 8.0f,  8.0f);
            glTexCoord2f(0.0,  16.0); glVertex2f(-8.0f,  8.0f);
        glEnd();

        glColor3f(1.0f, 1.0f, 1.0f);

        glBindTexture(GL_TEXTURE_2D, texture_buf[1]); // Choosing human texture to render into the window

        // Bringing up GL_BLEND to hide alpha channel
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        for(int i = 0; i<5; ++i)
        {
            double x = objects[i]->getX();
            double y = objects[i]->getY();
//            glRectd(x-0.15, y-0.15, x+0.15, y+0.15); // before it just drew a white square. How ugly...

            glBegin(GL_POLYGON); // Drawing human at specific place
                glTexCoord2f(0.0, 0.0);            glVertex2f(x-0.33, y-0.65);
                glTexCoord2f(14.0f/64, 0);         glVertex2f(x+0.33, y-0.65);
                glTexCoord2f(14.0f/64, 26.0f/121); glVertex2f(x+0.33, y+0.65);
                glTexCoord2f(0.0, 26.0f/121);      glVertex2f(x-0.33, y+0.65);
            glEnd();
        }
        glDisable(GL_BLEND);

        glDisable(GL_TEXTURE_2D); // Fun part is done for this frame, 2D textures are drawn.


        // Requesting image update
        glLoadIdentity();
        glfwSwapBuffers();

    } while(!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED)); // exit if ESC was pressed or window was closed

    // Some finishing touches.
    glDeleteTextures( 2, texture_buf ); // Clearing textures created
    glfwTerminate();

    return 0;
}
