#include "Backend.h"
#include "WindowHandling.h"
#include "API/OpenGL/OpenGL.h"
#include "Input/Input.h"
#include "Camera/Camera.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Backend {
	API g_api;
	WindowMode g_windowmode = WindowMode::WINDOWED;
	int g_windowWidth = 0;
	int g_windowHeight = 0;

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
			 // Positions				// Texture
			 -0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
			  0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
			  0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
			  0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
			 -0.5f,  0.5f, -0.5f,		0.0f, 1.0f,
			 -0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
			 
			 -0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
			  0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
			  0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
			  0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
			 -0.5f,  0.5f,  0.5f,		0.0f, 1.0f,
			 -0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
			 
			 -0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
			 -0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
			 -0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
			 -0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
			 -0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
			 
			  0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
			  0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
			  0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
			  0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
			  0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
			  0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
			 
			 -0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
			  0.5f, -0.5f, -0.5f,		1.0f, 1.0f,
			  0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
			  0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
			 -0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
			 -0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
			 
			 -0.5f,  0.5f, -0.5f,		0.0f, 1.0f,
			  0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
			  0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
			  0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,		0.0f, 0.0f,
			 -0.5f,  0.5f, -0.5f,		0.0f, 1.0f
		};
		//---------------

		g_api = api;
		g_windowmode = windowmode;
		if (!WindowHandling::Init(g_api, g_windowmode)) {
			std::cout << "WindowHandling Failed to Initialize\n";
			return false;
		}
		if (g_api == API::OpenGL) OpenGL::Init(); //Add an Else if (g_api == API::Vulkan) for Vulkan Integration.
		
		Camera::Init(glm::vec3(0,0,3)); // TEMP
		Input::Init(Backend::GetWindowPointer(), Camera::ProcessMouseMovement);

		//TEMP
		if (api == API::OpenGL) {
			container_vao = OpenGL::genVertexArrays();
			container_vbo = OpenGL::genArrayBuffers(vertices, sizeof(vertices));

			OpenGL::bindVertexArray(container_vao);
			// Position Attribute
			OpenGL::setVertexAttributePointer(3, 5, 0);
			// TextureCoord Attribute
			OpenGL::setVertexAttributePointer(2, 5, 3 * sizeof(float));

			// TEMP - loadShader() loads all shaders in path=Resources/shaders/OpenGL/. objectName parameter is irrelevant
			container_shaderProgram = OpenGL::loadShaders();

			OpenGL::EnableDepthTest();
		}
		//------------

		//TEMP - stbi/texture stuff
		container_texture = OpenGL::genTextures("Resources/textures/container.jpg");
		//------------

		g_windowWidth = WindowHandling::GetWindowWidth();
		g_windowHeight = WindowHandling::GetWindowHeight();

		return true;
	}

	void PreRender() {
		Input::Update();
	}

	void Render() {
		if (g_api == API::OpenGL) {
			OpenGL::Clear();
			OpenGL::bindTexture(container_texture);
			// Transformations
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			view = Camera::GetViewMatrix();
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(70.0f), (float)g_windowWidth / g_windowHeight, 0.1f, 100.f);
			// --------------
			OpenGL::useShaderProgram(&container_shaderProgram);
			// Setting Transforms Uniform in shader
			OpenGL::setMat4(container_shaderProgram, "model", glm::value_ptr(model));
			OpenGL::setMat4(container_shaderProgram, "view", glm::value_ptr(view));
			OpenGL::setMat4(container_shaderProgram, "projection", glm::value_ptr(projection));
			// -----------------------------------
			OpenGL::bindVertexArray(container_vao);
			
			OpenGL::Draw();		//Renders First cube

			//Renders Second Cube
			model = glm::translate(model, glm::vec3(-3, 0, 2.5));
			OpenGL::setMat4(container_shaderProgram, "model", glm::value_ptr(model));
			OpenGL::Draw();

			//Renders Third Cube
			model = glm::translate(model, glm::vec3(-3, 0, -3));
			OpenGL::setMat4(container_shaderProgram, "model", glm::value_ptr(model));
			OpenGL::Draw();
		}
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