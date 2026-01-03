#pragma once

namespace OpenGL {
	void Init();
	void setViewport(void* window, int width, int height);
	void Clear();
	//TEMP
	void Draw(unsigned int* shaderProgram);
	unsigned int setBuffers(int x, float vertices[], size_t size);
	unsigned int setVertexArrays(int x);
	//REMOVE ---------
	//unsigned int compileVertexShader(const char* shaderSource);
	//unsigned int compileFragmentShader(const char* shaderSource);
	//unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
	//----------------
	unsigned int loadShader(const char* objectName, const char* shaderPath = "Resources/shaders/OpenGL/");
}