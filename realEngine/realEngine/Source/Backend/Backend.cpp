#include "Backend.h"
#include "WindowHandling.h"
#include "API/OpenGL/OpenGL.h"
#include "Input/Input.h"
#include <iostream>

namespace Backend {
	API g_api;
	WindowMode g_windowmode = WindowMode::WINDOWED;

	//TEMP
	unsigned int shaderProgram;
	//-----------------

	bool Init(API api, WindowMode windowmode) {

		//TEMP
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		//---------------

		g_api = api;
		g_windowmode = windowmode;
		if (!WindowHandling::Init(g_api, g_windowmode)) {
			std::cout << "WindowHandling Failed to Initialize\n";
			return false;
		}
		if (g_api == API::OpenGL) OpenGL::Init(); //Add an Else if (g_api == API::Vulkan) for Vulkan Integration.
		Input::Init(Backend::GetWindowPointer());
		
		//TEMP
		if (api == API::OpenGL) {
			OpenGL::setBuffers(1, vertices, sizeof(vertices));
			OpenGL::setVertexArrays(1);
			shaderProgram = OpenGL::loadShader("helloTriangle");
		}
		//------------

		return true;
	}

	void PreRender() {
		Input::Update();
	}

	void Render() {
		OpenGL::Clear();
		OpenGL::Draw(&shaderProgram);
	}
	void PostRender() {
		WindowHandling::DisplayFrame();
		WindowHandling::PollEvents();
	}
	
	bool WindowIsOpen() {
		return WindowHandling::WindowIsOpen();
	}

	void* GetWindowPointer() {
		return WindowHandling::GetWindowPointer();
	}

	void Cleanup() {
		WindowHandling::Destroy();
	}

}