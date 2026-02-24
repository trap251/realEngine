# realEngine

A Graphics Engine with OpenGL and Vulkan Support. Made from Scratch. Easy to get into for beginners.



#### Screenshots:

![Wood-Textured Square Container with Blue Background](https://github.com/trap251/realEngine/blob/main/screenshots/container.png?raw=true)

#### Controls: 

&nbsp; Exit Engine = Escape  
&nbsp; Look Around = Mouse

#### What I've learnt so far:

Steps:

>1. Make sure to always set up the environment correctly for every new library.  
  Follow the process at learnopengl.com very strictly and carefully to avoid future headaches.
>2. Learn "Creating a window" at learnopengl.com.  
  Make a WindowHandling class for the GLFW window handling functionality. Files: WindowHandling.h, WindowHandling.cpp
>3. Make a Backend class to initialize everything and abstract it away from the Main.cpp which has the main() function.  
  Main.cpp should be absolutely clean and shouldn't directly communicate with Engine components such as WindowHandling, Input, etc. It contains Initialization functions such as WindowHandling::Init();
>4. Have a common Enums file (like realEngineEnums.h).  
  Use Enums to choose and check options. Have enums like API, WindowMode, etc. To set API to OpenGL, for example, you would simply pass API::OpenGL to Backend::Init() like so: Backend::Init(API::OpenGL, WindowMode::WINDOWED). When perfoming any API-specific actions within the engine we would always have if (m_api == API::OpenGL).
>6. GLFW has input handling functionality.  
  Have an Input class and implement GLFW Input Handling within it, follow information hiding principles. Files: Input.h, Input.cpp
>8. Implement shader handling in API/ as it involves API-specific functions. 
>9. Include a maths library and implement Transform(Scale, Rotate, Translate) functionality.  
  Add helper functions to the Shader namespace to pass values such as int,float,vec3, mat4, etc. to shaders. There is always an API function for that purpose. 
>11. Understand Euclidean angles and view, model, and projection matrices.  
  Implement a 'Camera' using these. Camera and Input need to communicate, use Backend to pass pointers to functions instead of intermingling these components. For example, a ProcessMouseMovement function from Camera can be passed to Input::Init() inside Backend. Input::Init() can use it as void (*processMouseMovementFunc_camera). This is how you can pass functions as parameters to other functions. Useful in keeping components separate and engine architecture clean.

Resources:

www.learnopengl.com
