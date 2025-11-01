#include "Backend/Backend.h"
#include <iostream>

int main() {
	std::cout << "Hello, Real Engine!" << std::endl;

	
	// Initialize the engine
	if (!Backend::Init(API::OpenGL, WindowMode::WINDOWED)) {
		std::cout << "Backend Failed to Initialize\n";
		return 0;
	}

	// Load resources
	// Start the main loop
	
	while (Backend::WindowIsOpen()) {
		// Poll for events
		Backend::PreRender();
		// Render the scene
		Backend::Render();
		// Swap buffers
		Backend::PostRender();
	}
	// Clean up and exit
	Backend::Cleanup();

	std::cout << "Exiting Real Engine." << std::endl;
	return 0;
}