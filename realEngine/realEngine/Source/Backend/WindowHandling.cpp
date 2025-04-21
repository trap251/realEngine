#include "WindowHandling.h"
#include "API/OpenGL/OpenGL.h"
#include <iostream>

namespace WindowHandling {
    API g_api = API::OpenGL;
    WindowMode g_windowMode = WindowMode::WINDOWED;
    GLFWwindow* g_window = NULL;
    GLFWmonitor* g_primaryMonitor = NULL;
    const GLFWvidmode* g_videoMode;
    int g_fullscreenWidth = 0;
    int g_fullscreenHeight = 0;
    int g_windowedWidth = 0;
    int g_windowedHeight = 0;
    int g_currentWidth = 0;
    int g_currentHeight = 0;

    bool WindowHandling::Init(API api, WindowMode windowMode)
    {
        g_api = api;
        g_windowMode = windowMode;

        if (!glfwInit()) return false;
        
        if (g_api == API::OpenGL) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        g_primaryMonitor = glfwGetPrimaryMonitor();
        g_videoMode = glfwGetVideoMode(g_primaryMonitor);
        g_fullscreenWidth = g_videoMode->width;
        g_fullscreenHeight = g_videoMode->height;
        g_windowedWidth = g_fullscreenWidth * 0.75f;
        g_windowedHeight = g_fullscreenHeight * 0.75f;

        if (!WindowHandling::SetWindowMode(g_windowMode)) return false;

        //if (g_api == API::OpenGL) {
        //    glfwSetFramebufferSizeCallback(g_window, WindowHandling::m_framebuffer_size_callback);
        //}
        return true;
    }

    GLFWwindow* GetWindowPointer()
    {
        return g_window;
    }

    bool SetWindowMode(WindowMode windowMode) {
        if (g_window) {
            glfwDestroyWindow(g_window);
        }
        if (windowMode == WindowMode::FULLSCREEN) {
            g_window = glfwCreateWindow(g_fullscreenWidth, g_fullscreenHeight, "realEngine", NULL, NULL);
            g_currentWidth = g_fullscreenWidth;
            g_currentHeight = g_fullscreenHeight;
        }
        else if (windowMode == WindowMode::WINDOWED) {
            g_window = glfwCreateWindow(g_windowedWidth, g_windowedHeight, "realEngine", NULL, NULL);
            g_currentWidth = g_windowedWidth;
            g_currentHeight = g_windowedHeight;
        }
        if (!g_window) {
            std::cerr << "GLFW Window creation failed!" << std::endl;
            WindowHandling::Destroy();
            return false;
        }
        return true;
    }

    bool WindowIsOpen() {
        return (!glfwWindowShouldClose(g_window));
    }

    void PollEvents()
    {
        glfwPollEvents();
    }

    void DisplayFrame()
    {
        glfwSwapBuffers(g_window);
    }

    void MakeContextCurrent() {
        glfwMakeContextCurrent(g_window);
    }

    void Destroy()
    {
        glfwTerminate();
    }

    /*void m_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        OpenGL::Viewport(window, width, height);
    }*/
}
