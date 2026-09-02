#pragma once
#include <cstddef>

namespace OpenGL {
	void Init();
	void InitRenderer();
	void Render(int windowWidth, int windowHeight);
	void Cleanup();
	void setViewport(void* window, int width, int height);
	void Clear();


}
