#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGL.h"
#include "Backend/WindowHandling.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "Common/stb_image.h"

namespace OpenGL {
	//TEMP
	int m_attributePointerMaxIndex;	// Points to the latest alotted attribute pointer index
	//--------------
	void Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to load GLAD\n";
			return;
		}
		m_attributePointerMaxIndex = 0;
	}
	void setViewport(void* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
	void Clear() {
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// TEMP ---------------

	void Draw() {
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void bindTexture(unsigned int texture) {
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void bindVertexArray(unsigned int vao) {
		glBindVertexArray(vao);
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

	void setVertexAttributePointer(int size, int stride, int offset) {
		glVertexAttribPointer(m_attributePointerMaxIndex, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset));
		glEnableVertexAttribArray(m_attributePointerMaxIndex);
		m_attributePointerMaxIndex++;
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