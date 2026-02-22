#include "Backend.h"
#include "WindowHandling.h"
#include "API/OpenGL/OpenGL.h"
#include "Input/Input.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
			// Positions			// Textures Coords
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,		// Top Right
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		// Bottom Right
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		// Bottom Left
			-0.5f,	0.5f, 0.0f,		0.0f, 1.0f		// Top Left
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

			OpenGL::bindVertexArray(container_vao);
			// Position Attribute
			OpenGL::setVertexAttributePointer(3, 5, 0);
			// TextureCoord Attribute
			OpenGL::setVertexAttributePointer(2, 5, 3 * sizeof(float));

			// TEMP - loadShader() loads all shaders in path=Resources/shaders/OpenGL/. objectName parameter is irrelevant
			container_shaderProgram = OpenGL::loadShaders();
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
		// Transformation
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, sin((float)WindowHandling::GetWindowUpTime()), glm::vec3(0.0f, 0.0f, 1.0f));
		// --------------
		OpenGL::useShaderProgram(&container_shaderProgram);
		// Setting Transform Uniform in shader
		OpenGL::setMat4(container_shaderProgram, "transform", glm::value_ptr(transform));
		// -----------------------------------
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