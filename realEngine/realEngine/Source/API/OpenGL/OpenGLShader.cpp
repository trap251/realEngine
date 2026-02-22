#include "OpenGL.h"
#include <glad/glad.h>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <glm/glm.hpp>

namespace OpenGL {
	unsigned int loadShaders(const char* shaderPath) {
		std::vector<unsigned int> compiledShaders;
		std::string shaderSource = "";
		std::unordered_map<std::string, GLenum> shaderTypes{
			{ ".vert", GL_VERTEX_SHADER },
			{ ".frag", GL_FRAGMENT_SHADER }
		};

		std::string baseDir = std::filesystem::path(shaderPath).string();

		unsigned int shaderProgramID = glCreateProgram();
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


				glAttachShader(shaderProgramID, currentShader);
				compiledShaders.push_back(currentShader);
				currentShader = NULL;
			}

		}

		glLinkProgram(shaderProgramID);

		// CHEcK WHETHER SUCCESSFUL
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
			std::cout << "Error: Shader Program Linking Failed!\n" << infoLog << std::endl;
		}
		glUseProgram(shaderProgramID);
		for (unsigned int shader : compiledShaders) {
			glDeleteShader(shader);
		}
		// -----------------------------------


		return shaderProgramID;

	}
	void useShaderProgram(unsigned int* shaderProgramID) {
		glUseProgram(*shaderProgramID);
	}

	void setBool(const int shaderProgramID , const char* name, bool value) {
		glUniform1i(glGetUniformLocation(shaderProgramID, name), (int)value);
	}
	void setInt(const int shaderProgramID , const char* name, int value) {
		glUniform1i(glGetUniformLocation(shaderProgramID, name), value);
	}
	void setFloat(const int shaderProgramID, const char* name, float value) {
		glUniform1f(glGetUniformLocation(shaderProgramID, name), value);
	}
	void setVec2(const int shaderProgramID , const char* name, const float* value) {
		glUniform2fv(glGetUniformLocation(shaderProgramID, name), 1, value);
	}
	void setVec2(const int shaderProgramID , const char* name, float x, float y) {
		glUniform2f(glGetUniformLocation(shaderProgramID, name), x, y);
	}
	void setVec3(const int shaderProgramID , const char* name, const float* value) {
		glUniform3fv(glGetUniformLocation(shaderProgramID, name), 1, value);
	}
	void setVec3(const int shaderProgramID , const char* name, float x, float y, float z) {
		glUniform3f(glGetUniformLocation(shaderProgramID, name), x, y, z);
	}
	void setVec4(const int shaderProgramID , const char* name, const float* value) {
		glUniform4fv(glGetUniformLocation(shaderProgramID, name), 1, value);
	}
	void setVec4(const int shaderProgramID , const char* name, float x, float y, float z, float w) {
		glUniform4f(glGetUniformLocation(shaderProgramID, name), x, y, z, w);
	}
	void setMat2(const int shaderProgramID , const char* name, const float* mat) {
		glUniformMatrix2fv(glGetUniformLocation(shaderProgramID, name), 1, GL_FALSE, mat);
	}
	void setMat3(const int shaderProgramID , const char* name, const float* mat) {
		glUniformMatrix3fv(glGetUniformLocation(shaderProgramID, name), 1, GL_FALSE, mat);
	}
	void setMat4(const int shaderProgramID , const char* name, const float* mat) {
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name), 1, GL_FALSE, mat);
	}
}