// GLFW 3.0 check
#ifdef USE_GLFW3
    #include <GL/glfw3.h>
#else
    #include <GL/glfw.h>
#endif

// Defines for glfw compatibility
#ifdef __glfw3_h__
    #define _VIEW_WINDOW window
    #define glfwSwapBuffers() glfwSwapBuffers(window); glfwPollEvents()
    #define createWindow(width, height)  (_VIEW_WINDOW = glfwCreateWindow(width, \
                            height, GLFW_WINDOWED, "Project", NULL))
    #define createContext() glfwMakeContextCurrent(_VIEW_WINDOW); \
                            glfwSetInputMode( window, GLFW_KEY_REPEAT, GL_TRUE )
    #define glfwSetWindowTitle(text) glfwSetWindowTitle(_VIEW_WINDOW, text)
    #define glfwGetKey(key) glfwGetKey(_VIEW_WINDOW, key)
    #define windowOpened() !glfwGetWindowParam(_VIEW_WINDOW, GLFW_CLOSE_REQUESTED)
    #define glfwGetWindowSize(width, height) glfwGetWindowSize(_VIEW_WINDOW, width, height)
    #define glfwGetMousePos(x,y)    glfwGetCursorPos(_VIEW_WINDOW, x,y)
    #define glfwGetMouseButton(button) glfwGetMouseButton(_VIEW_WINDOW, button)
#else
    #define createWindow(width, height)  glfwOpenWindow(width, height, \
                                           0, 0, 0, 0, 0, 0, GLFW_WINDOW)
    #define createContext() 
    #define windowOpened()  glfwGetWindowParam(GLFW_OPENED)
#endif
