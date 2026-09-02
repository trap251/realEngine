#include "API/OpenGL/OpenGL.h"
#include "API/OpenGL/OpenGLShader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//TEMP

#include "Camera/Camera.h"

//-----
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "Common/stb_image.h"

namespace OpenGLRenderer {
	unsigned int container_shaderProgram;
	unsigned int container_vao;
	unsigned int general_vbo;
	unsigned int container_ebo;

	unsigned int lightcube_shaderProgram;
	unsigned int lightcube_vao;
	unsigned int lightcube_ebo;

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


	namespace {
		void Draw();
		void bindTexture(unsigned int texture);
		void bindVertexArray(unsigned int vao);
		void bindBuffer(unsigned int vbo);
		unsigned int genArrayBuffers(float vertices[], size_t size);
		unsigned genElementArrayBuffers(unsigned int indices[], size_t size);
		unsigned int genVertexArrays();
		void setVertexAttributePointer(int index, int size, int stride, int offset);
		void deleteVertexArrays(unsigned int* vao);
		void deleteBuffers(unsigned int* vbo);
		unsigned int genTextures(const char* textureFilePath);
		void EnableDepthTest();
	}
	
	//TEMP
	float vertices[] = {
		// Positions			// Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	//---------------
	void Init() {
		container_vao = genVertexArrays();
		general_vbo = genArrayBuffers(vertices, sizeof(vertices));

		bindVertexArray(container_vao);
		// Position Attribute
		setVertexAttributePointer(0, 3, 6, 0);
		// Normal Attribute
		setVertexAttributePointer(1, 3, 6, 3 * sizeof(float));

		lightcube_vao = genVertexArrays();
		bindBuffer(general_vbo);
		setVertexAttributePointer(0, 3, 6, 0);


		// loadShader loads shaders in path=Resources/shaders/OpenGL/. 
		container_shaderProgram = OpenGLShader::loadShader("container");
		lightcube_shaderProgram = OpenGLShader::loadShader("lightcube");

		EnableDepthTest();

	}
	void Render(int windowWidth, int windowHeight) {
		OpenGL::Clear();

		OpenGLShader::useShaderProgram(&container_shaderProgram);
		OpenGLShader::setVec3(container_shaderProgram, "objectColor", 1.0f, 0.5f, 0.31f);
		OpenGLShader::setVec3(container_shaderProgram, "lightColor", 1.0f, 1.0f, 1.0f);
		OpenGLShader::setVec3(container_shaderProgram, "lightPos", lightPos.x, lightPos.y, lightPos.z);
		glm::vec3 camPos = Camera::getPosition();
		OpenGLShader::setVec3(container_shaderProgram, "viewPos", camPos.x, camPos.y, camPos.z);
		// Transformations
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		view = Camera::GetViewMatrix();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(70.0f), (float)windowWidth / windowHeight, 0.1f, 100.f);
		// --------------
		OpenGLShader::useShaderProgram(&container_shaderProgram);
		// Setting Transforms Uniform in shader
		OpenGLShader::setMat4(container_shaderProgram, "model", glm::value_ptr(model));
		OpenGLShader::setMat4(container_shaderProgram, "view", glm::value_ptr(view));
		OpenGLShader::setMat4(container_shaderProgram, "projection", glm::value_ptr(projection));
		// -----------------------------------
		bindVertexArray(container_vao);
		Draw();

		OpenGLShader::useShaderProgram(&lightcube_shaderProgram);
		OpenGLShader::setMat4(lightcube_shaderProgram, "projection", glm::value_ptr(projection));
		OpenGLShader::setMat4(lightcube_shaderProgram, "view", glm::value_ptr(view));
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		OpenGLShader::setMat4(lightcube_shaderProgram, "model", glm::value_ptr(model));

		bindVertexArray(lightcube_vao);
		Draw();

	}

	void Cleanup() {
		deleteVertexArrays(&container_vao);
		deleteBuffers(&general_vbo);
		deleteBuffers(&container_ebo);
	}


	// TEMP ---------------
	namespace {
		void Draw() {
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		void bindTexture(unsigned int texture) {
			glBindTexture(GL_TEXTURE_2D, texture);
		}

		void bindVertexArray(unsigned int vao) {
			glBindVertexArray(vao);
		}

		void bindBuffer(unsigned int vbo) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
		}

		unsigned int genArrayBuffers(float vertices[], size_t size) {
			unsigned int vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
			return vbo;
		}

		unsigned genElementArrayBuffers(unsigned int indices[], size_t size) {
			unsigned int ebo;
			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
			return ebo;
		}

		unsigned int genVertexArrays() {
			unsigned int vao;
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			return vao;
		}

		void setVertexAttributePointer(int index, int size, int stride, int offset) {
			glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset));
			glEnableVertexAttribArray(index);
		}

		void deleteVertexArrays(unsigned int* vao) {
			glDeleteVertexArrays(1, vao);
		}
		void deleteBuffers(unsigned int* vbo) {
			glDeleteBuffers(1, vbo);
		}

		//TEMP
		unsigned int genTextures(const char* textureFilePath) {
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			int width, height, nrChannels;
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = stbi_load(textureFilePath, &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
				std::cout << "Failed to load texture" << std::endl;
			stbi_image_free(data);

			return texture;
		}

		void EnableDepthTest() {
			glEnable(GL_DEPTH_TEST);
		}
		//-------------
	}

}