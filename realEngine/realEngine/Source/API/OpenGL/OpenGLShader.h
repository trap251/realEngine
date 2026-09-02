#pragma once

namespace OpenGLShader {
	// Shader <Helper Functions
	void useShaderProgram(unsigned int* shaderProgramID);
	unsigned int loadShaders(const char* shaderPath = "Resources/shaders/OpenGL/");
	void setBool(const int shaderProgramID, const char* name, bool value);
	void setInt(const int shaderProgramID, const char* name, int value);
	void setFloat(const int shaderProgramID, const char* name, float value);
	void setVec2(const int shaderProgramID, const char* name, const float* value);
	void setVec2(const int shaderProgramID, const char* name, float x, float y);
	void setVec3(const int shaderProgramID, const char* name, const float* value);
	void setVec3(const int shaderProgramID, const char* name, float x, float y, float z);
	void setVec4(const int shaderProgramID, const char* name, const float* value);
	void setVec4(const int shaderProgramID, const char* name, float x, float y, float z, float w);
	void setMat2(const int shaderProgramID, const char* name, const float* mat);
	void setMat3(const int shaderProgramID, const char* name, const float* mat);
	void setMat4(const int shaderProgramID, const char* name, const float* mat);
}