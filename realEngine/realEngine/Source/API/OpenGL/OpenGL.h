#pragma once

namespace OpenGL {
	void Init();
	void setViewport(void* window, int width, int height);
	void Clear();	
	//TEMP
	void Draw(unsigned int* shaderProgram);
	unsigned int setBuffers(int x, float vertices[], size_t size);
	unsigned int setVertexArrays(int x);
	unsigned int compileVertexShader(const char* shaderSource);
	unsigned int compileFragmentShader(const char* shaderSource);
	unsigned int shaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
	//----------------
}