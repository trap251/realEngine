#pragma once

namespace OpenGL {
	void Init();
	void setViewport(void* window, int width, int height);
	void Clear();
	//TEMP
	void Draw();
	void useShaderProgram(unsigned int* shaderProgram);
	void bindTexture(unsigned int texture);
	void bindVertexArray(unsigned int vao);
	unsigned int genArrayBuffers(float vertices[], size_t size);
	unsigned genElementArrayBuffers(unsigned int indices[], size_t size);
	unsigned int genVertexArrays();
	void setVertexAttributePointer(int size, int stride, int offset);
	void deleteVertexArrays(unsigned int* vao);
	void deleteBuffers(unsigned int* vbo);
	unsigned int genTextures(const char* textureFilePath);
	unsigned int loadShader(const char* objectName, const char* shaderPath = "Resources/shaders/OpenGL/");
}