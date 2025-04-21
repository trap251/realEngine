#pragma once
#include "Common/realEngineEnums.h"

namespace Backend {
	bool Init(API api, WindowMode windowmode);
	void PreRender();
	void Render();
	void PostRender();
	bool WindowIsOpen();
	void* GetWindowPointer();
	void Cleanup();
}