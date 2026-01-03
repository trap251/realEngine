#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGL.h"
#include "Backend/WindowHandling.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

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

	// TEMP ---------------

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
	unsigned int loadShader(const char* objectName, const char* shaderPath) {
		std::vector<unsigned int> compiledShaders;
		std::string shaderSource = "";
		std::unordered_map<std::string, GLenum> shaderTypes{
			{ ".vert", GL_VERTEX_SHADER },
			{ ".frag", GL_FRAGMENT_SHADER }
		};

		std::string baseDir = std::filesystem::path(shaderPath).string();

		unsigned int shaderProgram = glCreateProgram();
		unsigned int currentShader = 0;
		std::unordered_map<std::string, std::string> filePathsWithExtensions;


		for (const auto& [extension, shaderType] : shaderTypes) {
			for (std::filesystem::directory_entry file : std::filesystem::directory_iterator(baseDir)) {
				if (file.path().extension().string() != extension) {
					continue;
				}
				// Extracts the Source Code
				std::ifstream inputFile(file.path());
				std::stringstream sourceStream;
				sourceStream << inputFile.rdbuf();
				shaderSource = sourceStream.str();

				currentShader = glCreateShader(shaderType);

				// Compile Shader
				const char* shaderSourceConstChar = shaderSource.c_str();
				glShaderSource(currentShader, 1, &shaderSourceConstChar, NULL);
				glCompileShader(currentShader);
				// CHECK WHETHER SUCCESSFUL
				int success;
				char infoLog[512];
				glGetShaderiv(currentShader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(currentShader, 512, NULL, infoLog);
					std::cout << "Error: " << shaderType << " Shader Compilation Failed!\n" << infoLog << std::endl;
				}

				// ------------------------------------------------


				glAttachShader(shaderProgram, currentShader);
				compiledShaders.push_back(currentShader);
				currentShader = NULL;
			}

			}

			glLinkProgram(shaderProgram);

			// CHEcK WHETHER SUCCESSFUL
			int success;
			char infoLog[512];
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
				std::cout << "Error: Shader Program Linking Failed!\n" << infoLog << std::endl;
			}
			glUseProgram(shaderProgram);
			for (unsigned int shader : compiledShaders) {
				glDeleteShader(shader);
			}
			// -----------------------------------


			return shaderProgram;

		}
}