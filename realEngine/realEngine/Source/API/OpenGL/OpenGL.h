#pragma once

namespace OpenGL {
	void Init();
	void setViewport(void* window, int width, int height);
	void Clear();
	//TEMP
	void Draw();
	void bindTexture(unsigned int texture);
	void bindVertexArray(unsigned int vao);
	unsigned int genArrayBuffers(float vertices[], size_t size);
	unsigned genElementArrayBuffers(unsigned int indices[], size_t size);
	unsigned int genVertexArrays();
	void setVertexAttributePointer(int size, int stride, int offset);
	void deleteVertexArrays(unsigned int* vao);
	void deleteBuffers(unsigned int* vbo);
	unsigned int genTextures(const char* textureFilePath);

	// Shader Helper Functions
	void useShaderProgram(unsigned int* shaderProgramID);
	unsigned int loadShaders(const char* shaderPath = "Resources/shaders/OpenGL/");
	void setBool(const int shaderProgramID, const char* name, bool value);
	void setInt(const int shaderProgramID, const char* name, int value);
	void setFloat(const int shaderProgramID, const char* name, float value);
	void setVec2(const int shaderProgramID, const char* name, const float* value);
	void setVec2(const int shaderProgramID, const char* name, float x, float y);
	void setVec3(const int shaderProgramID, const char* name, const float *value);
	void setVec3(const int shaderProgramID, const char* name, float x, float y, float z);
	void setVec4(const int shaderProgramID, const char* name, const float* value);
	void setVec4(const int shaderProgramID, const char* name, float x, float y, float z, float w);
	void setMat2(const int shaderProgramID, const char* name, const float* mat);
	void setMat3(const int shaderProgramID, const char* name, const float* mat);
	void setMat4(const int shaderProgramID, const char* name, const float* mat);

}