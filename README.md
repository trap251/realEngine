# realEngine

A full-blown Gaming Engine with OpenGL and Vulkan Support. Made from Scratch. Easy to get into for beginners.

## What I've learnt so far:

Steps:

1. Make sure to always set up the environment correctly for every new library. Follow the process at learnopengl.com very strictly and carefully to avoid future headaches.
2. Learn "Creating a window" at learnopengl.com. Make a WindowHandling class for the GLFW windowhandling functionality. Files: WindowHandling.h, WindowHandling.cpp
3. Make a Backend class to initialize everything and abstract it away from the Main.cpp which has the main() function. Main.cpp should be absolutely clean and shouldn't directly communicate with Engine components such as WindowHandling, Input, etc. It contains Initialization functions such as WindowHandling::Init();
4. Have an common Enums file (like realEngineEnums.h). Use Enums to choose and check options. Put enums like API, WindowMode, etc. To set API to OpenGL, for example, you would simply pass API::OpenGL to Backend::Init() like so: Backend::Init(API::OpenGL, WindowMode::WINDOWED). When perfoming any API-specific actions within the engine we would always have if (m_api == API::OpenGL).

Resources:

www.learnopengl.com
