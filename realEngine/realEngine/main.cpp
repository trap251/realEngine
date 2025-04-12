#include <iostream>
#include "Source/Backend/engineWindow.h"

int main() {
	std::cout << "Hello, Real Engine!" << std::endl;
	// Initialize the engine
	engineWindow::Init(API::OpenGL, WindowMode::WINDOWED);
	
	while (engineWindow::WindowIsOpen()) {
		// Poll for events
		engineWindow::PollEvents();

		// Render the scene
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Swap buffers
		engineWindow::DisplayFrame();
	}
	// Load resources
	// Start the main loop
	// Clean up and exit
	std::cout << "Exiting Real Engine." << std::endl;
	return 0;
}