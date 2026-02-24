#pragma once

namespace Input {
	void Init(void* window, void (*ProcessMouseMovementFunction_camera) (float, float, float) );
	void Update();
}