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

#define STB_IMAGE_IMPLEMENTATION
#include "Common/stb_image.h"

namespace OpenGL {
	//TEMP
	int attributePointerMaxIndex = 0;	// Points to the latest alotted attribute pointer index
	//--------------
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

	void Draw() {
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	
	void useShaderProgram(unsigned int* shaderProgram) {
		glUseProgram(*shaderProgram);
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
		glVertexAttribPointer(attributePointerMaxIndex, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset));
		glEnableVertexAttribArray(attributePointerMaxIndex);
		attributePointerMaxIndex++;
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
	//-------------

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