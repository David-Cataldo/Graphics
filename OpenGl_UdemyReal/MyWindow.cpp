#include "MyWindow.h"

MyWindow::MyWindow()
{
    // default window size is 800 by 600
	width = 800;
	height = 600;
    xChange = 0.0f;
    yChange = 0.0f;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}

MyWindow::MyWindow(GLint windowWidth, GLint windowHeight)
{
    // lets the user choose the size of the window
	width = windowWidth;
	height = windowHeight;
    xChange = 0.0f;
    yChange = 0.0f;

    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}

int MyWindow::Initialize()
{
    // initialize glfw
    if (!glfwInit())
    {
        printf("GLFW initialization failed");
        glfwTerminate();
        return 1;
    }

    // setup glfw window properties
    // openGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // core profile = no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // allows forwards compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // create an GLFW window using the width and the height
    mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
    // if GLFW fails to create a window - terminate GLFW
    if (!mainWindow)
    {
        printf("GLFW window creation falied");
        glfwTerminate();
        return 1;
    }

    // get buffer size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //set context for GLEW to use
    // ties window to openGL
    glfwMakeContextCurrent(mainWindow);

    // Handle key + mouse input
    CreateCallbacks();
    //glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    // is GLEW fails to initialize - terminate GLFW and destroy the window
    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        printf("Error: %s", glewGetErrorString(error));
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        
        return 1;
    }

    // tells openGL to check which face is closest to camera and only draws that face
    glEnable(GL_DEPTH_TEST);

    // setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    glfwSetWindowUserPointer(mainWindow, this);

    return 0;
}

void MyWindow::CreateCallbacks()
{
    glfwSetKeyCallback(mainWindow, HandleKeys);
    glfwSetCursorPosCallback(mainWindow, HandleMouse);
}

GLfloat MyWindow::GetXChange()
{
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
}

GLfloat MyWindow::GetYChange()
{
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
}

void MyWindow::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            theWindow->keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;
        }
    }
}

void MyWindow::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
    MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));

    if (theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}

MyWindow::~MyWindow()
{
    // when our window object is destroyed, destroy the GLFW window and terminate GLFW
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}