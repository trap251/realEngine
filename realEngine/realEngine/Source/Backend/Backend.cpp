#include "Backend.h"
#include "WindowHandling.h"
#include "API/OpenGL/OpenGL.h"
#include "Input/Input.h"
#include <iostream>


namespace Backend {
	API g_api;
	WindowMode g_windowmode = WindowMode::WINDOWED;

	//TEMP
	unsigned int container_shaderProgram;
	unsigned int container_texture;
	unsigned int container_vao;
	unsigned int container_vbo;
	unsigned int container_ebo;

	//-----------------

	bool Init(API api, WindowMode windowmode) {

		//TEMP
		float vertices[] = {
			// Positions			// Colors			// Textures Coords
			 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,		// Top Right
			 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		// Bottom Right
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,		// Bottom Left
			-0.5f,	0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f		// Top Left
		};
		unsigned int indices[] = {
			0, 1, 3,	// First Triangle
			1, 2, 3		// Second Triangle
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
			container_vao = OpenGL::genVertexArrays();
			container_vbo = OpenGL::genArrayBuffers(vertices, sizeof(vertices));
			container_ebo = OpenGL::genElementArrayBuffers(indices, sizeof(indices));
			// Position Attribute
			OpenGL::setVertexAttributePointer(3, 8, 0);
			// Color Attribute
			OpenGL::setVertexAttributePointer(3, 8, 3 * sizeof(float));
			// TextureCoord Attribute
			OpenGL::setVertexAttributePointer(2, 8, 6 * sizeof(float));

			// TEMP - loadShader() loads all shaders in path=Resources/shaders/OpenGL/. objectName parameter is irrelevant
			container_shaderProgram = OpenGL::loadShader("container");
		}
		//------------

		//TEMP - stbi/texture stuff
		container_texture = OpenGL::genTextures("Resources/textures/container.jpg");
		//------------

		return true;
	}

	void PreRender() {
		Input::Update();
	}

	void Render() {
		OpenGL::Clear();
		OpenGL::bindTexture(container_texture);
		OpenGL::useShaderProgram(&container_shaderProgram);
		OpenGL::bindVertexArray(container_vao);
		OpenGL::Draw();
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
		//TEMP
		OpenGL::deleteVertexArrays(&container_vao);
		OpenGL::deleteBuffers(&container_vbo);
		OpenGL::deleteBuffers(&container_ebo);
		//----------------
		WindowHandling::Destroy();
	}

}