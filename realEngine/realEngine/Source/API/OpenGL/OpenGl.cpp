#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGL.h"
#include "Backend/WindowHandling.h"
#include <iostream>

namespace OpenGL {
	void Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to load GLAD\n";
			return;
		}
	}
	void setViewport(void* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
	void Clear() {
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	//TEMP
	void Draw(unsigned int* shaderProgram) {
		glUseProgram(*shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	unsigned int setBuffers(int x, float vertices[], size_t size) {
		unsigned int vbo;
		glGenBuffers(x, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		return vbo;
	}

	unsigned int setVertexArrays(int x) {
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//glBindVertexArray(0);
		return vao; 
	}
	unsigned int compileVertexShader(const char* shaderSource) {
		unsigned int shader;
		
		shader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);
		// CHECK WHETHER SUCCESSFUL
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "Error: Vertex Shader Compilation Failed!\n" << infoLog << std::endl;
		}
		return shader;
	}

	unsigned int compileFragmentShader(const char* shaderSource) {
		unsigned int shader;

		shader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);
		// CHECK WHETHER SUCCESSFUL
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "Error: Vertex Shader Compilation Failed!\n" << infoLog << std::endl;
		}
		return shader;

	}
	unsigned int shaderProgram(unsigned int vertexShader, unsigned int fragmentShader) {
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// CHEcK WHETHER SUCCESSFUL
		int success;
		char infoLog[512];
		glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "Error: Shader Program Linking Failed!\n" << infoLog << std::endl;
		}
		glUseProgram(shaderProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
	}
	//------------
}